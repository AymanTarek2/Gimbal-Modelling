import json
import sympy as sp
import xml.etree.ElementTree as ET
import sys
import os
import shutil
from model_visualizer import start_visualizer
from sympy.printing.mathematica import mathematica_code
import re  # Added for regex operations in Mathematica generation

class MujocoKinematicChainDebugger:
    def __init__(self, xml_content, output_folder="automated_dynamics"):
        self.root = ET.fromstring(xml_content)
        self.q_count = 0
        self.abs_pos_map = {} 
        self.robot_up_axis = None 
        
        # Modeling Variables
        self.q_joints = []
        self.dq_joints = []
        self.bodies_data = [] 
        self.params_dict = {} 
        
        # --- storage for points (Transformation matrices) ---
        self.visual_frames = []
        
        # Code Generation Variables
        self.output_folder = output_folder
        self.N = 0  
        
        # Base Symbols
        self.px, self.py, self.pz = sp.symbols('px py pz')
        self.bx, self.by, self.bz = sp.symbols('bx by bz')
        self.dpx, self.dpy, self.dpz = sp.symbols('dpx dpy dpz')
        self.dbx, self.dby, self.dbz = sp.symbols('dbx dby dbz')
        self.g = sp.symbols('g')

    def _get_internal_map(self):
        # NEW ORDER: [Joints, Base Orientation, Base Position]
        raw_q_all = self.q_joints + [self.bx, self.by, self.bz] + [self.px, self.py, self.pz]
        raw_dq_all = self.dq_joints + [self.dbx, self.dby, self.dbz] + [self.dpx, self.dpy, self.dpz]
        
        sub_map = {}
        for i, sym in enumerate(raw_q_all): sub_map[sym] = sp.Symbol(f"q_{i}")
        for i, sym in enumerate(raw_dq_all): sub_map[sym] = sp.Symbol(f"dq_{i}")
        return sub_map

    def _quat_to_up_axis(self, quat_str):
        if not quat_str: return sp.Matrix([0, 0, 1])
        w, x, y, z = [float(val) for val in quat_str.split()]
        R = sp.Matrix([
            [1 - 2*y**2 - 2*z**2,    2*x*y - 2*z*w,       2*x*z + 2*y*w],
            [2*x*y + 2*z*w,         1 - 2*x**2 - 2*z**2,   2*y*z - 2*x*w],
            [2*x*z - 2*y*w,         2*y*z + 2*x*w,       1 - 2*x**2 - 2*y**2]
        ])
        up = R.T * sp.Matrix([0, 0, 1])
        return sp.Matrix([round(float(val)) for val in up])

    def _get_alignment_matrix(self, target_axis, ref_up):
        v = sp.Matrix(target_axis).normalized()
        u = ref_up.normalized()
        if v == u: return sp.eye(3)
        if v == -u:
            if u[0] == 0 and u[1] == 0: return sp.Matrix([[-1,0,0],[0,1,0],[0,0,-1]])
            return sp.Matrix([[-1,0,0],[0,-1,0],[0,0,1]])
        c = u.dot(v)
        k = u.cross(v)
        K = sp.Matrix([[0, -k[2], k[1]], [k[2], 0, -k[0]], [-k[1], k[0], 0]])
        return sp.eye(3) + K + (K*K) * (1/(1+c))

    def _get_symbolic_rotation(self, axis, angle_sym):
        c, s = sp.cos(angle_sym), sp.sin(angle_sym)
        if axis[1] == 1: return sp.Matrix([[c, 0, s], [0, 1, 0], [-s, 0, c]])
        elif axis[2] == 1: return sp.Matrix([[c, -s, 0], [s, c, 0], [0, 0, 1]])
        else: return sp.Matrix([[1, 0, 0], [0, c, -s], [0, s, c]])
        
    def _quat_to_rot_matrix(self, quat_str):
            """
            Robust quaternion (w x y z) -> 3x3 rotation matrix conversion.
            Normalizes the quaternion first to avoid tiny numerical drifting
            and returns a sympy Matrix of floats.
            """
            if not quat_str:
                return sp.eye(3)
            w, x, y, z = [float(v) for v in quat_str.split()]
            norm = (w*w + x*x + y*y + z*z) ** 0.5
            if norm == 0:
                return sp.eye(3)
            w, x, y, z = w / norm, x / norm, y / norm, z / norm
            R = sp.Matrix([
                [1 - 2*(y*y + z*z),     2*(x*y - z*w),       2*(x*z + y*w)],
                [2*(x*y + z*w),         1 - 2*(x*x + z*z),   2*(y*z - x*w)],
                [2*(x*z - y*w),         2*(y*z + x*w),       1 - 2*(x*x + y*y)]
            ])
            return R
    
    
    def _collect_inertial_data(self, elem, parent_T=sp.eye(4)):
        """
        Recursively collects inertial data from `elem` and its jointless children.
        Returns list of dicts: {'m': mass, 'p': CoM_in_root, 'I': I_in_root, 'orig_diag': [dxx,dyy,dzz]}.
        """
        data_list = []

        pos = [float(x) for x in elem.get('pos', '0 0 0').split()]
        quat_str = elem.get('quat')

        R_local = self._quat_to_rot_matrix(quat_str) if quat_str else sp.eye(3)

        T_local = sp.eye(4)
        T_local[0:3, 0:3] = R_local
        T_local[0:3, 3] = sp.Matrix(pos)

        T_to_root = parent_T * T_local
        R_to_root = sp.Matrix(T_to_root[0:3, 0:3])
        P_in_root = sp.Matrix(T_to_root[0:3, 3])

        inertial = elem.find('inertial')
        if inertial is not None:
            m = float(inertial.get('mass', 0.0))
            i_pos_local = sp.Matrix([float(x) for x in inertial.get('pos', '0 0 0').split()])
            p_com_root = P_in_root + R_to_root * i_pos_local

            diag_vals = [float(x) for x in (inertial.get('diaginertia') or "0 0 0").split()]
            I_diag = sp.diag(*diag_vals)

            i_quat_str = inertial.get('quat')
            R_i = self._quat_to_rot_matrix(i_quat_str) if i_quat_str else sp.eye(3)

            R_total = R_to_root * R_i
            I_root = R_total * I_diag * R_total.T

            data_list.append({'m': m, 'p': p_com_root, 'I': I_root, 'orig_diag': diag_vals})

        # recurse into children that do NOT have their own joint
        for child in elem.findall('body'):
            if child.find('joint') is None:
                data_list.extend(self._collect_inertial_data(child, T_to_root))

        return data_list


    def run_full_modeling(self):
        print("="*120)
        print("FULL KINEMATIC CHAIN WITH PARENT-CHILD ORIENTATION INHERITANCE")
        print("="*120)
        
        worldbody = self.root.find('worldbody')
        first_body = worldbody.find('body') 
        
        def RotX(t): return sp.Matrix([[1, 0, 0], [0, sp.cos(t), -sp.sin(t)], [0, sp.sin(t), sp.cos(t)]])
        def RotY(t): return sp.Matrix([[sp.cos(t), 0, sp.sin(t)], [0, 1, 0], [-sp.sin(t), 0, sp.cos(t)]])
        def RotZ(t): return sp.Matrix([[sp.cos(t), -sp.sin(t), 0], [sp.sin(t), sp.cos(t), 0], [0, 0, 1]])

        if first_body is not None:
            self.robot_up_axis = self._quat_to_up_axis(first_body.get('quat'))
            print(f"DETECTED ROBOT UP AXIS: {list(self.robot_up_axis)}")

            # --- BUG FIX: Root the symbolic base position at its real XML coordinate ---
            body_pos_xml = [float(x) for x in first_body.get('pos', '0 0 0').split()]
            
            R_base = RotX(self.bx) * RotY(self.by) * RotZ(self.bz)
            self.T_base_raw = sp.eye(4)
            self.T_base_raw[0:3, 0:3] = R_base
            self.T_base_raw[0:3, 3] = sp.Matrix([
                body_pos_xml[0] + self.px, 
                body_pos_xml[1] + self.py, 
                body_pos_xml[2] + self.pz
            ])

            inertial = first_body.find('inertial')
            
            if inertial is not None and 'pos' in inertial.attrib:
                base_com_abs = [float(x) for x in inertial.get('pos').split()]
            elif first_body.get('pos') is not None:
                base_com_abs = [float(x) for x in first_body.get('pos').split()]
            else:
                print("Error: Could not determine base CoM from inertial.pos or body.pos; terminating.")
                sys.exit(1)

            print(f"\n[BODY: {first_body.get('name')}]\nCHAIN: T_base\n")
            sp.pprint(self.T_base_raw)
            print("-" * 120)

            # Pass 1: Gather joints to build the map
            self._first_pass_joints(first_body, True)
            self.internal_map = self._get_internal_map()
            self.N = len(self.internal_map) // 2
            
            # --- Lever is vector from XML Body Pos to XML CoM Pos ---
            rel_lever_base = sp.Matrix(base_com_abs) - sp.Matrix(body_pos_xml)
            T_Lever_base = sp.eye(4); T_Lever_base[0:3, 3] = rel_lever_base
            
            T_rooted = self.T_base_raw * T_Lever_base

            self.visual_frames.append((
                "base_com",
                T_rooted.subs(self.internal_map),
                ["T_base", "T_Lever_base"]
            ))

            # Pass 2: Recursive parse
            self._parse_recursive(
                body_element=first_body, 
                is_base=True, 
                ancestor_path_names=["T_base", "T_Lever_base"],
                parent_ref_pos=base_com_abs, 
                last_link_name=first_body.get('name'),
                parent_global_orient=sp.eye(3),
                accumulated_T_raw=T_rooted,
                accumulated_T_internal=T_rooted.subs(self.internal_map)
            )
            
        # --- LOGIC TO DUMP I MATRICES EARLY ---
        inertia_dump = {}
        for body in self.bodies_data:
            bn = body['name']
            inertia_dump[bn] = {
                "mass": self.params_dict[f"m_{bn}"][0],
                "inertia_tensor": [
                    [self.params_dict[f"Ixx_{bn}"][0], self.params_dict[f"Ixy_{bn}"][0], self.params_dict[f"Ixz_{bn}"][0]],
                    [self.params_dict[f"Ixy_{bn}"][0], self.params_dict[f"Iyy_{bn}"][0], self.params_dict[f"Iyz_{bn}"][0]],
                    [self.params_dict[f"Ixz_{bn}"][0], self.params_dict[f"Iyz_{bn}"][0], self.params_dict[f"Izz_{bn}"][0]]
                ]
            }
        with open("energies.json", "w") as f:
            json.dump({"fused_inertias": inertia_dump}, f, indent=4)
        print("Inertia matrices dumped to energies.json early.")
        
        print("\nStarting Kinematic Visualizer...")
        start_visualizer(self.visual_frames, self.internal_map)

        print("\n" + "="*80)
        print("STARTING LAGRANGIAN DERIVATION")
        print("="*80)
        self._derive_lagrangian()
        self.generate_c_code(self.M, self.C, self.G)
        self.generate_mathematica_code(self.M, self.C, self.G)
        # self.export_full_equations_text(self.M, self.C, self.G)
        

    def _first_pass_joints(self, body_element, is_base):
        joint_elem = body_element.find('joint')
        if not is_base and joint_elem is not None:
            raw_qi = sp.Symbol(f'jq_{self.q_count}')
            self.q_joints.append(raw_qi)
            self.dq_joints.append(sp.Symbol(f'jdq_{self.q_count}'))
            self.q_count += 1
        for child in body_element.findall('body'): self._first_pass_joints(child, False)


    def _parse_recursive(self, body_element, is_base, ancestor_path_names, parent_ref_pos, last_link_name, parent_global_orient, accumulated_T_raw, accumulated_T_internal):
        body_name = body_element.get('name', 'unnamed').replace("-", "_")
        joint_elem = body_element.find('joint')
        
        if not is_base and joint_elem is None:
            for child in body_element.findall('body'):
                self._parse_recursive(child, False, ancestor_path_names, parent_ref_pos, last_link_name, parent_global_orient, accumulated_T_raw, accumulated_T_internal)
            return

        pos_str = joint_elem.get('pos') if joint_elem is not None and 'pos' in joint_elem.attrib else body_element.get('pos')
        current_joint_abs = [float(x) for x in pos_str.split()] if pos_str else parent_ref_pos

        curr_T_raw, curr_T_int = accumulated_T_raw, accumulated_T_internal
        curr_global_orient, curr_blocks = parent_global_orient, []

        if not is_base:
            # REL_OFFSET is world vector. We rotate it by parent_global_orient.T to make it LOCAL.
            rel_offset_world = sp.Matrix([current_joint_abs[i] - parent_ref_pos[i] for i in range(3)])
            local_offset = parent_global_orient.T * rel_offset_world
            
            off_name = f"T_{last_link_name}_to_{body_name}"
            T_Off = sp.eye(4); T_Off[0:3, 3] = local_offset
            
            curr_T_raw *= T_Off; curr_T_int *= T_Off
            curr_blocks.append((off_name, T_Off, f"Offset: {list(local_offset)}"))
            
            self.visual_frames.append((f"Joint_{body_name}", curr_T_int, ancestor_path_names + [off_name]))

            if joint_elem is not None:
                axis = [float(x) for x in joint_elem.get('axis', '0 1 0').split()]
                R_glob = self._get_alignment_matrix(axis, self.robot_up_axis)
                T_Orient = sp.eye(4); T_Orient[0:3, 0:3] = parent_global_orient.T * R_glob
                curr_T_raw *= T_Orient; curr_T_int *= T_Orient
                curr_global_orient = R_glob
                curr_blocks.append((f"T_Orient_{body_name}", T_Orient, f"Align to {axis}"))
                
                raw_qi = self.q_joints.pop(0); self.q_joints.append(raw_qi)
                T_Rot = sp.eye(4); T_Rot[0:3, 0:3] = self._get_symbolic_rotation(self.robot_up_axis, raw_qi)
                curr_T_raw *= T_Rot; curr_T_int *= T_Rot.subs(self.internal_map)
                curr_blocks.append((f"T_Rot_{body_name}", T_Rot, f"Rot {raw_qi}"))
                
                self.visual_frames.append((
                    f"Rotated_{body_name}",
                    curr_T_int,
                    ancestor_path_names + [b[0] for b in curr_blocks]
                ))

        inertial_components = self._collect_inertial_data(body_element)
        if inertial_components:
            M_total = sum(c['m'] for c in inertial_components)
            COM_fused = sp.Add(*[c['m'] * c['p'] for c in inertial_components]) / M_total
            
            I_fused = sp.zeros(3, 3)
            for c in inertial_components:
                d = c['p'] - COM_fused 
                I_offset = c['m'] * ( (d.dot(d) * sp.eye(3)) - (d * d.T) )
                I_fused += (c['I'] + I_offset)

            # --- Detect & correct simple diagonal permutations (heuristic) ---
            # Build a reference diag list from the component diaginertia if available.
            ref_diag = None
            # take the first component that carries orig_diag as representative
            for c in inertial_components:
                if 'orig_diag' in c:
                    ref_diag = c['orig_diag']
                    break

            if ref_diag is not None:
                # expected diag values (sum if multiple components would be more complex;
                # here we pick the reference from the main inertial tag)
                expected = list(map(float, ref_diag))

                # current fused diag
                fused_diag = [float(sp.N(I_fused[i,i])) for i in range(3)]

                # find a permutation that maps fused_diag -> expected (by nearest match)
                import itertools
                best_perm = None
                best_err = float('inf')
                for perm in itertools.permutations(range(3)):
                    permuted = [fused_diag[perm[i]] for i in range(3)]
                    err = sum(abs(permuted[i] - expected[i]) for i in range(3))
                    if err < best_err:
                        best_err = err
                        best_perm = perm

                # if the best permutation is not identity and reduces error significantly, apply it
                if best_perm is not None and best_perm != (0,1,2) and best_err < sum(abs(fused_diag[i]-expected[i]) for i in range(3)):
                    # build permutation matrix P such that newI = P * I_fused * P.T
                    P = sp.zeros(3,3)
                    for new_i, old_i in enumerate(best_perm):
                        P[new_i, old_i] = 1
                    I_fused = (P * I_fused * P.T)
                    # optional debug print:
                    # print(f"[Inertia fix] body={body_name} best_perm={best_perm} before={fused_diag} after={[float(sp.N(I_fused[i,i])) for i in range(3)]}")

            rel_lever_world = COM_fused - sp.Matrix(current_joint_abs)
            local_lever = curr_global_orient.T * rel_lever_world
            T_Lever = sp.eye(4); T_Lever[0:3, 3] = local_lever

            

            m_sym = sp.Symbol(f'm_{body_name}')
            I_syms = sp.symbols(f'Ixx_{body_name} Iyy_{body_name} Izz_{body_name} Ixy_{body_name} Ixz_{body_name} Iyz_{body_name}')
            Ixx, Iyy, Izz, Ixy, Ixz, Iyz = I_syms
            
            self.params_dict[f'm_{body_name}'] = (float(M_total), "")
            self.params_dict[f'Ixx_{body_name}'] = (float(I_fused[0,0]), ""); self.params_dict[f'Iyy_{body_name}'] = (float(I_fused[1,1]), ""); self.params_dict[f'Izz_{body_name}'] = (float(I_fused[2,2]), "")
            self.params_dict[f'Ixy_{body_name}'] = (float(I_fused[0,1]), ""); self.params_dict[f'Ixz_{body_name}'] = (float(I_fused[0,2]), ""); self.params_dict[f'Iyz_{body_name}'] = (float(I_fused[1,2]), "")
            
            I_sym_mat = sp.Matrix([[Ixx, Ixy, Ixz], [Ixy, Iyy, Iyz], [Ixz, Iyz, Izz]])
            
            self.visual_frames.append((
                f"{body_name}_CoM",
                curr_T_int * T_Lever,
                ancestor_path_names + [b[0] for b in curr_blocks if "Lever" not in b[0]] + [f"T_Lever_{body_name}"]
            ))
            self.bodies_data.append({'name': body_name, 'T_com': curr_T_int * T_Lever, 'm_sym': m_sym, 'I_mat': I_sym_mat, 'R_link': curr_T_int[0:3, 0:3]})
            curr_blocks.append((f"T_Lever_{body_name}", T_Lever, f"Local CoM: {list(local_lever)}"))

        if not is_base:
            print(f"\n[BODY: {body_name}]\nCHAIN: {' * '.join(ancestor_path_names + [b[0] for b in curr_blocks])}")
            for name, matrix, desc in curr_blocks:
                print(f"\nBLOCK: {name} ({desc})"); sp.pprint(matrix)
            print("-" * 120)

        for child in body_element.findall('body'):
            self._parse_recursive(child, False, ancestor_path_names + [b[0] for b in curr_blocks if "Lever" not in b[0]], current_joint_abs, body_name, curr_global_orient, curr_T_raw, curr_T_int)


    def _derive_lagrangian(self):
        q = [sp.Symbol(f"q_{i}") for i in range(self.N)]
        dq = [sp.Symbol(f"dq_{i}") for i in range(self.N)]
        
        # Base Euler mapping to dq_i symbols
        bx_i, by_i, bz_i = self.bx.subs(self.internal_map), self.by.subs(self.internal_map), self.bz.subs(self.internal_map)
        dbx_i, dby_i, dbz_i = self.dbx.subs(self.internal_map), self.dby.subs(self.internal_map), self.dbz.subs(self.internal_map)
        w_world = (dbx_i*sp.Matrix([1,0,0])) + (sp.rot_axis1(bx_i).T*dby_i*sp.Matrix([0,1,0])) + (sp.rot_axis1(bx_i).T*sp.rot_axis2(by_i).T*dbz_i*sp.Matrix([0,0,1]))
        R_base = self.bodies_data[0]['R_link']
        w_body_base = R_base.T * w_world
        
        T_eul_inv = sp.Matrix.hstack(sp.diff(w_body_base, dbx_i), sp.diff(w_body_base, dby_i), sp.diff(w_body_base, dbz_i)).inv()
        wb = sp.symbols('wb1 wb2 wb3'); bv = sp.symbols('bv1 bv2 bv3')
        
        # Sub placeholders with real dq_i
        dq_vec = sp.Matrix(dq)
        subs_to_gen = {wb[i]: (sp.Matrix.hstack(sp.diff(w_body_base, dbx_i), sp.diff(w_body_base, dby_i), sp.diff(w_body_base, dbz_i)) * sp.Matrix([dbx_i, dby_i, dbz_i]))[i] for i in range(3)}
        subs_to_gen.update({bv[i]: (R_base.T * sp.Matrix([self.dpx.subs(self.internal_map), self.dpy.subs(self.internal_map), self.dpz.subs(self.internal_map)]))[i] for i in range(3)})

        total_KE, total_PE, body_energies = 0, 0, []
        for body in self.bodies_data:
            T = body['T_com'].subs(self.internal_map)
            pos = T[0:3, 3]
            v_world = pos.jacobian(q) * dq_vec
            v_body = (T[0:3, 0:3].T * v_world).subs(subs_to_gen)
            
            R = T[0:3, 0:3]
            R_dot = sum([sp.diff(R, q[i]) * dq[i] for i in range(self.N)], sp.zeros(3,3))
            Omega_skew = R_dot * R.T
            w_world_link = sp.Matrix([Omega_skew[2,1], Omega_skew[0,2], Omega_skew[1,0]])
            w_body_link = (R.T * w_world_link).subs(subs_to_gen)
            
            bKE = sp.Rational(1,2) * (body['m_sym'] * v_body.dot(v_body) + w_body_link.dot(body['I_mat'] * w_body_link))
            bPE = body['m_sym'] * self.g * pos.dot(self.robot_up_axis)
            total_KE += bKE; total_PE += bPE
            body_energies.append({"body_name": body['name'], "KE": str(bKE), "PE": str(bPE)})

        # Preserving early dump data and adding energies
        with open("energies.json", "r") as f:
            dump_data = json.load(f)
        dump_data["energy_equations"] = body_energies
        with open("energies.json", "w") as f: 
            json.dump(dump_data, f, indent=4)

        self.M = sp.zeros(self.N, self.N)
        for i in range(self.N):
            print(f"   > M Matrix: Computing Row {i+1}/{self.N}...")
            for j in range(i, self.N): self.M[i,j] = self.M[j,i] = sp.diff(total_KE, dq[i], dq[j])
        self.G = sp.Matrix([sp.diff(total_PE, qi) for qi in q])
        dM_dq = [sp.diff(self.M, qi) for qi in q]
        self.C = sp.zeros(self.N, self.N)
        for i in range(self.N):
            print(f"   > C Matrix: Computing Row {i+1}/{self.N}...")
            for j in range(self.N):
                self.C[i,j] = sum([sp.Rational(1,2) * dM_dq[k][i,j] * dq[k] for k in range(self.N)])

    def generate_c_code(self, M, C, G):
        print("\n--- Generating C Files ---")
        if os.path.exists(self.output_folder): shutil.rmtree(self.output_folder)
        for sub in ['M', 'C', 'G']: os.makedirs(f"{self.output_folder}/{sub}")

        self.params_dict['g'] = (9.81, " // Gravity constant")
        with open(f"{self.output_folder}/params.h", "w") as f:
            f.write("#ifndef PARAMS_H\n#define PARAMS_H\n")
            for key in sorted(self.params_dict.keys()): f.write(f"extern const double {key};\n")
            f.write("#endif\n")

        with open(f"{self.output_folder}/params.c", "w") as f:
            f.write('#include "params.h"\n')
            for k in sorted(self.params_dict.keys()):
                v, c = self.params_dict[k]
                f.write(f"const double {k} = {v};{c}\n")

        def write_element(folder, name, r, c, expr):
            suffix = f"_{r}_{c}" if c is not None else f"_{r}"
            func = f"calculate_{name}{suffix}"
            replacements, reduced = sp.cse(expr)
            with open(f"{self.output_folder}/{folder}/{func}.c", "w") as f:
                f.write('#include <math.h>\n#include "../params.h"\n')
                f.write(f"void {func}(const double q[{self.N}], const double dq[{self.N}], double *val) {{\n")
                for i in range(self.N): f.write(f"  double q_{i} = q[{i}]; double dq_{i} = dq[{i}];\n")
                for var, sub in replacements: f.write(f"  double {var} = {sp.ccode(sub)};\n")
                f.write(f"  *val = {sp.ccode(reduced[0])};\n}}\n")

        for r in range(self.N):
            write_element("G", "G", r, None, G[r])
            for c in range(self.N):
                write_element("M", "M", r, c, M[r,c])
                write_element("C", "C", r, c, C[r,c])

        with open(f"{self.output_folder}/model.h", "w") as h:
            h.write("#ifndef MODEL_H\n#define MODEL_H\n\nvoid compute_dynamics(const double q_meas[3], const double q_dot_meas[3], const double q_acc_meas[3], const double b_pos[3], const double b_vel[3], const double b_acc[3], const double b_ori[3], const double b_dori[3], const double b_ddori[3], double M[9][9], double C[9][9], double G[9], double tau[9]);\n#endif\n")

        with open(f"{self.output_folder}/model.c", "w") as c_f:
            c_f.write('#include "model.h"\n#include "params.h"\n\n')
            for r in range(9):
                c_f.write(f"extern void calculate_G_{r}(const double q[9], const double dq[9], double *val);\n")
                for col in range(9):
                    c_f.write(f"extern void calculate_M_{r}_{col}(const double q[9], const double dq[9], double *val);\n")
                    c_f.write(f"extern void calculate_C_{r}_{col}(const double q[9], const double dq[9], double *val);\n")
            c_f.write(f"\nvoid compute_dynamics(const double q_meas[3], const double q_dot_meas[3], const double q_acc_meas[3], const double b_pos[3], const double b_vel[3], const double b_acc[3], const double b_ori[3], const double b_dori[3], const double b_ddori[3], double M[9][9], double C[9][9], double G[9], double tau[9]) {{\n")
            c_f.write(f"  double q_full[9], dq_full[9];\n")
            for i in range(3):
                c_f.write(f"  q_full[{i}] = q_meas[{i}]; dq_full[{i}] = q_dot_meas[{i}];\n")
                c_f.write(f"  q_full[{i+3}] = b_ori[{i}]; dq_full[{i+3}] = b_dori[{i}];\n")
                c_f.write(f"  q_full[{i+6}] = b_pos[{i}]; dq_full[{i+6}] = b_vel[{i}];\n")
            for r in range(9):
                c_f.write(f"  calculate_G_{r}(q_full, dq_full, &G[{r}]);\n")
                for col in range(9):
                    c_f.write(f"  calculate_M_{r}_{col}(q_full, dq_full, &M[{r}][{col}]);\n")
                    c_f.write(f"  calculate_C_{r}_{col}(q_full, dq_full, &C[{r}][{col}]);\n")
            c_f.write("}\n")
        print("Success.")
        
        
    def generate_mathematica_code(self, M, C, G):
        print("\n--- Generating Mathematica File (Optimized) ---")
        
        # 1. Prepare clean parameter names (for defining the constants at the top)
        clean_params = {}
        for key, val_tuple in self.params_dict.items():
            # Remove underscores for Mathematica compatibility
            clean_key = key.replace("_", "")
            clean_params[clean_key] = val_tuple[0]

        filepath = os.path.join(self.output_folder, "dynamics.m")
        with open(filepath, "w") as f:
            f.write("(* AUTOMATICALLY GENERATED DYNAMICS MODEL *)\n\n")
            
            f.write("(* --- Parameters --- *)\n")
            for k, v in clean_params.items():
                f.write(f"{k} = {v};\n")
            
            # Helper to clean string: q_0 -> q0, Ixx_body -> Ixxbody, and fix scientific notation
            def math_clean(expr):
                # 1. Generate standard Mathematica code
                code = mathematica_code(expr)
                
                # 2. Fix scientific notation: Convert "1.23e-5" to "1.23*^-5"
                # This regex looks for: (Digit) + "e" + (Optional +/-) + (Digit)
                code = re.sub(r'(?<=\d)e(?=[+-]?\d)', '*^', code)
                
                # 3. Clean underscores
                return code.replace("_", "")

            f.write("\n(* --- Matrix M Elements --- *)\n")
            # Create a placeholder 2D list to store variable names for the grid
            m_grid = [[f"M{r}{c}" for c in range(self.N)] for r in range(self.N)]
            
            for r in range(self.N):
                # OPTIMIZATION: M is symmetric. Only compute diagonal and upper triangle.
                for c in range(r, self.N):
                    print(f"   > Writing M[{r},{c}]...")
                    var_name = f"M{r}{c}"
                    
                    # OPTIMIZATION: Generate code directly, then fix strings (No .subs())
                    final_code = math_clean(M[r,c])
                    
                    f.write(f"{var_name} = {final_code};\n")
                    
                    # If off-diagonal, write the symmetric counterpart immediately
                    if r != c:
                        sym_name = f"M{c}{r}"
                        f.write(f"{sym_name} = {var_name};\n")

            # Flatten the grid list for the brace string: {{M00, M01...}, ...}
            # BUG FIX: Avoid complex nested f-strings
            m_rows = [f"{{{', '.join(row)}}}" for row in m_grid]
            matrix_m_str = ", ".join(m_rows)
            f.write(f"\nMatrixM = {{{matrix_m_str}}};\n")
            
            f.write("\n(* --- Matrix C Elements --- *)\n")
            c_rows = []
            for r in range(self.N):
                row_vars = []
                for c in range(self.N):
                    # C is not symmetric, must compute all
                    print(f"   > Writing C[{r},{c}]...")
                    var_name = f"C{r}{c}"
                    
                    final_code = math_clean(C[r,c])
                    
                    f.write(f"{var_name} = {final_code};\n")
                    row_vars.append(var_name)
                c_rows.append(f"{{{', '.join(row_vars)}}}")

            matrix_c_str = ", ".join(c_rows)
            f.write(f"\nMatrixC = {{{matrix_c_str}}};\n")
            
            f.write("\n(* --- Vector G Elements --- *)\n")
            g_vars = []
            for r in range(self.N):
                print(f"   > Writing G[{r}]...")
                var_name = f"G{r}"
                
                final_code = math_clean(G[r])
                
                f.write(f"{var_name} = {final_code};\n")
                g_vars.append(var_name)
            
            vector_g_str = ", ".join(g_vars)
            f.write(f"\nVectorG = {{{vector_g_str}}};\n")
            
            f.write("\n(* --- Visualization --- *)\n")
            f.write("Print[\"Mass Matrix M:\"];\n")
            f.write("Print[Grid[MatrixM, Dividers -> All, Frame -> True, FrameStyle -> Directive[Dashed, Gray], ItemSize -> Full]];\n\n")
            
            f.write("Print[\"Coriolis Matrix C:\"];\n")
            f.write("Print[Grid[MatrixC, Dividers -> All, Frame -> True, FrameStyle -> Directive[Dashed, Gray], ItemSize -> Full]];\n\n")
            
            f.write("Print[\"Gravity Vector G:\"];\n")
            f.write("Print[Grid[{VectorG}, Dividers -> All, Frame -> True, FrameStyle -> Directive[Dashed, Gray], ItemSize -> Full]];\n")
            
        print(f"Mathematica file generated at: {filepath}")

    def export_full_equations_text(self, M, C, G):
        print("\n--- Exporting Full Equations to Text Files ---")
        text_folder = os.path.join(self.output_folder, "full_text_equations")
        if os.path.exists(text_folder): shutil.rmtree(text_folder)
        os.makedirs(text_folder)
        
        # Helper to write a file
        def save_file(name, expr):
            filename = os.path.join(text_folder, f"{name}.txt")
            with open(filename, "w") as f:
                # sp.srepr gives the exact internal representation (very verbose)
                # sp.trigsimp could be used, but you asked for the full RAW expression.
                # using str() gives the standard readable math format.
                f.write(str(expr)) 
            print(f"   Saved {name}.txt")

        # 1. Export M Matrix
        for r in range(self.N):
            for c in range(r, self.N): # Symmetric optimization
                save_file(f"M_{r}_{c}", M[r,c])
                if r != c:
                    # Just create a small reference file for the symmetric part
                    with open(os.path.join(text_folder, f"M_{c}_{r}.txt"), "w") as f:
                        f.write(f"SAME AS M_{r}_{c}")

        # 2. Export C Matrix
        for r in range(self.N):
            for c in range(self.N):
                save_file(f"C_{r}_{c}", C[r,c])

        # 3. Export G Vector
        for r in range(self.N):
            save_file(f"G_{r}", G[r])
            
        print(f"Done. All equations are in: {text_folder}")
            
        
if __name__ == "__main__":
    try:
        with open("gimbal_3.xml", 'r') as f:
            debugger = MujocoKinematicChainDebugger(f.read())
            debugger.run_full_modeling()
    except FileNotFoundError: print("Error: gimbal_3.xml not found.")