import numpy as np
import math
import json
import os

# ==========================================
#   MATH HELPERS
# ==========================================
def quat_wxyz_to_rpy(quat_wxyz):
    w, x, y, z = quat_wxyz
    sinp = 2 * (w * y - z * x)
    if np.abs(sinp) >= 0.9995:
        pitch = np.copysign(np.pi / 2, sinp)
        roll = 0.0
        yaw = 2 * np.arctan2(x, w)
    else:
        pitch = np.arcsin(sinp)
        sinr_cosp = 2 * (w * x + y * z)
        cosr_cosp = 1 - 2 * (x * x + y * y)
        roll = np.arctan2(sinr_cosp, cosr_cosp)
        siny_cosp = 2 * (w * z + x * y)
        cosy_cosp = 1 - 2 * (y * y + z * z)
        yaw = np.arctan2(siny_cosp, cosy_cosp)
    return [roll, pitch, yaw]

def axis_angle_R_num(axis, theta):
    axis = np.array(axis, dtype=float)
    n = np.linalg.norm(axis)
    if n < 1e-9: return np.eye(3)
    u = axis / n
    ux, uy, uz = u
    c = math.cos(theta); s = math.sin(theta)
    return np.array([
        [c + ux*ux*(1-c),      ux*uy*(1-c) - uz*s, ux*uz*(1-c) + uy*s],
        [uy*ux*(1-c) + uz*s,   c + uy*uy*(1-c),    uy*uz*(1-c) - ux*s],
        [uz*ux*(1-c) - uy*s,   uz*uy*(1-c) + ux*s, c + uz*uz*(1-c)]
    ])

def make_homog(Rm, p=None):
    T = np.eye(4, dtype=float)
    T[:3,:3] = np.array(Rm, dtype=float)
    if p is not None:
        T[:3,3] = np.array(p, dtype=float)
    return T

def quat_from_matrix(Rm):
    m = np.asarray(Rm, dtype=float)
    tr = m[0,0] + m[1,1] + m[2,2]
    if tr > 0:
        S = math.sqrt(tr + 1.0) * 2.0
        w = 0.25 * S; x = (m[2,1] - m[1,2]) / S
        y = (m[0,2] - m[2,0]) / S; z = (m[1,0] - m[0,1]) / S
    else:
        if (m[0,0] > m[1,1]) and (m[0,0] > m[2,2]):
            S = math.sqrt(1.0 + m[0,0] - m[1,1] - m[2,2]) * 2.0
            w = (m[2,1] - m[1,2]) / S; x = 0.25 * S
            y = (m[0,1] + m[1,0]) / S; z = (m[0,2] + m[2,0]) / S
        elif m[1,1] > m[2,2]:
            S = math.sqrt(1.0 + m[1,1] - m[0,0] - m[2,2]) * 2.0
            w = (m[0,2] - m[2,0]) / S; x = (m[0,1] + m[1,0]) / S
            y = 0.25 * S; z = (m[1,2] + m[2,1]) / S
        else:
            S = math.sqrt(1.0 + m[2,2] - m[0,0] - m[1,1]) * 2.0
            w = (m[1,0] - m[0,1]) / S; x = (m[0,2] + m[2,0]) / S
            y = (m[1,2] + m[2,1]) / S; z = 0.25 * S
    return np.array([w, x, y, z], dtype=float)

# ==========================================
#   COMPUTE FACTORY
# ==========================================

def load_offsets_from_json(json_path):
    if not os.path.exists(json_path):
        raise FileNotFoundError(f"FK ERROR: '{json_path}' not found.")
    
    with open(json_path, 'r') as f:
        data = json.load(f)
    
    return data

def fk_chain_numeric(qvals, axes_local, A01, A12, A23, A3E):
    T = np.array(A01)
    # 3 Gimbal Joints
    for i in range(3):
        Rm = axis_angle_R_num(axes_local[i], qvals[i])
        if i == 0: T = T @ make_homog(Rm) @ A12
        elif i == 1: T = T @ make_homog(Rm) @ A23
        else: T = T @ make_homog(Rm) @ A3E
    return T

def make_compute_func_from_json(json_path):
    d = load_offsets_from_json(json_path)
    
    # Kinematic Chain
    A01 = np.array(d['A01'])
    A12 = np.array(d['A12'])
    A23 = np.array(d['A23'])
    A3E = np.array(d['A3E'])
    gimbal_axes = np.array(d['gimbal_axes'])
    
    # Base Info
    b_info = d['base_info']
    R_base_0 = np.array(b_info['R_base_0'])
    base_axes = np.array(b_info['axes'])
    base_order = b_info['order']  # e.g. [2, 1, 0]

    def compute_ee_orientation(base_rpy, qs, base_pos=None):
        # 1. Compute Rotations for Base Joints
        # base_rpy corresponds to index 0, 1, 2 of the stored axes
        Rs = []
        for i in range(3):
            # i is input index (0=Roll, 1=Pitch, 2=Yaw)
            # base_axes[i] is the vector for that input
            Rs.append(axis_angle_R_num(base_axes[i], base_rpy[i]))
            
        # 2. Compose Rotations in Correct Hierarchical Order
        # R_total = R[order[0]] @ R[order[1]] @ R[order[2]]
        R_rel = Rs[base_order[0]] @ Rs[base_order[1]] @ Rs[base_order[2]]
        
        # 3. Apply to Zero-Config Base Orientation
        # R_world_base = R_base_0 @ R_rel (assuming intrinsic joint application)
        R_base_curr = R_base_0 @ R_rel
        
        # 4. Construct Tworld_base
        Tworld_base = np.eye(4)
        Tworld_base[:3,:3] = R_base_curr
        if base_pos is not None:
            Tworld_base[:3,3] = base_pos
        else:
            # Default to zero if unknown? Or use T_base_0 position?
            # Usually base_pos comes from sensors, so we use input.
            pass

        # 5. Compute Chain
        Tbase_ee = fk_chain_numeric(qs, gimbal_axes, A01, A12, A23, A3E)
        
        # 6. Final Global EE
        Tworld_ee = Tworld_base @ Tbase_ee
        
        # Extract
        R_final = Tworld_ee[:3,:3]
        quat = quat_from_matrix(R_final)
        rpy = quat_wxyz_to_rpy(quat)
        pos = Tworld_ee[:3,3]

        return {'pos': pos, 'ori': [rpy[2], rpy[1], rpy[0]], 'fk_quat_wxyz': quat}

    return compute_ee_orientation