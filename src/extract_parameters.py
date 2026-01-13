import mujoco
import numpy as np
import json
import os
from scipy.spatial.transform import Rotation as R

XML_PATH = "gimbal.xml"
JSON_OUTPUT = "gimbal_fk_data.json"

def make_homog(Rm, p=None):
    T = np.eye(4, dtype=float)
    T[:3,:3] = np.array(Rm, dtype=float)
    if p is not None:
        T[:3,3] = np.array(p, dtype=float)
    return T

def inv_homog(T):
    Rm = T[:3,:3]; p = T[:3,3]
    Rt = Rm.T
    Tinv = np.eye(4, dtype=float)
    Tinv[:3,:3] = Rt
    Tinv[:3,3]  = -Rt @ p
    return Tinv

def safe_id(model, type_enum, name):
    idx = mujoco.mj_name2id(model, type_enum, name)
    if idx < 0: raise KeyError(f"Could not find {name} (type {type_enum})")
    return int(idx)

def read_world_body_T(model, data, body_id):
    arr_xmat = np.asarray(data.xmat)
    R_mat = arr_xmat[body_id].reshape(3,3)
    p_vec = np.asarray(data.xpos)[body_id]
    return make_homog(R_mat, p_vec)

def read_world_site_T(model, data, site_id):
    arr_xmat = np.asarray(data.site_xmat)
    R_mat = arr_xmat[site_id].reshape(3,3)
    p_vec = np.asarray(data.site_xpos)[site_id]
    return make_homog(R_mat, p_vec)

def get_joint_axis(model, jid):
    """Safely retrieves the joint axis regardless of array shape (1D vs 2D)."""
    axis_data = model.jnt_axis
    
    # Handle 2D Array (Standard MuJoCo Bindings: [N, 3])
    if axis_data.ndim == 2:
        raw_axis = axis_data[jid]
    # Handle 1D Array (Legacy/Other Bindings: [N*3])
    else:
        raw_axis = axis_data[jid*3 : jid*3+3]

    # Sanity check for empty axis (uninitialized)
    if raw_axis.shape != (3,) or np.all(raw_axis == 0):
        # Default MuJoCo joint axis is Z [0, 0, 1]
        return np.array([0.0, 0.0, 1.0], dtype=float)
        
    return raw_axis.copy()

def solve_base_kinematics(model, data, base_name="base_link"):
    print("  Analyizing Base Kinematics...")
    base_id = safe_id(model, mujoco.mjtObj.mjOBJ_BODY, base_name)
    
    # 1. Zero Config
    data.qpos[:] = 0.0
    mujoco.mj_forward(model, data)
    T_base_0 = read_world_body_T(model, data, base_id)
    R_base_0 = T_base_0[:3,:3]
    
    # 2. Identify Axes
    base_joints = ["base_roll", "base_pitch", "base_yaw"]
    joint_ids = [safe_id(model, mujoco.mjtObj.mjOBJ_JOINT, jn) for jn in base_joints]
    q_addrs = [int(model.jnt_qposadr[jid]) for jid in joint_ids]
    
    axis_map = []
    for i, name in enumerate(base_joints):
        data.qpos[:] = 0.0
        data.qpos[q_addrs[i]] = 0.1
        mujoco.mj_forward(model, data)
        T_pert = read_world_body_T(model, data, base_id)
        R_pert = T_pert[:3,:3]
        
        # Axis in Zero-Base Frame
        R_diff = R_base_0.T @ R_pert
        rvec = R.from_matrix(R_diff).as_rotvec()
        if np.linalg.norm(rvec) < 1e-6:
             print(f"    WARNING: No motion detected for {name}. Assuming Z.")
             axis = np.array([0., 0., 1.])
        else:
             axis = rvec / np.linalg.norm(rvec)
        axis_map.append(axis)

    # 3. Permutation (Order)
    test_vals = [0.3, 0.5, -0.4]
    data.qpos[:] = 0.0
    for i in range(3): data.qpos[q_addrs[i]] = test_vals[i]
    mujoco.mj_forward(model, data)
    
    T_target = read_world_body_T(model, data, base_id)
    R_target_rel = R_base_0.T @ T_target[:3,:3]

    import itertools
    best_perm = None
    min_err = 1e9
    
    for p in list(itertools.permutations([0,1,2])):
        # Construct R = R[p0] * R[p1] * R[p2]
        mats = []
        for idx in p:
            ax = axis_map[idx]; theta = test_vals[idx]
            ux, uy, uz = ax; c = np.cos(theta); s = np.sin(theta)
            mats.append(np.array([
                [c + ux*ux*(1-c),      ux*uy*(1-c) - uz*s, ux*uz*(1-c) + uy*s],
                [uy*ux*(1-c) + uz*s,   c + uy*uy*(1-c),    uy*uz*(1-c) - ux*s],
                [uz*ux*(1-c) - uy*s,   uz*uy*(1-c) + ux*s, c + uz*uz*(1-c)]
            ]))
        R_hyp = mats[0] @ mats[1] @ mats[2]
        err = np.linalg.norm(R_hyp - R_target_rel)
        if err < min_err:
            min_err = err
            best_perm = p

    print(f"    Base Match: Permutation {best_perm} (Err: {min_err:.2e})")
    
    return {
        "R_base_0": R_base_0.tolist(),
        "axes": [a.tolist() for a in axis_map],
        "order": best_perm 
    }

def main():
    if not os.path.exists(XML_PATH): raise FileNotFoundError(f"'{XML_PATH}' not found.")
    model = mujoco.MjModel.from_xml_path(XML_PATH)
    data = mujoco.MjData(model)

    print("Computing Kinematics Data...")
    
    # --- 1. Compute Chain Offsets (A Matrices) ---
    data.qpos[:] = 0.0
    mujoco.mj_forward(model, data)
    
    base_bid = safe_id(model, mujoco.mjtObj.mjOBJ_BODY, "base_link")
    joint_site_names = ["joint_1_site","joint_2_site","joint_3_site"]
    site_ids = [safe_id(model, mujoco.mjtObj.mjOBJ_SITE, s) for s in joint_site_names]
    ee_sid = safe_id(model, mujoco.mjtObj.mjOBJ_SITE, "end_effector_imu")
    
    Tworld_base0 = read_world_body_T(model, data, base_bid)
    Tbase_world0 = inv_homog(Tworld_base0)
    
    Tworld_sites0 = [read_world_site_T(model, data, sid) for sid in site_ids]
    Tworld_ee0 = read_world_site_T(model, data, ee_sid)
    
    # Calculate A matrices (Site-to-Site transforms)
    Tbase_sites0 = [Tbase_world0 @ Ts for Ts in Tworld_sites0]
    Tbase_ee0 = Tbase_world0 @ Tworld_ee0
    
    A01 = Tbase_sites0[0]
    A12 = inv_homog(Tbase_sites0[0]) @ Tbase_sites0[1]
    A23 = inv_homog(Tbase_sites0[1]) @ Tbase_sites0[2]
    A3E = inv_homog(Tbase_sites0[2]) @ Tbase_ee0
    
    # --- 2. Compute Corrected Joint Axes (In SITE Frames) ---
    gimbal_joints = ["joint_1_yaw","joint_2_pitch","joint_3_roll"]
    gimbal_axes = []
    
    for i, jn in enumerate(gimbal_joints):
        jid = safe_id(model, mujoco.mjtObj.mjOBJ_JOINT, jn)
        
        # --- FIXED ACCESS ---
        raw_axis_body = get_joint_axis(model, jid)
            
        # Get Body Rotation (Global)
        body_id = model.jnt_bodyid[jid]
        T_world_body = read_world_body_T(model, data, body_id)
        R_world_body = T_world_body[:3,:3]
        
        # Get Site Rotation (Global)
        sid = site_ids[i]
        T_world_site = read_world_site_T(model, data, sid)
        R_world_site = T_world_site[:3,:3]
        
        # Transform Axis: Body -> World -> Site
        axis_world = R_world_body @ raw_axis_body
        axis_site = R_world_site.T @ axis_world
        
        # Normalize
        norm = np.linalg.norm(axis_site)
        if norm > 1e-9:
             axis_site = axis_site / norm
        else:
             print(f"WARNING: Zero axis for {jn} after transform")
        
        print(f"  Joint {jn}:")
        print(f"    Raw (Body): {raw_axis_body}")
        print(f"    Adj (Site): {np.round(axis_site, 4)}")
        
        gimbal_axes.append(axis_site.tolist())

    # --- 3. Base Kinematics ---
    base_kin = solve_base_kinematics(model, data)
    
    export_data = {
        "A01": A01.tolist(),
        "A12": A12.tolist(),
        "A23": A23.tolist(),
        "A3E": A3E.tolist(),
        "gimbal_axes": gimbal_axes,
        "base_info": base_kin
    }

    with open(JSON_OUTPUT, 'w') as f:
        json.dump(export_data, f, indent=4)
    
    print(f"Data saved to {JSON_OUTPUT}")

if __name__ == "__main__":
    main()