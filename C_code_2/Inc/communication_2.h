#ifndef COMMUNICATION_2_H
#define COMMUNICATION_2_H

#define DOF 9

// Matches Python '67d' struct.pack
typedef struct {
    // --- SENSORS (30 doubles) ---
    double q_meas[3];
    double q_dot_meas[3];
    double b_pos[3];
    double b_vel[3];
    double b_acc[3];
    double b_ori[3];     // RPY
    double b_dori[3];    // Ang Vel
    double b_ddori[3];   // Ang Acc
    double ee_rpy[3];
    double ee_vel[3];

    // --- COMMANDS (18 doubles) ---
    double cmd_q_des[9];   // Order: [Joints(3), BaseOri(3), BasePos(3)]
    double cmd_dq_des[9];

    // --- GAINS (19 doubles) ---
    double gain_lambda[9];
    double gain_k[9];
    double gain_pos_error;

} RobotState;

// Matches Python '15d' struct.unpack
typedef struct {
    double torque[9]; // First 9 are control inputs
    double debug[6];  // Remaining 6 for padding/debug
} ControlOutput;

// Function Prototypes
int read_robot_state(RobotState *state);
void write_control_output(ControlOutput *out);

#endif // COMMUNICATION_2_H