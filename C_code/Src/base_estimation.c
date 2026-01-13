#include "base_estimation.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// --- Constants ---
static const double J2_uy = 0.2582889370066548;
static const double J2_uz = -0.966067712440475;

// --- Quaternion Helpers ---
static void quat_mult(const double q1[4], const double q2[4], double out[4]) {
    double w1=q1[0], x1=q1[1], y1=q1[2], z1=q1[3];
    double w2=q2[0], x2=q2[1], y2=q2[2], z2=q2[3];
    
    out[0] = w1*w2 - x1*x2 - y1*y2 - z1*z2;
    out[1] = w1*x2 + x1*w2 + y1*z2 - z1*y2;
    out[2] = w1*y2 - x1*z2 + y1*w2 + z1*x2;
    out[3] = w1*z2 + x1*y2 - y1*x2 + z1*w2;
}

static void quat_conj(const double q[4], double out[4]) {
    out[0] = q[0];
    out[1] = -q[1];
    out[2] = -q[2];
    out[3] = -q[3];
}

static void axis_ang_to_quat(double ux, double uy, double uz, double theta, double q[4]) {
    double half = 0.5 * theta;
    double s = sin(half);
    q[0] = cos(half);
    q[1] = ux * s;
    q[2] = uy * s;
    q[3] = uz * s;
}

static void quat_rot_vec(const double q[4], const double v[3], double out[3]) {
    double p[4] = {0, v[0], v[1], v[2]};
    double q_inv[4];
    quat_conj(q, q_inv);
    
    double t[4], res[4];
    quat_mult(q, p, t);
    quat_mult(t, q_inv, res);
    
    out[0] = res[1];
    out[1] = res[2];
    out[2] = res[3];
}

// --- MAIN ESTIMATOR ---
void estimate_base_state(
    const double ee_quat[4],
    const double ee_vel[3],  
    const double q[3],       
    const double q_dot[3],   
    double base_quat[4],      
    double base_vel[3]       
) {
    // 1. Construct Chain Quaternion: Q_chain = Q1 * Q2 * Q3
    double q1[4], q2[4], q3[4];
    axis_ang_to_quat(0, 1, 0, q[0], q1);
    axis_ang_to_quat(0, J2_uy, J2_uz, q[1], q2);
    axis_ang_to_quat(0, 1, 0, q[2], q3);

    double q_tmp[4], q_chain[4];
    quat_mult(q1, q2, q_tmp);
    quat_mult(q_tmp, q3, q_chain);

    // 2. Define Mount Quaternion
    // Corresponds to R_MOUNT = [[-1,0,0],[0,0,1],[0,1,0]]
    // Correct Quat: [0, 0, 0.70710678, 0.70710678]
    double q_mount[4] = {0.0, 0.0, 0.70710678118, 0.70710678118};

    // 3. Solve Base Orientation
    // Kinematic Chain: Q_ee = Q_mount * Q_base * Q_chain
    //
    // Wait, Standard Mobile Robotics: T_ee = T_base * T_mount * T_chain
    // If we assume T_base is World->DroneBody and T_mount is DroneBody->GimbalBase
    // Then Q_ee = Q_base * Q_mount * Q_chain
    //
    // To solve for Q_base:
    // Multiply right by Q_chain_inv:  Q_ee * Q_chain_inv = Q_base * Q_mount
    // Multiply right by Q_mount_inv:  Q_ee * Q_chain_inv * Q_mount_inv = Q_base
    //
    // HOWEVER, previous working Matrix math was: R_base = R_mount^T * R_ee * R_chain^T
    // This implies the chain was: R_ee = R_mount * R_base * R_chain (unlikely)
    // OR R_ee = R_mount * (R_base * R_chain) ??
    //
    // Let's stick strictly to the Matrix Order that worked:
    // R_base = R_mount^T * R_ee * R_chain^T
    //
    // Quaternion Equivalent:
    // Q_base = Q_mount_inv * Q_ee * Q_chain_inv
    
    double q_chain_inv[4], q_mount_inv[4];
    quat_conj(q_chain, q_chain_inv);
    quat_conj(q_mount, q_mount_inv);
    
    double q_step1[4];
    
    // Step 1: Q_mount_inv * Q_ee
    quat_mult(q_mount_inv, ee_quat, q_step1);
    
    // Step 2: Result * Q_chain_inv
    quat_mult(q_step1, q_chain_inv, base_quat);

    // Normalize
    double n = sqrt(base_quat[0]*base_quat[0] + base_quat[1]*base_quat[1] + 
                    base_quat[2]*base_quat[2] + base_quat[3]*base_quat[3]);
    
    if (n > 1e-6) {
        base_quat[0]/=n; base_quat[1]/=n; base_quat[2]/=n; base_quat[3]/=n;
    } else {
        base_quat[0]=1.0; base_quat[1]=0.0; base_quat[2]=0.0; base_quat[3]=0.0;
    }

    // 4. Solve Base Velocity
    // We need to subtract the chain velocity from the EE velocity.
    // But we must project the chain velocity into the global frame using the BASE orientation.
    // w_ee = w_base + R_base * R_mount * w_local
    
    // Calculate Q_total_base = Q_base * Q_mount
    // (This is the orientation of the frame where the chain actually starts)
    double q_total_base[4];
    quat_mult(base_quat, q_mount, q_total_base);

    // Calculate Chain Local Velocity components (in J0 frame)
    // J0 is the frame after the Mount rotation
    double ax2_loc[3] = {0, J2_uy, J2_uz};
    double ax3_loc[3] = {0, 1, 0};
    
    double v1[3] = {0, 1, 0}; // J1 Axis (Base Y)
    double v2[3], v3[3];
    
    // v2 = Q1 * ax2 * Q1'
    quat_rot_vec(q1, ax2_loc, v2);
    
    // v3 = (Q1*Q2) * ax3 * (Q1*Q2)'
    quat_mult(q1, q2, q_tmp);
    quat_rot_vec(q_tmp, ax3_loc, v3);
    
    // Sum velocities
    double w_local[3];
    for(int i=0; i<3; i++) {
        w_local[i] = v1[i]*q_dot[0] + v2[i]*q_dot[1] + v3[i]*q_dot[2];
    }
    
    // Rotate sum to Global Frame using Q_total_base
    double w_chain_global[3];
    quat_rot_vec(q_total_base, w_local, w_chain_global);
    
    // Final subtraction
    for(int i=0; i<3; i++) {
        base_vel[i] = ee_vel[i] - w_chain_global[i];
    }
}