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

# --- CONFIGURATION ---
XML_PATH = "gimbal_2.xml"
C_EXECUTABLE = "C_code_2/main.exe"
MODEL_PATH = "sac_gimbal_tuned" # The saved model file (without .zip)

STATE_FMT = '67d'
STATE_SIZE = struct.calcsize(STATE_FMT)
CONTROL_FMT = '15d'
CONTROL_SIZE = struct.calcsize(CONTROL_FMT)

# Targets used during training (Must match to be consistent)
CMD_Q_DES = np.array([0.0, 0.0, 0.0,  0.0, 0.0, 0.0,  0.0, 0.0, 1.0]) 
CMD_DQ_DES = np.array([0.0] * 9)
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
        self.action_space = spaces.Box(low=-1.0, high=1.0, shape=(18,), dtype=np.float32)
        self.observation_space = spaces.Box(low=-np.inf, high=np.inf, shape=(18,), dtype=np.float32)
        self.render_mode = render_mode
        self.process = None
        
        import mujoco
        self.model = mujoco.MjModel.from_xml_path(XML_PATH)
        self.data = mujoco.MjData(self.model)
        self.model.opt.timestep = 0.002
        
        self.viewer = None
        if self.render_mode == 'human':
            import mujoco.viewer
            self.viewer = mujoco.viewer.launch_passive(self.model, self.data)

        self.steps = 0
        self.max_steps = 1000 # Longer duration for testing

    def _get_sensor_data(self, name):
        import mujoco
        id = mujoco.mj_name2id(self.model, mujoco.mjtObj.mjOBJ_SENSOR, name)
        if id == -1: return np.zeros(1)
        adr = self.model.sensor_adr[id]
        dim = self.model.sensor_dim[id]
        return self.data.sensordata[adr:adr+dim].copy()

    def reset(self, seed=None, options=None):
        super().reset(seed=seed)
        import mujoco
        mujoco.mj_resetData(self.model, self.data)
        self.data.qpos[:3] += np.random.uniform(-0.05, 0.05, 3) 
        
        if self.process:
            self.process.terminate()
            try: self.process.wait(timeout=0.1)
            except: self.process.kill()
                
        self.process = subprocess.Popen([C_EXECUTABLE], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, bufsize=0)
        self.steps = 0
        return self._get_obs(), {}

    def _get_obs(self):
        q_j = [self._get_sensor_data('gimbal_yaw_pos')[0], self._get_sensor_data('gimbal_pitch_pos')[0], self._get_sensor_data('gimbal_roll_pos')[0]]
        dq_j = [self._get_sensor_data('gimbal_yaw_vel')[0], self._get_sensor_data('gimbal_pitch_vel')[0], self._get_sensor_data('gimbal_roll_vel')[0]]
        base_ori = [self._get_sensor_data(f'base_{axis}_pos')[0] for axis in ['roll', 'pitch', 'yaw']]
        base_dori = [self._get_sensor_data(f'base_{axis}_vel')[0] for axis in ['roll', 'pitch', 'yaw']]
        base_pos = [self._get_sensor_data(f'base_{axis}_pos')[0] for axis in ['x', 'y', 'z']]
        base_vel = [self._get_sensor_data(f'base_{axis}_vel')[0] for axis in ['x', 'y', 'z']]

        current_q = np.array(q_j + base_ori + base_pos)
        current_dq = np.array(dq_j + base_dori + base_vel)
        return np.concatenate([current_q - CMD_Q_DES, current_dq - CMD_DQ_DES]).astype(np.float32)

    def step(self, action):
        import mujoco
        
        # --- RECONSTRUCT GAINS FROM ACTION ---
        gain_lambda = (action[:9] + 1.0) * 50.0 + 5.0
        gain_k      = (action[9:] + 1.0) * 2.0 + 0.01
        
        q_meas = [self._get_sensor_data('gimbal_yaw_pos')[0], self._get_sensor_data('gimbal_pitch_pos')[0], self._get_sensor_data('gimbal_roll_pos')[0]]
        q_dot_meas = [self._get_sensor_data('gimbal_yaw_vel')[0], self._get_sensor_data('gimbal_pitch_vel')[0], self._get_sensor_data('gimbal_roll_vel')[0]]
        b_pos = [self._get_sensor_data(f'base_{axis}_pos')[0] for axis in ['x', 'y', 'z']]
        b_vel = [self._get_sensor_data(f'base_{axis}_vel')[0] for axis in ['x', 'y', 'z']]
        b_ori = [self._get_sensor_data(f'base_{axis}_pos')[0] for axis in ['roll', 'pitch', 'yaw']]
        b_dori = [self._get_sensor_data(f'base_{axis}_vel')[0] for axis in ['roll', 'pitch', 'yaw']]
        b_acc = self._get_sensor_data('base_lin_acc')
        b_ddori = self._get_sensor_data('base_ang_acc')
        
        raw_ee_vel = self._get_sensor_data('ee_vel')
        ee_vel = raw_ee_vel if len(raw_ee_vel)>0 else [0.0, 0.0, 0.0]
        raw_ee_quat = self._get_sensor_data('ee_quat')
        ee_quat = raw_ee_quat if len(raw_ee_quat)>0 else [1.0, 0.0, 0.0, 0.0]
        ee_rpy = quat2rpy(ee_quat)

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
                for i in range(min(len(self.data.ctrl), 9)):
                    self.data.ctrl[i] = np.clip(unpacked_ctrl[i], -100.0, 100.0)
        except Exception:
            pass

        mujoco.mj_step(self.model, self.data)
        if self.viewer: self.viewer.sync()

        return self._get_obs(), 0.0, False, False, {"lambda": gain_lambda, "k": gain_k}

    def close(self):
        if self.process: self.process.terminate()
        if self.viewer: self.viewer.close()

if __name__ == "__main__":
    if not os.path.exists(XML_PATH): raise FileNotFoundError(f"Error: '{XML_PATH}' not found.")
    if not os.path.exists(C_EXECUTABLE): raise FileNotFoundError(f"Error: '{C_EXECUTABLE}' not found.")

    # Load Model
    print(f"Loading model from {MODEL_PATH}...")
    model = SAC.load(MODEL_PATH)

    # Init Env
    env = GimbalEnv(render_mode='human')
    obs, _ = env.reset()

    print("\n--- TESTING OPTIMAL GAINS ---")
    try:
        for i in range(5000):
            action, _ = model.predict(obs, deterministic=True)
            obs, reward, done, truncated, info = env.step(action)
            
            # Print Gains every 50 steps
            if i % 50 == 0:
                L = info["lambda"]
                K = info["k"]
                print(f"\nStep {i}:")
                print(f"  > Joints  (0-2) | Lambda: [{L[0]:.1f}, {L[1]:.1f}, {L[2]:.1f}]  K: [{K[0]:.3f}, {K[1]:.3f}, {K[2]:.3f}]")
                print(f"  > BaseOri (3-5) | Lambda: [{L[3]:.1f}, {L[4]:.1f}, {L[5]:.1f}]  K: [{K[3]:.3f}, {K[4]:.3f}, {K[5]:.3f}]")
                print(f"  > BasePos (6-8) | Lambda: [{L[6]:.1f}, {L[7]:.1f}, {L[8]:.1f}]  K: [{K[6]:.3f}, {K[7]:.3f}, {K[8]:.3f}]")

            if done or truncated:
                obs, _ = env.reset()
                print("--- Resetting Environment ---")
                
            time.sleep(0.002) # Slow down slightly to match real-time better

    except KeyboardInterrupt:
        print("Stopping...")
    finally:
        env.close()