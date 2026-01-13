import mujoco
import mujoco.viewer
import subprocess
import struct
import numpy as np
import time
import os
import sys
import threading
from ui_control import SharedControl, run_ui

# --- Configuration ---
XML_PATH = 'gimbal_2.xml'
C_EXECUTABLE = "C_code_2/main.exe"

# --- Validation ---
if not os.path.exists(XML_PATH):
    print(f"Error: XML file '{XML_PATH}' not found.")
    sys.exit(1)
if not os.path.exists(C_EXECUTABLE):
    print(f"Error: C executable '{C_EXECUTABLE}' not found.")
    sys.exit(1)

def simulation_thread_func(shared_data):
    print("[SimThread] Launching C Controller...")
    try:
        process = subprocess.Popen(
            C_EXECUTABLE,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=sys.stderr,
            bufsize=0
        )
    except Exception as e:
        print(f"[SimThread] Failed to launch C executable: {e}")
        return

    model = mujoco.MjModel.from_xml_path(XML_PATH)
    data = mujoco.MjData(model)

    # Gains
    gain_lambda = 15.0
    gain_k = 25.0
    gain_pos = 1.0
    
    # Formats
    fmt_in = 'd' * 61 
    fmt_out = 'd' * 15
    calc_size_out = struct.calcsize(fmt_out)

    print("[SimThread] Starting Viewer...")
    
    with mujoco.viewer.launch_passive(model, data) as viewer:
        while viewer.is_running() and shared_data.running:
            step_start = time.time()

            # --- 1. UPDATE SHARED MEASUREMENTS (For UI Display) ---
            # XML Base Pos: [0, 1, 2]
            # XML Base Rot: [3, 4, 5]
            # XML Joints:   [6, 7, 8]
            
            # Use 'with' or just assignment (lists are thread-safe enough for floats here)
            shared_data.meas_base_pos[0] = data.qpos[0]
            shared_data.meas_base_pos[1] = data.qpos[1]
            shared_data.meas_base_pos[2] = data.qpos[2]
            
            shared_data.meas_base_ori[0] = data.qpos[3]
            shared_data.meas_base_ori[1] = data.qpos[4]
            shared_data.meas_base_ori[2] = data.qpos[5]
            
            shared_data.meas_joints[0] = data.qpos[6]
            shared_data.meas_joints[1] = data.qpos[7]
            shared_data.meas_joints[2] = data.qpos[8]

            # --- 2. PREPARE PACKET FOR C CODE ---
            pack_list = []
            
            # A. Gains (18 doubles)
            pack_list.extend([gain_lambda] * 9)
            pack_list.extend([gain_k] * 9)
            
            # B. Command (Desired Position) (9 doubles)
            # *** FIX: ORDER MUST BE [JOINTS, ORI, POS] TO MATCH C CODE LOGIC ***
            pack_list.extend(shared_data.joints)    # Indices 0,1,2 in C
            pack_list.extend(shared_data.base_ori)  # Indices 3,4,5 in C
            pack_list.extend(shared_data.base_pos)  # Indices 6,7,8 in C
            
            # C. Command Velocity (9 doubles)
            pack_list.extend([0.0] * 9)
            
            # D. Current State (Order doesn't matter as long as mapped to struct fields correctly)
            # However, looking at your C struct packing in previous turns, it expects:
            # q(3), q_dot(3), base_pos(3), base_vel(3), base_acc(3), base_ori(3), base_dori(3), base_ddori(3)
            
            # q (Gimbal Joints)
            pack_list.extend(data.qpos[6:9])
            pack_list.extend(data.qvel[6:9])
            
            # base_pos
            pack_list.extend(data.qpos[0:3])
            pack_list.extend(data.qvel[0:3])
            pack_list.extend(data.qacc[0:3] if hasattr(data, 'qacc') else [0,0,0])
            
            # base_ori
            pack_list.extend(data.qpos[3:6])
            pack_list.extend(data.qvel[3:6])
            pack_list.extend([0,0,0])
            
            # Gain Pos Error
            pack_list.append(gain_pos)

            # --- 3. COMMUNICATION ---
            try:
                packed_data = struct.pack(fmt_in, *pack_list)
                process.stdin.write(packed_data)
                process.stdin.flush()
                
                raw_output = process.stdout.read(calc_size_out)
                if raw_output:
                    unpacked = struct.unpack(fmt_out, raw_output)
                    torques = unpacked[0:9]
                    
                    # --- 4. APPLY CONTROL ---
                    # C Code Output Order: [Joints, Ori, Pos]
                    # MuJoCo Actuator Order: [Joints, Ori, Pos]
                    # Direct mapping is correct here.
                    for i in range(9):
                        data.ctrl[i] = torques[i]
                        
            except Exception as e:
                print(f"[SimThread] Comms Error: {e}")
                break

            # --- 5. STEP PHYSICS ---
            mujoco.mj_step(model, data)
            viewer.sync()

            # --- 6. TIMING ---
            time_until_next = model.opt.timestep - (time.time() - step_start)
            if time_until_next > 0:
                time.sleep(time_until_next)

    process.terminate()
    print("[SimThread] Finished.")

if __name__ == "__main__":
    shared = SharedControl()
    
    sim_thread = threading.Thread(target=simulation_thread_func, args=(shared,))
    sim_thread.start()
    
    print("Starting UI...")
    run_ui(shared)
    
    sim_thread.join()