#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#include <string.h>

// User headers
#include "communication_2.h"
#include "backstepping_2.h"
#include "model.h" // Provided by user (computes 9x9 M, C, G)

int main() {
    // --- 1. Setup Binary I/O (Windows specific) ---
    _setmode(_fileno(stdin), _O_BINARY);
    _setmode(_fileno(stdout), _O_BINARY);
    setvbuf(stdout, NULL, _IONBF, 0);

    // Variable Definitions
    RobotState state_in;
    ControlOutput ctrl_out;
    ControlGains gains;

    // Dynamics Storage
    double M[9][9];
    double C[9][9];
    double G[9];
    double tau_dummy[9]; // Output from compute_dynamics (unused here)

    // State Vectors (Order: Joint, BaseRot, BasePos)
    double curr_q[9];
    double curr_dq[9];
    double des_ddq[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // Assuming 0 acceleration target for regulation

    // Loop variables
    int i, j;

    // --- Main Control Loop ---
    while (read_robot_state(&state_in)) {
        
        // --- 1. Map Inputs to State Vectors ---
        // Protocol Order: Joints[3], BaseRot[3], BasePos[3]
        
        // Joints (Indices 0-2)
        curr_q[0]  = state_in.q_meas[0];
        curr_q[1]  = state_in.q_meas[1];
        curr_q[2]  = state_in.q_meas[2];
        
        curr_dq[0] = state_in.q_dot_meas[0];
        curr_dq[1] = state_in.q_dot_meas[1];
        curr_dq[2] = state_in.q_dot_meas[2];

        // Base Orientation (Indices 3-5)
        curr_q[3]  = state_in.b_ori[0];
        curr_q[4]  = state_in.b_ori[1];
        curr_q[5]  = state_in.b_ori[2];

        curr_dq[3] = state_in.b_dori[0];
        curr_dq[4] = state_in.b_dori[1];
        curr_dq[5] = state_in.b_dori[2];

        // Base Position (Indices 6-8)
        curr_q[6]  = state_in.b_pos[0];
        curr_q[7]  = state_in.b_pos[1];
        curr_q[8]  = state_in.b_pos[2];

        curr_dq[6] = state_in.b_vel[0];
        curr_dq[7] = state_in.b_vel[1];
        curr_dq[8] = state_in.b_vel[2];

        // --- 2. Setup Gains ---
        // Diagonal matrices construction
        for (i = 0; i < DOF; i++) {
            for (j = 0; j < DOF; j++) {
                gains.Lambda[i][j] = (i == j) ? state_in.gain_lambda[i] : 0.0;
                gains.K[i][j]      = (i == j) ? state_in.gain_k[i]      : 0.0;
            }
        }

        // --- 3. Compute Dynamics Matrices (M, C, G) ---
        // Note: Passing the RAW measured vectors as expected by model.c
        double dummy_joint_acc[3] = {0, 0, 0};
        
        compute_dynamics(
            state_in.q_meas,   state_in.q_dot_meas, dummy_joint_acc,
            state_in.b_pos,    state_in.b_vel,      state_in.b_acc,
            state_in.b_ori,    state_in.b_dori,     state_in.b_ddori,
            M, C, G, tau_dummy
        );

        // --- 4. Compute Control ---
        compute_backstepping_control(
            curr_q,
            curr_dq,
            state_in.cmd_q_des,
            state_in.cmd_dq_des,
            des_ddq,
            M, C, G,
            &gains,
            state_in.gain_pos_error,
            ctrl_out.torque
        );

        // --- 5. Pack & Send ---
        // Zero out debug/padding
        for (i = 0; i < 6; i++) {
            ctrl_out.debug[i] = 0.0;
        }

        write_control_output(&ctrl_out);
    }

    return 0;
}