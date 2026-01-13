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
            # FIXED: Un-rotate the global translation offset into the parent's frame
            world_offset = sp.Matrix([current_joint_abs[i] - parent_ref_pos[i] for i in range(3)])
            local_offset = curr_T_raw[0:3, 0:3].T * world_offset
            
            off_name = f"T_{last_link_name}_to_{body_name}"
            T_Off = sp.eye(4); T_Off[0:3, 3] = local_offset
            curr_T_raw *= T_Off; curr_T_int *= T_Off
            curr_blocks.append((off_name, T_Off, f"Offset: {list(local_offset)}"))
            self.visual_frames.append((f"Joint_{body_name}", curr_T_int, ancestor_path_names + [off_name]))
            
            if joint_elem is not None:
                axis = [float(x) for x in joint_elem.get('axis', '0 1 0').split()]
                R_glob = self._get_alignment_matrix(axis, self.robot_up_axis)
                T_Orient = sp.eye(4); T_Orient[0:3, 0:3] = curr_T_raw[0:3, 0:3].T * R_glob
                curr_T_raw *= T_Orient; curr_T_int *= T_Orient
                curr_global_orient = R_glob
                curr_blocks.append((f"T_Orient_{body_name}", T_Orient, f"Align to {axis}"))
                
                raw_qi = self.q_joints.pop(0); self.q_joints.append(raw_qi)
                T_Rot = sp.eye(4); T_Rot[0:3, 0:3] = self._get_symbolic_rotation(self.robot_up_axis, raw_qi)
                curr_T_raw *= T_Rot; curr_T_int *= T_Rot.subs(self.internal_map)
                curr_blocks.append((f"T_Rot_{body_name}", T_Rot, f"Rot {raw_qi}"))
                self.visual_frames.append((f"Rotated_{body_name}", curr_T_int, ancestor_path_names + [b[0] for b in curr_blocks]))

        # Fused Inertia Calculation
        def collect_inertial_data(elem):
            data_list = []
            inertial = elem.find('inertial')
            if inertial is not None:
                m = float(inertial.get('mass', 0))
                p_glob = sp.Matrix([float(x) for x in inertial.get('pos', '0 0 0').split()])
                diag_vals = [float(x) for x in (inertial.get('diaginertia') or "0 0 0").split()]
                I_diag = sp.diag(*diag_vals)
                quat_str = inertial.get('quat')
                if quat_str:
                    w, x, y, z = [float(val) for val in quat_str.split()]
                    R = sp.Matrix([[1-2*y**2-2*z**2, 2*x*y-2*z*w, 2*x*z+2*y*w], [2*x*y+2*z*w, 1-2*x**2-2*z**2, 2*y*z-2*x*w], [2*x*z-2*y*w, 2*y*z+2*x*w, 1-2*x**2-2*y**2]])
                    I_mat = R * I_diag * R.T
                else: I_mat = I_diag
                data_list.append({'m': m, 'p': p_glob, 'I': I_mat})
            for child in elem.findall('body'):
                if child.find('joint') is None: data_list.extend(collect_inertial_data(child))
            return data_list

        inertial_components = collect_inertial_data(body_element)
        if inertial_components:
            M_total = sum(c['m'] for c in inertial_components)
            COM_fused_glob = sp.Add(*[c['m'] * c['p'] for c in inertial_components]) / M_total
            
            # FIXED: Un-rotate the global lever for Body CoM
            world_lever = COM_fused_glob - sp.Matrix(current_joint_abs)
            local_lever = curr_T_raw[0:3, 0:3].T * world_lever
            T_Lever = sp.eye(4); T_Lever[0:3, 3] = local_lever
            
            I_fused = sp.zeros(3, 3)
            for c in inertial_components:
                d = c['p'] - COM_fused_glob 
                I_offset = c['m'] * ( (d.dot(d) * sp.eye(3)) - (d * d.T) )
                I_fused += (c['I'] + I_offset)

            m_sym = sp.Symbol(f'm_{body_name}')
            I_sym_mat = sp.Matrix(sp.symbols(f'Ixx_{body_name} Ixy_{body_name} Ixz_{body_name} Ixy_{body_name} Iyy_{body_name} Iyz_{body_name} Ixz_{body_name} Iyz_{body_name} Izz_{body_name}')).reshape(3,3)
            self.params_dict[f'm_{body_name}'] = (float(M_total), "")
            for idx, key in enumerate(['Ixx','Iyy','Izz','Ixy','Ixz','Iyz']):
                val = I_fused[0,0] if key=='Ixx' else I_fused[1,1] if key=='Iyy' else I_fused[2,2] if key=='Izz' else I_fused[0,1] if key=='Ixy' else I_fused[0,2] if key=='Ixz' else I_fused[1,2]
                self.params_dict[f'{key}_{body_name}'] = (float(val), "")

            self.visual_frames.append((f"{body_name}_CoM", curr_T_int * T_Lever, ancestor_path_names + [b[0] for b in curr_blocks if "Lever" not in b[0]] + [f"T_Lever_{body_name}"]))
            self.bodies_data.append({'name': body_name, 'T_com': curr_T_int * T_Lever, 'm_sym': m_sym, 'I_mat': I_sym_mat, 'R_link': curr_T_int[0:3, 0:3]})
            curr_blocks.append((f"T_Lever_{body_name}", T_Lever, f"Fused CoM (Local): {list(local_lever)}"))

        if not is_base:
            print(f"\n[BODY: {body_name} (FUSED)]\nCHAIN: {' * '.join(ancestor_path_names + [b[0] for b in curr_blocks])}")
            print("-" * 120)

        for child in body_element.findall('body'):
            self._parse_recursive(child, False, ancestor_path_names + [b[0] for b in curr_blocks if "Lever" not in b[0]], current_joint_abs, body_name, curr_global_orient, curr_T_raw, curr_T_int)
