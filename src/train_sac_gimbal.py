import gymnasium as gym
import numpy as np
import struct
import subprocess
import os
import sys
import math
import time
from gymnasium import spaces
from stable_baselines3 import SAC
import mujoco
import mujoco.viewer  # <--- Moved here to prevent UnboundLocalError

# --- CONFIGURATION ---
XML_PATH = "gimbal_2.xml"
C_EXECUTABLE = "C_code_2/main.exe"

# Packing Formats (Must match C struct)
STATE_FMT = '67d'
STATE_SIZE = struct.calcsize(STATE_FMT)
CONTROL_FMT = '15d'
CONTROL_SIZE = struct.calcsize(CONTROL_FMT)

# --- DESIRED TARGETS ---
CMD_Q_JOINTS = [0.0, 0.0, 0.0]
CMD_Q_BASE_ORI = [0.0, 0.0, 0.0]
CMD_Q_BASE_POS = [0.0, 0.0, 1.0]

CMD_Q_DES = np.array(CMD_Q_JOINTS + CMD_Q_BASE_ORI + CMD_Q_BASE_POS, dtype=np.float64)
CMD_DQ_DES = np.zeros(9, dtype=np.float64)
GAIN_POS_ERR = 1.0

# --- HELPER FUNCTIONS ---
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

class GimbalEnv(gym.Env):
    metadata = {'render_modes': ['human']}

    def __init__(self, render_mode=None):
        super(GimbalEnv, self).__init__()
        
        # Action: 18 continuous values (9 Lambdas + 9 Ks)
        self.action_space = spaces.Box(low=-1.0, high=1.0, shape=(18,), dtype=np.float32)

        # Observation: 18 values (Pos Error + Vel Error)
        self.observation_space = spaces.Box(low=-np.inf, high=np.inf, shape=(18,), dtype=np.float32)

        self.render_mode = render_mode
        self.process = None
        
        # Mujoco Setup
        self.model = mujoco.MjModel.from_xml_path(XML_PATH)
        self.data = mujoco.MjData(self.model)
        self.model.opt.timestep = 0.002
        
        self.viewer = None
        if self.render_mode == 'human':
            # Removed the local import here that caused the crash
            self.viewer = mujoco.viewer.launch_passive(self.model, self.data)

        self.steps = 0
        self.max_steps = 500
        self.current_torques = np.zeros(9)

    def _get_sensor_data(self, name):
        try:
            id = mujoco.mj_name2id(self.model, mujoco.mjtObj.mjOBJ_SENSOR, name)
            if id == -1: return None
            adr = self.model.sensor_adr[id]
            dim = self.model.sensor_dim[id]
            return self.data.sensordata[adr:adr+dim].copy()
        except:
            return None

    def reset(self, seed=None, options=None):
        super().reset(seed=seed)
        
        mujoco.mj_resetData(self.model, self.data)
        self.data.qpos[:3] += np.random.uniform(-0.1, 0.1, 3) 
        
        if self.process:
            self.process.terminate()
            try: self.process.wait(timeout=0.1)
            except: self.process.kill()
                
        self.process = subprocess.Popen([C_EXECUTABLE], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, bufsize=0)
        
        self.steps = 0
        self.current_torques = np.zeros(9)
        return self._get_obs(), {}

    def _get_obs(self):
        def get_scalar(name):
            val = self._get_sensor_data(name)
            return val[0] if val is not None else 0.0

        q_j = [get_scalar('gimbal_yaw_pos'), get_scalar('gimbal_pitch_pos'), get_scalar('gimbal_roll_pos')]
        dq_j = [get_scalar('gimbal_yaw_vel'), get_scalar('gimbal_pitch_vel'), get_scalar('gimbal_roll_vel')]
        
        base_ori = [get_scalar(f'base_{axis}_pos') for axis in ['roll', 'pitch', 'yaw']]
        base_dori = [get_scalar(f'base_{axis}_vel') for axis in ['roll', 'pitch', 'yaw']]
        
        base_pos = [get_scalar(f'base_{axis}_pos') for axis in ['x', 'y', 'z']]
        base_vel = [get_scalar(f'base_{axis}_vel') for axis in ['x', 'y', 'z']]

        current_q = np.array(q_j + base_ori + base_pos)
        current_dq = np.array(dq_j + base_dori + base_vel)

        error_q = current_q - CMD_Q_DES
        error_dq = current_dq - CMD_DQ_DES
        
        return np.concatenate([error_q, error_dq]).astype(np.float32)

    def step(self, action):
        # 1. Map Actions to Gains
        gain_lambda = (action[:9] + 1.0) * 225.0 + 50.0
        gain_k = (action[9:] + 1.0) * 0.05 
        
        # 2. Read Sensors
        def get_val(name, default_arr):
            val = self._get_sensor_data(name)
            return val if val is not None else np.array(default_arr)

        q_meas = [get_val('gimbal_yaw_pos', [0])[0], get_val('gimbal_pitch_pos', [0])[0], get_val('gimbal_roll_pos', [0])[0]]
        q_dot_meas = [get_val('gimbal_yaw_vel', [0])[0], get_val('gimbal_pitch_vel', [0])[0], get_val('gimbal_roll_vel', [0])[0]]
        
        b_pos = [get_val(f'base_{axis}_pos', [0])[0] for axis in ['x', 'y', 'z']]
        b_vel = [get_val(f'base_{axis}_vel', [0])[0] for axis in ['x', 'y', 'z']]
        b_ori = [get_val(f'base_{axis}_pos', [0])[0] for axis in ['roll', 'pitch', 'yaw']]
        b_dori = [get_val(f'base_{axis}_vel', [0])[0] for axis in ['roll', 'pitch', 'yaw']]
        
        b_acc = get_val('base_lin_acc', [0.0, 0.0, 0.0])
        b_ddori = get_val('base_ang_acc', [0.0, 0.0, 0.0])
        
        ee_vel = get_val('ee_vel', [0.0, 0.0, 0.0])
        ee_quat = get_val('ee_quat', [1.0, 0.0, 0.0, 0.0])
        ee_rpy = quat2rpy(ee_quat)

        # 3. Communicate
        try:
            packed_data = struct.pack(STATE_FMT,
                *q_meas, *q_dot_meas,
                *b_pos, *b_vel, *b_acc, *b_ori, *b_dori, *b_ddori,
                *ee_rpy, *ee_vel,
                *CMD_Q_DES, *CMD_DQ_DES, 
                *gain_lambda, *gain_k, GAIN_POS_ERR
            )
            
            self.process.stdin.write(packed_data)
            self.process.stdin.flush()
            
            response_data = self.process.stdout.read(CONTROL_SIZE)
            
            if response_data:
                unpacked_ctrl = struct.unpack(CONTROL_FMT, response_data)
                self.current_torques = np.array(unpacked_ctrl[:9]) 
                clipped_torques = np.clip(self.current_torques, -150.0, 150.0)
                
                for i in range(min(len(self.data.ctrl), 9)):
                    self.data.ctrl[i] = clipped_torques[i]
        except Exception:
            return self._get_obs(), -500.0, True, False, {}

        # 4. Physics Step
        try:
            mujoco.mj_step(self.model, self.data)
        except Exception:
            return self._get_obs(), -500.0, True, False, {}

        if self.viewer:
            self.viewer.sync()

        # 5. Reward
        obs = self._get_obs()
        pos_error = obs[:9]
        vel_error = obs[9:]
        
        mse = np.mean(np.square(pos_error))
        reward = -mse * 50.0
        
        vel_penalty = np.mean(np.square(vel_error))
        reward -= 0.1 * vel_penalty

        torque_penalty = np.mean(np.square(self.current_torques))
        reward -= 0.001 * torque_penalty 
        reward -= 0.01 * np.mean(np.square(action))

        self.steps += 1
        terminated = False
        truncated = False

        if np.isnan(obs).any() or np.max(np.abs(pos_error)) > 10.0:
            return obs, -500.0, True, False, {}

        if mse < 1e-4:
            reward += 100.0 
            terminated = True
            print(f"Goal Reached! MSE: {mse:.6f}")
        
        if self.steps >= self.max_steps:
            truncated = True

        return obs, reward, terminated, truncated, {}

    def close(self):
        if self.process: self.process.terminate()
        if self.viewer: self.viewer.close()

if __name__ == "__main__":
    if not os.path.exists(XML_PATH): raise FileNotFoundError(f"Error: '{XML_PATH}' not found.")
    if not os.path.exists(C_EXECUTABLE): raise FileNotFoundError(f"Error: '{C_EXECUTABLE}' not found.")

    env = GimbalEnv(render_mode='human') 
    model = SAC("MlpPolicy", env, verbose=1, learning_rate=3e-4)

    print("Starting Training...")
    try:
        model.learn(total_timesteps=100000, log_interval=4)
        model.save("sac_gimbal_v2")
        print("Training Finished.")
    except KeyboardInterrupt:
        print("Interrupted.")
    finally:
        env.close()