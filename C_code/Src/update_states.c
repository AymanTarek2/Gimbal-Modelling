#include "update_states.h"
#include <stdio.h>
#include <string.h> // For memset/memcpy

// ==========================================
// Internal Helper: 3x3 Matrix Inversion
// ==========================================
static int invert_matrix3x3(const Matrix3x3 m, Matrix3x3 invOut) {
    double det;
    
    // Calculate Cofactors
    double c00 =  (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
    double c01 = -(m[1][0] * m[2][2] - m[1][2] * m[2][0]);
    double c02 =  (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    
    double c10 = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]);
    double c11 =  (m[0][0] * m[2][2] - m[0][2] * m[2][0]);
    double c12 = -(m[0][0] * m[2][1] - m[0][1] * m[2][0]);
    
    double c20 =  (m[0][1] * m[1][2] - m[0][2] * m[1][1]);
    double c21 = -(m[0][0] * m[1][2] - m[0][2] * m[1][0]);
    double c22 =  (m[0][0] * m[1][1] - m[0][1] * m[1][0]);

    // Calculate Determinant
    det = m[0][0] * c00 + m[0][1] * c01 + m[0][2] * c02;

    if (det == 0.0) return 0; // Singular matrix

    double invDet = 1.0 / det;

    // Adjugate / Determinant
    invOut[0][0] = c00 * invDet; invOut[0][1] = c10 * invDet; invOut[0][2] = c20 * invDet;
    invOut[1][0] = c01 * invDet; invOut[1][1] = c11 * invDet; invOut[1][2] = c21 * invDet;
    invOut[2][0] = c02 * invDet; invOut[2][1] = c12 * invDet; invOut[2][2] = c22 * invDet;
    
    return 1;
}

// ==========================================
// Internal Helper: Compute Derivatives (Dynamics)
// ==========================================
// Calculates: d(State)/dt
// Output dx: returns current velocity (xi)
// Output dxi: returns acceleration (M_inv * (u - C*xi - G))
static void compute_derivatives(
    const Vector3 xi_in,         // Current velocity for this RK step
    const Vector3 u_applied,
    const Matrix3x3 M_inv,       // Pre-inverted Mass matrix
    const Matrix3x3 C,
    const Vector3 G,
    Vector3 dx_out,              // Output: Velocity (derivative of pos)
    Vector3 dxi_out              // Output: Acceleration (derivative of vel)
) {
    Vector3 C_xi;
    Vector3 net_force;

    // 1. dx/dt = velocity (xi)
    for(int i=0; i<3; i++) dx_out[i] = xi_in[i];

    // 2. Calculate C * xi
    for(int i=0; i<3; i++) {
        C_xi[i] = 0;
        for(int j=0; j<3; j++) {
            C_xi[i] += C[i][j] * xi_in[j];
        }
    }

    // 3. Calculate Net Force (u - C*xi - G)
    for(int i=0; i<3; i++) {
        net_force[i] = u_applied[i] - C_xi[i] - G[i];
    }

    // 4. Calculate Acceleration (M_inv * net_force)
    for(int i=0; i<3; i++) {
        dxi_out[i] = 0;
        for(int j=0; j<3; j++) {
            dxi_out[i] += M_inv[i][j] * net_force[j];
        }
    }
}

// ==========================================
// Main Update Function (Runge-Kutta 4)
// ==========================================
void update_robot_states(
    Vector3 current_x,
    Vector3 current_xi,
    const Vector3 u_applied,
    const Matrix3x3 M,
    const Matrix3x3 C,
    const Vector3 G,
    double dt,
    Vector3 acc_out
) {
    Matrix3x3 M_inv;
    
    // Invert Mass Matrix once at the start
    if(!invert_matrix3x3(M, M_inv)) {
        printf("Error: Singular Mass Matrix!\n");
        return;
    }

    // RK4 staging variables (same types as before)
    Vector3 k1_x, k1_xi;
    Vector3 k2_x, k2_xi;
    Vector3 k3_x, k3_xi;
    Vector3 k4_x, k4_xi;
    Vector3 temp_xi;

    // ---------- Sub-stepping policy (no headers changed) ----------
    const double MAX_SUBSTEP_DT = 0.0001; // tweak if needed
    const int MAX_SUBSTEPS = 50000;


    int n_substeps = 1;
    if (dt > MAX_SUBSTEP_DT) {
        n_substeps = (int)(dt / MAX_SUBSTEP_DT);
        if ((double)n_substeps * MAX_SUBSTEP_DT < dt) n_substeps += 1;
        if (n_substeps > MAX_SUBSTEPS) n_substeps = MAX_SUBSTEPS;
    }


    double sub_dt = dt / (double)n_substeps;

    // Perform n_substeps of RK4 with sub_dt (keeps API unchanged)
    for (int s = 0; s < n_substeps; ++s) {
        // Step 1 (K1): derivatives at current velocity
        compute_derivatives(current_xi, u_applied, M_inv, C, G, k1_x, k1_xi);

        // Step 2 (K2): midpoint using k1
        for (int i = 0; i < 3; ++i) temp_xi[i] = current_xi[i] + (0.5 * sub_dt * k1_xi[i]);
        compute_derivatives(temp_xi, u_applied, M_inv, C, G, k2_x, k2_xi);

        // Step 3 (K3): midpoint using k2
        for (int i = 0; i < 3; ++i) temp_xi[i] = current_xi[i] + (0.5 * sub_dt * k2_xi[i]);
        compute_derivatives(temp_xi, u_applied, M_inv, C, G, k3_x, k3_xi);

        // Step 4 (K4): end using k3
        for (int i = 0; i < 3; ++i) temp_xi[i] = current_xi[i] + (sub_dt * k3_xi[i]);
        compute_derivatives(temp_xi, u_applied, M_inv, C, G, k4_x, k4_xi);

        // Final weighted update for this sub-step (same formula, with sub_dt)
        for (int i = 0; i < 3; ++i) {
            current_x[i]  += (sub_dt / 6.0) * (k1_x[i] + 2.0*k2_x[i] + 2.0*k3_x[i] + k4_x[i]);
            current_xi[i] += (sub_dt / 6.0) * (k1_xi[i] + 2.0*k2_xi[i] + 2.0*k3_xi[i] + k4_xi[i]);
        }
    }
}