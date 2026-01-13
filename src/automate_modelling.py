import sympy as sp
import xml.etree.ElementTree as ET
import os
import shutil

class MujocoAbsoluteToDynamics:
    def __init__(self, xml_content):
        self.root = ET.fromstring(xml_content)
        self.bodies = []
        self.q = [] 
        self.dq = [] 
        self.params_dict = {} 
        self.output_folder = "automated_dynamics"
        self.world_pos_map = {}

    def _make_T(self, R, P):
        T = sp.eye(4)
        T[0:3, 0:3] = R
        T[0:3, 3] = P
        return T

    def parse_kinematics(self):
        print("--- Step 1: Parsing Absolute XML Kinematics ---")
        worldbody = self.root.find('worldbody')
        self.world_pos_map['world'] = [0.0, 0.0, 0.0]
        first_body = worldbody.find('body')
        if first_body is not None:
            self._parse_body(first_body, sp.eye(3), 'world')
        self.N = len(self.q)
        self.qq = sp.Matrix(self.q)
        self.dqq = sp.Matrix(self.dq)

    def _parse_body(self, body_element, R_parent_accumulated, parent_name):
        body_name = body_element.get('name', 'unnamed').replace("-", "_").replace(" ", "_")
        joint_elem = body_element.find('joint')
        pos_str = joint_elem.get('pos') if joint_elem is not None else body_element.get('pos')
        
        comment = ""
        if pos_str is None:
            pos_vals = self.world_pos_map[parent_name]
            comment = " // Inherited from parent"
        else:
            pos_vals = [float(x) for x in pos_str.split()]
        
        self.world_pos_map[body_name] = pos_vals
        for i, ax in enumerate(['x', 'y', 'z']):
            self.params_dict[f'p_{body_name}_{ax}'] = (pos_vals[i], comment)
        
        P_absolute_joint = sp.Matrix(pos_vals)
        R_current_accumulated = R_parent_accumulated
        for joint in body_element.findall('joint'):
            idx = len(self.q)
            qi, dqi = sp.symbols(f'q_{idx} dq_{idx}')
            self.q.append(qi); self.dq.append(dqi)
            axis = [float(x) for x in joint.get('axis', '0 0 1').split()]
            v = sp.Matrix(axis).normalized()
            K = sp.Matrix([[0, -v[2], v[1]], [v[2], 0, -v[0]], [-v[1], v[0], 0]])
            R_q = sp.eye(3) + sp.sin(qi)*K + (1-sp.cos(qi))*(K*K)
            R_current_accumulated = R_current_accumulated * R_q

        inertial = body_element.find('inertial')
        if inertial is not None:
            m_val = float(inertial.get('mass'))
            self.params_dict[f'm_{body_name}'] = (m_val, "")
            m_sym = sp.symbols(f'm_{body_name}')
            com_pos = [float(x) for x in inertial.get('pos').split()]
            for i, ax in enumerate(['x', 'y', 'z']):
                self.params_dict[f'com_{body_name}_{ax}'] = (com_pos[i], "")
            com_syms = sp.symbols(f'com_{body_name}_x com_{body_name}_y com_{body_name}_z')
            diag_i = [float(x) for x in inertial.get('diaginertia').split()]
            for i, ax in enumerate(['xx', 'yy', 'zz']):
                self.params_dict[f'I{ax}_{body_name}'] = (diag_i[i], "")
            for ax in ['xy', 'xz', 'yz']:
                self.params_dict[f'I{ax}_{body_name}'] = (0.0, "")
            
            rel_com_offset = sp.Matrix(com_syms) - P_absolute_joint
            P_com_world = P_absolute_joint + R_current_accumulated * rel_com_offset
            self.bodies.append({'P_com_world': P_com_world, 'm': m_sym, 'name': body_name})

        for child in body_element.findall('body'):
            self._parse_body(child, R_current_accumulated, body_name)

    def derive_dynamics(self):
        print("--- Step 2: Deriving Dynamics ---")
        g_sym = sp.symbols('g'); self.params_dict['g'] = (9.81, "")
        KE = 0; PE = 0
        for body in self.bodies:
            v_com = body['P_com_world'].jacobian(self.qq) * self.dqq
            PE += body['m'] * g_sym * body['P_com_world'][2]
            KE += sp.Rational(1,2) * body['m'] * v_com.dot(v_com)

        M = sp.zeros(self.N, self.N)
        for i in range(self.N):
            for j in range(i, self.N):
                M[i,j] = M[j,i] = sp.diff(KE, self.dq[i], self.dq[j])
                print(f"M: {i},{j}", end='\r')
        
        G = sp.zeros(self.N, 1)
        for i in range(self.N):
            G[i] = sp.diff(PE, self.q[i])
        
        C = sp.zeros(self.N, self.N)
        for i in range(self.N):
            for j in range(self.N):
                term = 0
                for k in range(self.N):
                    term += sp.Rational(1,2) * (sp.diff(M[i,j], self.q[k]) + sp.diff(M[i,k], self.q[j]) - sp.diff(M[j,k], self.q[i])) * self.dq[k]
                C[i,j] = term
                print(f"C: {i},{j}", end='\r')
        return M, C, G

    def generate_c_code(self, M, C, G):
        print("\n--- Step 3: Generating C Files ---")
        if os.path.exists(self.output_folder): shutil.rmtree(self.output_folder)
        for sub in ['M', 'C', 'G']: os.makedirs(f"{self.output_folder}/{sub}")

        with open(f"{self.output_folder}/params.h", "w") as f:
            f.write("#ifndef PARAMS_H\n#define PARAMS_H\n")
            for key in self.params_dict: f.write(f"extern const double {key};\n")
            f.write("#endif\n")

        with open(f"{self.output_folder}/params.c", "w") as f:
            f.write('#include "params.h"\n')
            for k, (v, c) in self.params_dict.items(): f.write(f"const double {k} = {v};{c}\n")

        def write_element(folder, name, r, c, expr):
            suffix = f"_{r}_{c}" if c is not None else f"_{r}"
            func = f"calculate_{name}{suffix}"
            path = f"{self.output_folder}/{folder}/{func}.c"
            replacements, reduced = sp.cse(expr)
            with open(path, "w") as f:
                f.write('#include <math.h>\n#include "../params.h"\n')
                f.write(f"void {func}(const double q[{self.N}], const double dq[{self.N}], double *val) {{\n")
                for i in range(self.N): f.write(f"  double q_{i} = q[{i}]; double dq_{i} = dq[{i}];\n")
                for var, sub in replacements: f.write(f"  double {var} = {sp.ccode(sub)};\n")
                f.write(f"  *val = {sp.ccode(reduced[0])};\n}}\n")

        for r in range(self.N):
            write_element("G", "G", r, None, G[r])
            for c in range(self.N):
                write_element("M", "M", r, c, M[r,c]); write_element("C", "C", r, c, C[r,c])

        # GENERATE WRAPPER (PARENT FILE)
        with open(f"{self.output_folder}/model_wrapper.h", "w") as h:
            h.write("#ifndef MODEL_WRAPPER_H\n#define MODEL_WRAPPER_H\n")
            h.write(f"void compute_dynamics_matrices(const double q[{self.N}], const double dq[{self.N}], double M[{self.N}][{self.N}], double C[{self.N}][{self.N}], double G[{self.N}]);\n")
            h.write("#endif\n")

        with open(f"{self.output_folder}/model_wrapper.c", "w") as c_f:
            c_f.write('#include "model_wrapper.h"\n')
            for r in range(self.N):
                c_f.write(f"extern void calculate_G_{r}(const double q[{self.N}], const double dq[{self.N}], double *val);\n")
                for col in range(self.N):
                    c_f.write(f"extern void calculate_M_{r}_{col}(const double q[{self.N}], const double dq[{self.N}], double *val);\n")
                    c_f.write(f"extern void calculate_C_{r}_{col}(const double q[{self.N}], const double dq[{self.N}], double *val);\n")
            c_f.write(f"\nvoid compute_dynamics_matrices(const double q[{self.N}], const double dq[{self.N}], double M[{self.N}][{self.N}], double C[{self.N}][{self.N}], double G[{self.N}]) {{\n")
            for r in range(self.N):
                c_f.write(f"  calculate_G_{r}(q, dq, &G[{r}]);\n")
                for col in range(self.N):
                    c_f.write(f"  calculate_M_{r}_{col}(q, dq, &M[{r}][{col}]);\n")
                    c_f.write(f"  calculate_C_{r}_{col}(q, dq, &C[{r}][{col}]);\n")
            c_f.write("}\n")
        print("Success.")

if __name__ == "__main__":
    with open("gimbal_2.xml", 'r') as f:
        model = MujocoAbsoluteToDynamics(f.read())
        model.parse_kinematics()
        M, C, G = model.derive_dynamics()
        model.generate_c_code(M, C, G)