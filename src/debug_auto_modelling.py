import sympy as sp
import xml.etree.ElementTree as ET

class MujocoKinematicChainDebugger:
    def __init__(self, xml_content):
        self.root = ET.fromstring(xml_content)
        self.q_count = 0
        self.abs_pos_map = {} 
        self.robot_up_axis = None # Will be detected

    def _quat_to_up_axis(self, quat_str):
        """
        Uses the quat ONLY to detect the functional 'Up' axis of the robot.
        Rounds strictly for this detection step.
        """
        if not quat_str: return sp.Matrix([0, 0, 1])
        w, x, y, z = [float(val) for val in quat_str.split()]
        # Quat to Rot Matrix
        R = sp.Matrix([
            [1 - 2*y**2 - 2*z**2,    2*x*y - 2*z*w,       2*x*z + 2*y*w],
            [2*x*y + 2*z*w,        1 - 2*x**2 - 2*z**2,   2*y*z - 2*x*w],
            [2*x*z - 2*y*w,        2*y*z + 2*x*w,       1 - 2*x**2 - 2*y**2]
        ])
        # Find where World-Z [0,0,1] points in the robot's frame
        up = R.T * sp.Matrix([0, 0, 1])
        # Round to integers to get clear axis [0, 1, 0] or [0, 0, 1]
        return sp.Matrix([round(float(val)) for val in up])

    def _get_alignment_matrix(self, target_axis, ref_up):
        """
        Generates Rotation Matrix to align 'ref_up' to 'target_axis'.
        """
        v = sp.Matrix(target_axis).normalized()
        u = ref_up.normalized()
        
        if v == u: return sp.eye(3)
        if v == -u: # Handle 180 flip case simply
            if u[0] == 0 and u[1] == 0: return sp.Matrix([[-1,0,0],[0,1,0],[0,0,-1]]) # Simple flip for Z
            return sp.Matrix([[-1,0,0],[0,-1,0],[0,0,1]]) # Fallback flip

        c = u.dot(v)
        k = u.cross(v)
        K = sp.Matrix([[0, -k[2], k[1]], [k[2], 0, -k[0]], [-k[1], k[0], 0]])
        # Rodrigues' rotation formula
        R = sp.eye(3) + K + (K*K) * (1/(1+c))
        return R

    def _get_symbolic_rotation(self, axis, angle_sym):
        """
        Generates a standard rotation matrix around the DETECTED Up axis.
        """
        c, s = sp.cos(angle_sym), sp.sin(angle_sym)
        # If Up is Y (0, 1, 0) -> RotY
        if axis[1] == 1: 
            return sp.Matrix([[c, 0, s], [0, 1, 0], [-s, 0, c]])
        # If Up is Z (0, 0, 1) -> RotZ
        elif axis[2] == 1:
            return sp.Matrix([[c, -s, 0], [s, c, 0], [0, 0, 1]])
        # If Up is X (1, 0, 0) -> RotX
        else:
            return sp.Matrix([[1, 0, 0], [0, c, -s], [0, s, c]])

    def debug_numeric_chains(self):
        print("="*120)
        print("FULL KINEMATIC CHAIN WITH PARENT-CHILD ORIENTATION INHERITANCE")
        print("="*120)
        
        worldbody = self.root.find('worldbody')
        first_body = worldbody.find('body') 
        
        bx, by, bz = sp.symbols('bx by bz')
        px, py, pz = sp.symbols('px py pz')
        
        def RotX(t): return sp.Matrix([[1, 0, 0], [0, sp.cos(t), -sp.sin(t)], [0, sp.sin(t), sp.cos(t)]])
        def RotY(t): return sp.Matrix([[sp.cos(t), 0, sp.sin(t)], [0, 1, 0], [-sp.sin(t), 0, sp.cos(t)]])
        def RotZ(t): return sp.Matrix([[sp.cos(t), -sp.sin(t), 0], [sp.sin(t), sp.cos(t), 0], [0, 0, 1]])

        if first_body is not None:
            # 1. DETECT THE UP AXIS
            self.robot_up_axis = self._quat_to_up_axis(first_body.get('quat'))
            print(f"DETECTED ROBOT UP AXIS: {list(self.robot_up_axis)}")

            # 2. T_BASE (Pure Symbolic)
            R_base = RotX(bx) * RotY(by) * RotZ(bz)
            self.T_base = sp.eye(4)
            self.T_base[0:3, 0:3] = R_base
            self.T_base[0:3, 3] = sp.Matrix([px, py, pz])

            inertial = first_body.find('inertial')
            base_com_abs = [float(x) for x in (inertial.get('pos') if inertial is not None else "0 0 0").split()]
            self.abs_pos_map['base_com_ref'] = base_com_abs 
            
            # Start recursion with Identity global orientation
            self._parse_recursive(
                body_element=first_body, 
                is_base=True, 
                ancestor_path_names=["T_base"], 
                parent_ref_pos=base_com_abs, 
                last_link_name=first_body.get('name'),
                parent_global_orient=sp.eye(3) # Base starts aligned
            )

    def _parse_recursive(self, body_element, is_base=False, ancestor_path_names=[], parent_ref_pos=None, last_link_name=None, parent_global_orient=None):
        body_name = body_element.get('name', 'unnamed').replace("-", "_")
        joint_elem = body_element.find('joint')
        
        # Skip bodies without joints unless it's the base (or we need to traverse fixed links)
        # Note: If you want to support fixed links (camera/sensors), remove 'and joint_elem is None' check below
        if not is_base and joint_elem is None:
            for child in body_element.findall('body'):
                self._parse_recursive(child, False, ancestor_path_names, parent_ref_pos, last_link_name, parent_global_orient)
            return

        # --- POSITION HANDLING (INHERITANCE FIX) ---
        pos_str = None
        
        # Check if 'pos' exists in attributes (handling joint vs body pos priority)
        if joint_elem is not None and 'pos' in joint_elem.attrib:
            pos_str = joint_elem.get('pos')
        elif 'pos' in body_element.attrib:
            pos_str = body_element.get('pos')
            
        pos_comment = ""
        if pos_str is None:
            # Not found -> Inherit from Parent
            current_joint_abs = parent_ref_pos
            pos_comment = " # (Not found, inherited from parent)"
        else:
            current_joint_abs = [float(x) for x in pos_str.split()]

        current_link_blocks = []
        
        # Global orientation of THIS link (to be passed to children)
        current_global_orient = parent_global_orient

        if is_base:
            print(f"\n[BODY: {body_name}]\nCHAIN: T_base\n")
            sp.pprint(self.T_base)
            child_ref_pos = self.abs_pos_map['base_com_ref']
            new_path_names = ["T_base"]
            active_link_name = body_name
        else:
            # 1. Physical Offset
            rel_offset = [current_joint_abs[i] - parent_ref_pos[i] for i in range(3)]
            offset_name = f"T_{last_link_name}_to_{body_name}"
            T_Off = sp.eye(4); T_Off[0:3, 3] = sp.Matrix(rel_offset)
            current_link_blocks.append((offset_name, T_Off, f"Offset: {rel_offset}{pos_comment}"))
            
            if joint_elem is not None:
                # 2. Orientation Logic (The Fix)
                axis = [float(x) for x in joint_elem.get('axis', '0 1 0').split()]
                
                # Calculate what orientation we NEED locally to match the axis
                # This is the "Absolute" alignment required for this specific joint
                R_global_required = self._get_alignment_matrix(axis, self.robot_up_axis)
                
                # Calculate the RELATIVE rotation needed to get from Parent's orientation to Required orientation
                # R_relative = R_parent_global.T * R_global_required
                # This inherently "Untilts" the parent and "Tilts" the child
                R_relative = parent_global_orient.T * R_global_required
                
                T_Orient = sp.eye(4); T_Orient[0:3, 0:3] = R_relative
                current_link_blocks.append((f"T_Orient_{body_name}", T_Orient, f"Align to {axis} (Relative)"))
                
                # Update current global orientation for the next child
                current_global_orient = R_global_required
                
                # 3. Symbolic Rotation (Using DETECTED Up Axis)
                qi = sp.Symbol(f'q_{self.q_count}')
                self.q_count += 1
                
                # Dynamic Rotation Matrix based on what we defined as "Up"
                R_q = self._get_symbolic_rotation(self.robot_up_axis, qi)
                
                T_Rot = sp.eye(4); T_Rot[0:3, 0:3] = R_q
                current_link_blocks.append((f"T_Rot_{body_name}", T_Rot, f"Rot q_{self.q_count-1}"))

            inertial = body_element.find('inertial')
            child_lever = [float(x) - current_joint_abs[i] for i, x in enumerate(inertial.get('pos').split())] if inertial is not None else [0,0,0]
            T_Lever = sp.eye(4); T_Lever[0:3, 3] = sp.Matrix(child_lever)
            current_link_blocks.append((f"T_Lever_{body_name}", T_Lever, f"Lever: {child_lever}"))
            
            print(f"\n[BODY: {body_name}]\nCHAIN: {' * '.join(ancestor_path_names + [b[0] for b in current_link_blocks])}")
            for name, matrix, desc in current_link_blocks:
                print(f"\nBLOCK: {name} ({desc})"); sp.pprint(matrix)
            print("-" * 100)
            
            # Prepare for recursion
            # Exclude T_Lever from path names passed to children (Lever is for inertial center, not joint chain)
            chain_without_lever = [b[0] for b in current_link_blocks if "Lever" not in b[0]]
            new_path_names = ancestor_path_names + chain_without_lever
            child_ref_pos = current_joint_abs
            active_link_name = body_name

        for child in body_element.findall('body'):
            self._parse_recursive(child, False, new_path_names, child_ref_pos, active_link_name, current_global_orient)

if __name__ == "__main__":
    with open("gimbal_2.xml", 'r') as f:
        debugger = MujocoKinematicChainDebugger(f.read())
        debugger.debug_numeric_chains()