import sympy as sp
from model_visualizer import start_visualizer

def debug_manual_9dof_numeric():
    # --- 1. SYMBOLIC VARIABLES ---
    q1, q2, q3 = sp.symbols('q1 q2 q3')
    bx, by, bz = sp.symbols('bx by bz')
    px_s, py_s, pz_s = sp.symbols('px py pz')

    visual_frames = []
    internal_map = {q1: q1, q2: q2, q3: q3, bx: bx, by: by, bz: bz, px_s: px_s, py_s: py_s, pz_s: pz_s}

    # --- 2. NUMERIC CONSTANTS ---
    L1, L2 = 0.08822, 0.13548
    tilt_rad = float(sp.N(sp.rad(15 - 180))) # -165 degrees in radians
    
    # Hardcoded J1 Coordinates as requested
    j1_x, j1_y, j1_z = 0.02741, 0.16571, 0.09305

    def RotX(t): return sp.Matrix([[1, 0, 0], [0, sp.cos(t), -sp.sin(t)], [0, sp.sin(t), sp.cos(t)]])
    def RotY(t): return sp.Matrix([[sp.cos(t), 0, sp.sin(t)], [0, 1, 0], [-sp.sin(t), 0, sp.cos(t)]])
    def RotZ(t): return sp.Matrix([[sp.cos(t), -sp.sin(t), 0], [sp.sin(t), sp.cos(t), 0], [0, 0, 1]])

    def make_T(R, P):
        T = sp.eye(4)
        T[0:3, 0:3] = R
        T[0:3, 3] = P
        return T

    print("="*100)
    print("9-DOF NUMERIC ATOMIC DEBUGGER: FULL CHAIN RECONSTRUCTION")
    print("="*100)

    # --- BASE BLOCK ---
    R_base = RotX(bx) * RotY(by) * RotZ(bz)
    # T_base now uses the hardcoded J1 coordinates
    T_base = make_T(R_base, sp.Matrix([j1_x, j1_y, j1_z]))
    
    # --- LINK 1 BLOCKS ---
    T_rot_q1 = make_T(RotY(q1), sp.Matrix([0, 0, 0]))
    T_joint_q1 = T_base * T_rot_q1
    
    # base_link_origin removed, replaced with Joint_q1 as requested
    visual_frames.append(("Joint_q1", T_joint_q1, ["T_base", "T_rot_q1"]))

    T_base_com_offset = make_T(sp.eye(3), sp.Matrix([0, -0.05531, 0]))
    T_base_com_full = T_joint_q1 * T_base_com_offset
    visual_frames.append(("base_com", T_base_com_full, ["T_base", "T_rot_q1", "T_base_com_offset"]))

    print("\n[BODY: base_link]")
    print("CHAIN: T_base * T_base_com_offset")
    print("\n1. BLOCK: T_base (Hardcoded J1 Translation)")
    sp.pprint(T_base)
    print("\n2. BLOCK: T_base_com_offset (Numeric Offset)")
    sp.pprint(T_base_com_offset)
    print("-" * 100)

    T_com1_offset = make_T(sp.eye(3), sp.Matrix([0, L1, 0.02554]))
    T_link1_com_full = T_joint_q1 * T_com1_offset
    visual_frames.append(("link_1_CoM", T_link1_com_full, ["T_base", "T_rot_q1", "T_com1_offset"]))

    print("\n[BODY: link_1]")
    print("CHAIN: T_base * T_rot_q1 * T_com1_offset")
    print("\n1. BLOCK: T_rot_q1")
    sp.pprint(T_rot_q1)
    print("\n2. BLOCK: T_com1_offset")
    sp.pprint(T_com1_offset)
    print("-" * 100)

    # --- LINK 2 BLOCKS ---
    T_m1_m2_len = make_T(sp.eye(3), sp.Matrix([0, L2, 0]))
    T_static_tilt = make_T(RotX(tilt_rad), sp.Matrix([0, 0, 0]))
    T_rot_q2 = make_T(RotZ(q2), sp.Matrix([0, 0, 0]))
    T_joint_q2 = T_joint_q1 * T_m1_m2_len * T_static_tilt * T_rot_q2
    visual_frames.append(("Joint_q2", T_joint_q2, ["T_base", "T_rot_q1", "T_m1_m2_len", "T_static_tilt", "T_rot_q2"]))
    
    R_tilt_num = RotX(tilt_rad)
    P_local_2 = R_tilt_num.T * sp.Matrix([0, -0.00051, -0.06656])
    T_com2_offset = make_T(sp.eye(3), P_local_2)
    T_link2_com_full = T_joint_q2 * T_com2_offset
    visual_frames.append(("link_2_CoM", T_link2_com_full, ["T_base", "T_rot_q1", "T_m1_m2_len", "T_static_tilt", "T_rot_q2", "T_com2_offset"]))

    print("\n[BODY: link_2]")
    print("CHAIN: T_joint_q1 * T_m1_m2_len * T_static_tilt * T_rot_q2 * T_com2_offset")
    print("\n1. BLOCK: T_m1_m2_len")
    sp.pprint(T_m1_m2_len)
    print("\n2. BLOCK: T_static_tilt")
    sp.pprint(T_static_tilt)
    print("\n3. BLOCK: T_rot_q2")
    sp.pprint(T_rot_q2)
    print("\n4. BLOCK: T_com2_offset")
    sp.pprint(T_com2_offset)
    print("-" * 100)

    # --- LINK 3 BLOCKS ---
    P_local_m2_m3 = R_tilt_num.T * sp.Matrix([0, 0.03734, -0.09309])
    T_m2_m3_offset = make_T(sp.eye(3), P_local_m2_m3)
    T_untilt = make_T(RotX(-tilt_rad), sp.Matrix([0, 0, 0]))
    T_rot_q3 = make_T(RotY(q3), sp.Matrix([0, 0, 0]))
    T_joint_q3 = T_joint_q2 * T_m2_m3_offset * T_untilt * T_rot_q3
    visual_frames.append(("Joint_q3", T_joint_q3, ["T_base", "T_rot_q1", "T_m1_m2_len", "T_static_tilt", "T_rot_q2", "T_m2_m3_offset", "T_untilt", "T_rot_q3"]))

    # Final COM placeholder
    T_link3_com_full = T_joint_q3 * make_T(sp.eye(3), sp.Matrix([0, 0.02, 0])) 
    visual_frames.append(("link_3_CoM", T_link3_com_full, ["T_base", "T_rot_q1", "T_m1_m2_len", "T_static_tilt", "T_rot_q2", "T_m2_m3_offset", "T_untilt", "T_rot_q3", "final"]))

    print("\n[BODY: link_3]")
    print("CHAIN: T_joint_q2 * T_m2_m3_offset * T_untilt * T_rot_q3")
    print("\n1. BLOCK: T_m2_m3_offset")
    sp.pprint(T_m2_m3_offset)
    print("\n2. BLOCK: T_untilt")
    sp.pprint(T_untilt)
    print("\n3. BLOCK: T_rot_q3")
    sp.pprint(T_rot_q3)
    print("-" * 100)

    start_visualizer(visual_frames, internal_map)

if __name__ == "__main__":
    debug_manual_9dof_numeric()