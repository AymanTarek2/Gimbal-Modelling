#include "backstepping_2.h"
#include <math.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Helper: Normalize angle to [-PI, PI]
static double normalize_angle(double angle) {
    while (angle > M_PI)  angle -= 2.0 * M_PI;
    while (angle <= -M_PI) angle += 2.0 * M_PI;
    return angle;
}

void compute_backstepping_control(
    const double current_q[DOF],
    const double current_dq[DOF],
    const double des_q[DOF],
    const double des_dq[DOF],
    const double des_ddq[DOF],
    double M[DOF][DOF],
    double C[DOF][DOF],
    double G[DOF],
    const ControlGains *gains,
    double pos_error_gain,
    double u_output[DOF]
) {
    double e[DOF];
    double Lambda_e[DOF];
    double phi[DOF];
    double z[DOF];
    double e_dot[DOF]; // Approximation: dq - des_dq
    double Lambda_edot[DOF];
    double phi_dot[DOF];
    
    // Intermediate terms for control law
    double M_phidot[DOF];
    double C_phi[DOF];
    double K_z[DOF];

    // 1. Error (e = q - q_d)
    for(int i=0; i<DOF; i++) {
        double diff = current_q[i] - des_q[i];
        
        // Apply angle wrapping ONLY to angular states
        // Indices 0,1,2 (Joints) and 3,4,5 (Base Orientation) are angular.
        // Indices 6,7,8 (Base Position) are linear.
        if (i < 6) {
            e[i] = normalize_angle(diff);
        } else {
            e[i] = diff;
        }
    }

    // 2. Virtual Control (phi = dq_d - Lambda*e)
    for(int i=0; i<DOF; i++) {
        Lambda_e[i] = 0.0;
        for(int j=0; j<DOF; j++) {
            Lambda_e[i] += gains->Lambda[i][j] * e[j];
        }
        phi[i] = des_dq[i] - Lambda_e[i];
    }

    // 3. Velocity Error (z = dq - phi)
    for(int i=0; i<DOF; i++) {
        z[i] = current_dq[i] - phi[i];
    }

    // 4. Time derivative of Virtual Control (phi_dot)
    // phi_dot = ddq_d - Lambda * e_dot
    // e_dot = dq - dq_d (Standard approximation)
    for(int i=0; i<DOF; i++) {
        e_dot[i] = current_dq[i] - des_dq[i]; 
    }

    for(int i=0; i<DOF; i++) {
        Lambda_edot[i] = 0.0;
        for(int j=0; j<DOF; j++) {
            Lambda_edot[i] += gains->Lambda[i][j] * e_dot[j];
        }
        phi_dot[i] = des_ddq[i] - Lambda_edot[i];
    }

    // 5. Compute Matrices Products
    // M * phi_dot
    for(int i=0; i<DOF; i++) {
        M_phidot[i] = 0.0;
        for(int j=0; j<DOF; j++) {
            M_phidot[i] += M[i][j] * phi_dot[j];
        }
    }

    // C * phi
    for(int i=0; i<DOF; i++) {
        C_phi[i] = 0.0;
        for(int j=0; j<DOF; j++) {
            C_phi[i] += C[i][j] * phi[j];
        }
    }

    // K * z
    for(int i=0; i<DOF; i++) {
        K_z[i] = 0.0;
        for(int j=0; j<DOF; j++) {
            K_z[i] += gains->K[i][j] * z[j];
        }
    }

    // 6. Final Control Law
    // u = M*phi_dot + C*phi + G - pos_error_gain*e - K*z
    for(int i=0; i<DOF; i++) {
        u_output[i] = M_phidot[i] 
                    + C_phi[i] 
                    + G[i] 
                    - (pos_error_gain * e[i]) 
                    - K_z[i];
    }
}