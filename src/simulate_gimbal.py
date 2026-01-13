import mujoco
import mujoco.viewer
import time
import os
import numpy as np
import subprocess
import struct
import sys
import math

GAIN_LAMBDA  = [100, 100, 100]
GAIN_K = [0.06, 0.06, 0.02]
GAIN_POS_ERR = 1

XML_PATH = "gimbal.xml"
C_EXECUTABLE = "C_code/main.exe" 

# 37 doubles (RPY sent)
STATE_FMT = '37d'
STATE_SIZE = struct.calcsize(STATE_FMT)
CONTROL_FMT = '15d'
CONTROL_SIZE = struct.calcsize(CONTROL_FMT)

def quat2rpy(q):
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
        return data.sensordata[adr:adr+dim]
    except: return None

def main():
    if not os.path.exists(XML_PATH): raise FileNotFoundError(f"Error: '{XML_PATH}' not found.")
    if not os.path.exists(C_EXECUTABLE): raise FileNotFoundError(f"Error: '{C_EXECUTABLE}' not found.")
        
    print(f"Launching C Controller ({C_EXECUTABLE})...")
    process = subprocess.Popen([C_EXECUTABLE], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=sys.stdout, bufsize=0)

    model = mujoco.MjModel.from_xml_path(XML_PATH)
    model.opt.timestep = 0.002
    data = mujoco.MjData(model)

    with mujoco.viewer.launch_passive(model, data) as viewer:
        while viewer.is_running():
            step_start = time.time()

            q_meas = [get_sensor_data(model, data, 'gimbal_yaw_pos')[0], get_sensor_data(model, data, 'gimbal_pitch_pos')[0], get_sensor_data(model, data, 'gimbal_roll_pos')[0]]
            q_dot_meas = [get_sensor_data(model, data, 'gimbal_yaw_vel')[0], get_sensor_data(model, data, 'gimbal_pitch_vel')[0], get_sensor_data(model, data, 'gimbal_roll_vel')[0]]
            b_pos = [get_sensor_data(model, data, f'base_{axis}_pos')[0] for axis in ['x', 'y', 'z']]
            b_vel = [get_sensor_data(model, data, f'base_{axis}_vel')[0] for axis in ['x', 'y', 'z']]
            b_ori = [get_sensor_data(model, data, f'base_{axis}_pos')[0] for axis in ['roll', 'pitch', 'yaw']]
            b_dori = [get_sensor_data(model, data, f'base_{axis}_vel')[0] for axis in ['roll', 'pitch', 'yaw']]
            b_acc = get_sensor_data(model, data, 'base_lin_acc')
            b_ddori = get_sensor_data(model, data, 'base_ang_acc')
            ee_vel_global = get_sensor_data(model, data, 'ee_vel')
            if ee_vel_global is None: ee_vel_global = [0.0, 0.0, 0.0]

            ee_quat = get_sensor_data(model, data, 'ee_quat')
            if ee_quat is None: ee_quat = [1.0, 0.0, 0.0, 0.0]
            ee_rpy = quat2rpy(ee_quat) 

            packed_data = struct.pack(STATE_FMT,
                *q_meas, *q_dot_meas,
                *b_pos, *b_vel, *b_acc, *b_ori, *b_dori, *b_ddori,
                *ee_rpy, *ee_vel_global, 
                *GAIN_LAMBDA, *GAIN_K, GAIN_POS_ERR
            )

            try:
                process.stdin.write(packed_data)
                process.stdin.flush()
                response_data = process.stdout.read(CONTROL_SIZE)
                if not response_data: break
                unpacked_ctrl = struct.unpack(CONTROL_FMT, response_data)
                data.ctrl[0] = unpacked_ctrl[0]
                data.ctrl[1] = unpacked_ctrl[1]
                data.ctrl[2] = unpacked_ctrl[2]
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