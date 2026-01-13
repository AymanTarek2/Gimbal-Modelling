#include "backstepping.h"
#include <string.h> // For memset
#include <math.h>   // For fmod, fabs, M_PI

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ==========================================
// Helper Math Functions (Internal Use)
// ==========================================

// Normalize angle difference to [-PI, PI]
// This ensures the controller takes the shortest path
static double normalize_angle_diff(double diff) {
    // Wrap to [-PI, PI] range
    while (diff > M_PI)  diff -= 2.0 * M_PI;
    while (diff < -M_PI) diff += 2.0 * M_PI;
    return diff;
}

// Subtract two vectors: out = a - b
static void vec_sub(const Vector3 a, const Vector3 b, Vector3 out) {
    for(int i = 0; i < DOF; i++) {
        out[i] = a[i] - b[i];
    }
}

// Specialized subtraction for angles: out = Normalize(a - b)
static void vec_sub_angular(const Vector3 a, const Vector3 b, Vector3 out) {
    for(int i = 0; i < DOF; i++) {
        double diff = a[i] - b[i];
        out[i] = normalize_angle_diff(diff);
    }
}

// Multiply 3x3 Matrix by Vector: out = M * v
static void mat_vec_mult(const Matrix3x3 M, const Vector3 v, Vector3 out) {
    for(int i = 0; i < DOF; i++) {
        out[i] = 0.0;
        for(int j = 0; j < DOF; j++) {
            out[i] += M[i][j] * v[j];
        }
    }
}

// ==========================================
// Main Backstepping Logic
// ==========================================

void compute_backstepping_control(
    const Vector3 current_x,
    const Vector3 current_xi,
    const TrajectoryPoint desired,
    const Matrix3x3 M,
    const Matrix3x3 C,
    const Vector3 G,
    const ControlGains gains,
    double e_gain, 
    Vector3 u_output,
    // Debug Output Pointers
    Vector3 debug_M_term,
    Vector3 debug_C_term,
    Vector3 debug_G_term,
    Vector3 debug_e_term,
    Vector3 debug_K_term
) {
    Vector3 e, Lambda_e;
    Vector3 phi, z;
    Vector3 e_dot, Lambda_e_dot, phi_dot;
    Vector3 term_M_phidot, term_C_phi, term_K_z;
    
    // 1. Position Error (e) with ANGULAR WRAPPING
    // Instead of simple subtraction, we normalize the difference to [-PI, PI]
    // This makes the controller choose the "shortest path"
    vec_sub_angular(current_x, desired.x_d, e);

    // 2. Virtual Control (phi)
    mat_vec_mult(gains.Lambda, e, Lambda_e);
    vec_sub(desired.dx_d, Lambda_e, phi);

    // 3. Velocity Error (z)
    // Note: No angular wrapping needed here; velocity differences are linear
    vec_sub(current_xi, phi, z);

    // 4. Phi_dot
    // Note: e_dot is technically velocity error (x_dot - x_d_dot), not d/dt(e_pos)
    // for standard backstepping formulation unless x_d is constant.
    // Assuming standard tracking, this subtraction is correct without wrapping.
    vec_sub(current_xi, desired.dx_d, e_dot);
    mat_vec_mult(gains.Lambda, e_dot, Lambda_e_dot);
    vec_sub(desired.ddx_d, Lambda_e_dot, phi_dot);

    // 5. Control Input Terms
    mat_vec_mult(M, phi_dot, term_M_phidot);
    mat_vec_mult(C, phi, term_C_phi);
    mat_vec_mult(gains.K, z, term_K_z);
    
    // 6. Summation & Scaling
    for(int i = 0; i < DOF; i++) {
        // Calculate the scaled E term using the passed gain
        double scaled_e = e_gain * e[i];

        // Sum: M*phi_dot + C*phi + G - e_scaled - K*z
        u_output[i] = term_M_phidot[i]
                    + term_C_phi[i]
                    + G[i]
                    - scaled_e
                    - term_K_z[i];

        // --- Populate Debug Outputs ---
        if(debug_M_term) debug_M_term[i] = term_M_phidot[i];
        if(debug_C_term) debug_C_term[i] = term_C_phi[i];
        if(debug_G_term) debug_G_term[i] = G[i];
        if(debug_e_term) debug_e_term[i] = scaled_e;
        if(debug_K_term) debug_K_term[i] = term_K_z[i];
    }
}