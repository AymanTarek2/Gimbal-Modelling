# Canted-Axis Gimbal: Modeling, Backstepping Control & MuJoCo Simulation

A 3-axis camera/sensor gimbal with a non-orthogonal (canted) joint axis, fully modeled from first principles — Euler-Lagrange dynamics, analytic forward/inverse kinematics, a Lyapunov-based backstepping controller, and a hierarchical safety supervisor — then validated in MuJoCo simulation and built as physical hardware.

Originally developed for coursework at the **German University in Cairo (GUC)**, Mechatronics Engineering Department, and extended into the conference paper *"Modeling and Backstepping Stabilization of a Canted-Axis Gimbal on a 6-DoF Moving Base."*

**The 3D model (SolidWorks) was designed entirely from scratch for this project** — not sourced from GrabCAD or any existing part library.

---

## Simulation Demo



https://github.com/user-attachments/assets/064867ab-5779-4ba0-b793-b17383601b43



*MuJoCo simulation of the gimbal tracking a commanded trajectory, with real-time torque computed by the compiled C backstepping controller and fed back into the physics engine.*

## Hardware



<img width="1280" height="890" alt="gimbal" src="https://github.com/user-attachments/assets/c5d95ed4-f445-4a3d-9534-7a8296ecc399" />





The physical build: a 3D-printed frame carrying three brushless gimbal motors in a cascaded ring arrangement (yaw → pitch → roll), with the pitch axis canted 15° off-orthogonal relative to the roll axis — the geometric feature that makes this system's kinematics and dynamics meaningfully harder than a standard orthogonal 3-axis gimbal.

---

## Why a Canted Axis

Most academic gimbal-control projects simplify the problem to 2 axes with orthogonal joints, which decouples the dynamics and avoids several hard cases. This project deliberately keeps the full 3-axis system **and** a non-orthogonal joint: there is a fixed 15° structural tilt (α) about the local x-axis between the roll and pitch joints. That single design choice:

- couples axes that would otherwise be independent, so the mass, Coriolis, and gravity terms in the equations of motion don't simplify away,
- moves the kinematic singularities to different, less-intuitive configurations than a standard gimbal lock,
- means the inverse kinematics can't be solved with the textbook orthogonal-gimbal formulas and had to be re-derived for this specific geometry.

---

## Modeling

### Kinematics (`src/forward_kinematics.py`, `src/inverse_pos.py`, `C_code/dh_matrices_kinematics_corrected.tex`)

- Standard Denavit-Hartenberg (DH) parameters describe the 3-joint chain, with the structural tilt baked into the link twist angles (α₁ = +75°, α₂ = −75°, equivalent to the 15° canted offset between stages).
- Forward kinematics is built symbolically in SymPy: chained homogeneous transforms `T0_1`, `T0_2`, `T0_3` give end-effector position and a yaw-pitch-roll (Z-Y-X) orientation extracted via `atan2` expressions.
- The velocity Jacobian is assembled column-by-column from each joint's z-axis and the standard linear/angular velocity propagation, then used to derive a least-squares pseudoinverse (`J⁺ = (JᵀJ)⁻¹Jᵀ`) for inverse velocity kinematics.
- **Inverse position kinematics is solved analytically**, not numerically: q2 is recovered from the `r33` element of the rotation matrix via a half-angle substitution, q1 from a combination of the `r13`/`r23` elements, and q3 by projecting the desired orientation through the partially-solved chain. All of this is exported to LaTeX (`dh_matrices_kinematics_corrected.tex`) so the full derivation is checkable by hand.
- Measured geometric parameters used throughout: link lengths l₁ = 0.0882 m, l₂ = 0.1355 m, with each link's center-of-mass offset measured separately (see Table I in the paper).

### Dynamics (`src/lagrangian_modelling.py`, `src/automate_modelling.py` / `_2.py`)

- Full Euler-Lagrange derivation: each link's kinetic energy is built from its linear Jacobian (`Jv`), angular Jacobian (`Jw`), mass, and the full 3×3 inertia tensor rotated into the base frame; potential energy comes from each center-of-mass height under gravity.
- The mass matrix **M(q)**, Coriolis/centripetal matrix **C(q,q̇)** (via symbolic Christoffel symbols), and gravity vector **G(q)** are all derived symbolically in SymPy — nothing is hand-linearized or approximated.
- Two model variants exist:
  - **`C_code/`** — the base 3-DOF model (gimbal joints only, fixed base).
  - **`C_code_2/`** — the extended **9-DOF model**: the 3 gimbal joints plus the moving base's 6 degrees of freedom (3 translation + 3 rotation), matching the paper's "gimbal on a 6-DoF moving base" framing. Real platforms (drones, vehicles) move under the gimbal, so the controller has to know the base's dynamics too, not just the gimbal's.
- Because the symbolic mass/Coriolis matrices for the 9-DOF case are large, each individual matrix entry (`M[i][j]`, `C[i][j]`, `G[i]`) is auto-generated into its own small C file (`automated_dynamics/M/calculate_M_i_j.c`, etc.) rather than one massive function — this keeps compile times and embedded memory footprint manageable on a microcontroller.

### Base State Estimation (`C_code/Src/base_estimation.c`)

Because the gimbal sits on a moving platform, the controller needs the platform's own orientation and velocity — but those aren't directly measured. Instead, an IMU (MPU6050) on the gimbal's end-effector gives the *absolute* end-effector orientation and velocity, and the base state is solved backward through the kinematic chain:

- the gimbal's own joint chain orientation is built as a quaternion product `Q_chain = Q1 · Q2 · Q3`,
- the base orientation is recovered via `Q_base = Q_mount⁻¹ · Q_ee · Q_chain⁻¹`, accounting for a fixed mounting-orientation offset between the base and the first gimbal joint,
- base angular velocity is recovered by computing the chain's own contribution to end-effector velocity (via the joint axes and joint rates, rotated into the global frame) and subtracting it from the measured end-effector velocity.

This means the gimbal can infer how its moving base is rotating using only sensors already on the gimbal itself, without needing a separate IMU on the base/vehicle.

---

## Control

### Lyapunov-Based Backstepping (`C_code/Src/backstepping.c`, `C_code_2/Src/backstepping_2.c`)

The controller is derived using backstepping, a recursive Lyapunov-based design method that gives a mathematical stability guarantee rather than just empirically-tuned gains:

1. **Position error** `e = q − q_d`, with angle wrapping to `[−π, π]` so the controller always takes the shortest rotational path.
2. **Virtual control / desired velocity** `φ = q̇_d − Λe` — instead of tracking position error directly, the controller defines a "desired velocity" that would drive the error to zero if perfectly followed.
3. **Velocity (sliding) error** `z = q̇ − φ` — how far the actual velocity is from that virtual target.
4. **Final control law**: `τ = M(q)φ̇ + C(q,q̇)φ + G(q) − Kₚe − K_d z`, which exactly cancels the system's own mass/Coriolis/gravity nonlinearities (computed from the symbolic dynamics above) and adds proportional-derivative-style correction on the transformed errors.

This control law is proven (in the accompanying paper) to make a Lyapunov function `V` strictly decrease, which guarantees the tracking error converges to zero — not just "tuned to look stable."

The 3-DOF version (`C_code/`) controls the gimbal joints alone; the 9-DOF version (`C_code_2/`) applies the identical structure across all 9 states (3 gimbal joints + 6 base DOF) using full 9×9 gain matrices.

### Discrete-Event Supervisor

A finite state machine sits above the continuous backstepping controller to handle safety and mode switching:
- **Idle** — actuators disabled, the commanded position is continuously set equal to the current position so there's no sudden jump when control is re-enabled.
- **Run** — active tracking; the inverse-kinematics-generated reference is passed straight to the controller, while the supervisor watches the magnitude of the reference change to detect approach to a kinematic singularity.
- (Additional states handle current-limit/fault conditions — see the paper for the full FSM.)

### Trajectory Generation (`C_code/Src/trajectory_planning.c`)

Point-to-point moves use a quintic (5th-order) minimum-jerk polynomial, `s(τ) = 10τ³ − 15τ⁴ + 6τ⁵`, so position, velocity, *and* acceleration all start and end at the correct values with no discontinuities — avoiding the jerky step-like motion a simple linear ramp would produce.

### Reinforcement-Learning Gain Tuning (`src/train_sac_gimbal.py`)

Rather than hand-tuning the backstepping gain matrices Λ and K, a Soft Actor-Critic (SAC) agent is trained directly against the MuJoCo simulation: the action space is the 18 gain values (9 Λ + 9 K), the observation is the 9-DOF position and velocity error, and the reward penalizes tracking error, velocity error, and control effort. This treats gain-tuning itself as a learnable control problem rather than manual trial-and-error.

### Low-Level Actuation

The backstepping controller's torque output is the setpoint for the brushless motors. Since BLDC torque is approximately proportional to current (`τ ≈ Kₜ·I`), the torque command is converted to a desired current and closed with a PI current-control loop. In hardware, an **ESP32** acts as the low-level abstraction layer, interfacing with the **Electronic Speed Controllers (ESCs)** driving the three **BLDC** gimbal motors, and aggregating IMU data from the **MPU6050**.

---

## MuJoCo Simulation (`src/control_mujoco.py`, `src/simulate_gimbal.py` / `_2.py`)

The simulation loop does **not** reimplement the controller in Python — it calls the actual compiled C controller (`main.exe`) as a subprocess and exchanges state/control data with it over `stdin`/`stdout` using packed binary structs (Python's `struct` module), so the exact same control code that would run on embedded hardware is what's being tested in simulation:

1. MuJoCo steps the physics and exposes the current joint/base state (`qpos`, `qvel`).
2. That state, plus the desired setpoint and gain matrices, is packed into a binary buffer and piped to the C executable's `stdin`.
3. The C controller computes `M`, `C`, `G` from the measured state, runs the backstepping law, and writes the resulting 9 joint torques back over `stdout`.
4. Python unpacks the torques, applies them as `data.ctrl[:]`, and steps the simulation forward.

A separate live UI (`src/ui_control.py`) lets the desired base position/orientation and joint angles be adjusted in real time via a `SharedControl` object read by the simulation thread, so setpoints can be changed interactively while watching the response in the MuJoCo viewer.

---

## Repository Structure

```
canted-axis-gimbal-stabilization/
├── src/                              # Python: modeling, kinematics, simulation, RL
│   ├── lagrangian_modelling.py       #   Symbolic Euler-Lagrange dynamics (M, C, G)
│   ├── forward_kinematics.py         #   DH-based FK, Jacobian, analytic IK derivation
│   ├── inverse_pos.py                #   Inverse position kinematics solver
│   ├── automate_modelling.py/_2.py   #   Auto-generates the per-entry C dynamics files
│   ├── control_mujoco.py             #   MuJoCo + compiled C-controller live simulation
│   ├── simulate_gimbal.py/_2.py      #   Simulation entry points (3-DOF / 9-DOF)
│   ├── train_sac_gimbal.py           #   RL (SAC) backstepping gain auto-tuning
│   ├── ui_control.py                 #   Live setpoint UI for the simulation
│   ├── model_visualizer.py           #   Kinematic chain visualization
│   └── ...                           #   Additional kinematics/debug utilities
├── C_code/                           # 3-DOF embedded controller (gimbal joints only)
│   ├── Src/backstepping.c            #   Lyapunov backstepping control law
│   ├── Src/base_estimation.c         #   Quaternion-based base state estimator
│   ├── Src/trajectory_planning.c     #   Quintic minimum-jerk trajectory generator
│   ├── Src/dynamics_c/               #   Auto-generated symbolic M, C, G entries
│   └── dh_matrices_kinematics_corrected.tex  # Full symbolic FK/IK derivation
├── C_code_2/                         # 9-DOF embedded controller (gimbal + moving base)
│   ├── Src/backstepping_2.c          #   9-DOF backstepping control law
│   ├── Src/automated_dynamics/       #   Auto-generated 9×9 M, C and 9×1 G entries
│   └── Src/main.c                    #   Binary stdin/stdout control loop entry point
└── docs/
    ├── Gimbal-Report.pdf             # Full conference-style paper
    └── media/
        └── hardware_gimbal.png       # Physical build photo
```

---

## Hardware Summary

| Component | Role |
|---|---|
| 3× Brushless DC (BLDC) gimbal motor | Direct-drive actuation for yaw, pitch, roll |
| 3× Electronic Speed Controller (ESC) | Motor current/torque drive, commanded by ESP32 |
| ESP32 | Low-level hardware abstraction: runs the control loop output, drives the ESCs |
| MPU6050 IMU | Mounted at the end-effector; measures absolute orientation/velocity, used to back-estimate base motion |
| 3D-printed frame (custom SolidWorks design) | Structural housing with the 15° canted pitch/roll joint offset |

---

## Running the Simulation

The C controller is compiled to `main.exe` (Windows) and launched as a subprocess by the Python simulation — both `C_code/run.bat` and `C_code_2/run.bat` show the build command if you need to recompile from source.

```bash
pip install mujoco numpy sympy stable-baselines3 gymnasium
cd src
python control_mujoco.py        # live MuJoCo simulation driven by the compiled C controller
# or
python train_sac_gimbal.py      # train an SAC agent to tune the backstepping gains
```

To regenerate the symbolic dynamics or kinematics derivations from scratch:

```bash
python lagrangian_modelling.py   # derives M(q), C(q,q̇), G(q) and exports to LaTeX
python forward_kinematics.py     # derives FK, Jacobian, and analytic IK, exports to LaTeX
```

---

## Paper

The full methodology, stability proof, geometric parameter table, and simulation results (static stabilization and dynamic trajectory tracking under base disturbance) are documented in [`docs/Gimbal-Report.pdf`](docs/Gimbal-Report.pdf) — *"Modeling and Backstepping Stabilization of a Canted-Axis Gimbal on a 6-DoF Moving Base."*

**Authors:** Ayman M. Tarek, Youssef Greiss, Ahmed Amr El Otefy, Adam Mohamed, Marwan Ashraf, Bassel Mahran — Mechatronics Engineering Department, German University in Cairo.
