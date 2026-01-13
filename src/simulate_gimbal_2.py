import mujoco
import mujoco.viewer
import time
import os
import subprocess
import struct
import sys
import math
import numpy as np
import threading

# Import the UI module
import ui_control

# --- 9-DOF GAINS ---
GAIN_LAMBDA  = [100, 100, 100, 100, 100, 100, 100, 100, 100]
GAIN_K       = [0.4,  0.06,  0.025, 1.2, 1.2, 1.2, 20, 25, 20]
GAIN_POS_ERR = 1

XML_PATH = "gimbal_3.xml"
C_EXECUTABLE = "C_code_2/main.exe" 

# PACKING CONSTANTS
STATE_FMT = '67d' 
STATE_SIZE = struct.calcsize(STATE_FMT)
CONTROL_FMT = '15d'
CONTROL_SIZE = struct.calcsize(CONTROL_FMT)

# --- HELPER FUNCTIONS ---
def wrap_angle(angle):
    """Wraps an angle in radians to [-pi, pi]"""
    return (angle + math.pi) % (2 * math.pi) - math.pi

def quat2rpy(q):
    """Converts Quaternion [w, x, y, z] to Roll-Pitch-Yaw Euler angles"""
    w, x, y, z = q[0], q[1], q[2], q[3]
    sinp = 2.0 * (w * y - z * x)
    if abs(sinp) >= 1: pitch = math.copysign(math.pi / 2, sinp)
    else: pitch = math.asin(sinp)
    sinr_cosp = 2.0 * (w * x + y * z)
    cosr_cosp = 1.0 - 2.0 * (x * x + y * y)
    roll = math.atan2(sinr_cosp, cosr_cosp)
    siny_cosp = 2.0 * (w * z + x * y)
    cosy_cosp = 1.0 - 2.0 * (y * y + z * z)
    yaw = math.atan2(siny_cosp, cosy_cosp)
    return [roll, pitch, yaw]

def get_sensor_data(model, data, sensor_name):
    try:
        sensor_id = mujoco.mj_name2id(model, mujoco.mjtObj.mjOBJ_SENSOR, sensor_name)
        if sensor_id == -1: return None
        adr = model.sensor_adr[sensor_id]
        dim = model.sensor_dim[sensor_id]
        return data.sensordata[adr:adr+dim].copy()
    except: return None

# --- MAIN LOOP ---
def main():
    if not os.path.exists(XML_PATH): raise FileNotFoundError(f"Error: '{XML_PATH}' not found.")
    if not os.path.exists(C_EXECUTABLE): raise FileNotFoundError(f"Error: '{C_EXECUTABLE}' not found.")
        
    print(f"Launching C Controller ({C_EXECUTABLE})...")
    process = subprocess.Popen([C_EXECUTABLE], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=sys.stdout, bufsize=0)

    # --- UI SETUP ---
    shared_data = ui_control.SharedControl()
    ui_thread = threading.Thread(target=ui_control.run_ui, args=(shared_data,), daemon=True)
    ui_thread.start()

    model = mujoco.MjModel.from_xml_path(XML_PATH)
    model.opt.timestep = 0.002
    data = mujoco.MjData(model)

    with mujoco.viewer.launch_passive(model, data) as viewer:
        while viewer.is_running() and shared_data.running:
            step_start = time.time()

            # 1. READ SENSORS
            
            # Joints (Local)
            q_meas = [
                wrap_angle(get_sensor_data(model, data, 'gimbal_yaw_pos')[0]), 
                wrap_angle(get_sensor_data(model, data, 'gimbal_pitch_pos')[0]), 
                wrap_angle(get_sensor_data(model, data, 'gimbal_roll_pos')[0])
            ]
            
            q_dot_meas = [
                get_sensor_data(model, data, 'gimbal_yaw_vel')[0], 
                get_sensor_data(model, data, 'gimbal_pitch_vel')[0], 
                get_sensor_data(model, data, 'gimbal_roll_vel')[0]
            ]
            
            # Base Position (Local/Relative to start if defined that way)
            b_pos = [get_sensor_data(model, data, f'base_{axis}_pos')[0] for axis in ['x', 'y', 'z']]
            b_vel = [get_sensor_data(model, data, f'base_{axis}_vel')[0] for axis in ['x', 'y', 'z']]
            
            # --- LOCAL ORIENTATION ONLY ---
            # Reading direct joint angles. 
            b_ori = [
                wrap_angle(get_sensor_data(model, data, f'base_{axis}_pos')[0]) 
                for axis in ['roll', 'pitch', 'yaw']
            ]
                
            b_dori = [get_sensor_data(model, data, f'base_{axis}_vel')[0] for axis in ['roll', 'pitch', 'yaw']]

            # --- ACCELERATION (Local) ---
            b_acc_local = get_sensor_data(model, data, 'base_lin_acc_in_base')
            if b_acc_local is None:
                b_acc_local = get_sensor_data(model, data, 'base_lin_acc')
            
            if b_acc_local is None: b_acc = [0.0, 0.0, 0.0]
            else: b_acc = list(b_acc_local[:3])

            b_ddori_local = get_sensor_data(model, data, 'base_ang_acc_in_base')
            if b_ddori_local is None:
                b_ddori_local = get_sensor_data(model, data, 'base_ang_acc')
            
            if b_ddori_local is None: b_ddori = [0.0, 0.0, 0.0]
            else: b_ddori = list(b_ddori_local[:3])
            
            # End Effector (Global, as needed for IMU sim, but control target is likely local relative to base)
            raw_ee_vel = get_sensor_data(model, data, 'ee_linvel_in_base')
            if raw_ee_vel is None:
                raw_ee_vel = get_sensor_data(model, data, 'ee_vel')
            ee_vel = raw_ee_vel if raw_ee_vel is not None else [0.0, 0.0, 0.0]

            raw_ee_quat = get_sensor_data(model, data, 'ee_quat_in_base')
            if raw_ee_quat is None:
                raw_ee_quat = get_sensor_data(model, data, 'ee_quat')
            ee_quat = raw_ee_quat if raw_ee_quat is not None else [1.0, 0.0, 0.0, 0.0]

            ee_rpy = quat2rpy(ee_quat) 

            # --- UPDATE UI WITH MEASURED DATA ---
            shared_data.meas_joints = q_meas
            shared_data.meas_base_ori = b_ori
            shared_data.meas_base_pos = b_pos 
            # ------------------------------------

            # 2. GET TARGETS
            CMD_Q_DES = shared_data.joints + shared_data.base_ori + shared_data.base_pos
            CMD_DQ_DES = [0.0] * 9

            # 3. PACK AND SEND TO C
            packed_data = struct.pack(STATE_FMT,
                *q_meas, *q_dot_meas,
                *b_pos, *b_vel, *b_acc, *b_ori, *b_dori, *b_ddori,
                *ee_rpy, *ee_vel,
                *CMD_Q_DES, *CMD_DQ_DES, 
                *GAIN_LAMBDA, *GAIN_K, GAIN_POS_ERR
            )

            try:
                process.stdin.write(packed_data)
                process.stdin.flush()
                response_data = process.stdout.read(CONTROL_SIZE)
                if not response_data: break
                
                unpacked_ctrl = struct.unpack(CONTROL_FMT, response_data)
                
                for i in range(min(len(data.ctrl), 9)):
                    data.ctrl[i] = unpacked_ctrl[i]

            except Exception as e:
                print(f"Communication Error: {e}")
                break

            mujoco.mj_step(model, data)
            viewer.sync()
            
            time_until_next_step = model.opt.timestep - (time.time() - step_start)
            if time_until_next_step > 0: time.sleep(time_until_next_step)

    process.terminate()

if __name__ == "__main__":
    main()