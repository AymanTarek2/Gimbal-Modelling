#ifndef MODEL_H
#define MODEL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Computes Lagrangian Dynamics: M(q)ddq + C(q,dq)dq + G(q) = tau
 * * @param q           [Input] Joint positions [rad] (q1, q2, q3) -> q[0], q[1], q[2]
 * @param dq          [Input] Joint velocities [rad/s]
 * @param ddq         [Input] Joint accelerations [rad/s^2] (Used to compute Tau)
 * * @param base_pos    [Input] Base Position (x0, y0, z0)
 * @param base_vel    [Input] Base Linear Velocity (dx0, dy0, dz0)
 * @param base_acc    [Input] Base Linear Acceleration (ddx0, ddy0, ddz0)
 * * @param base_ori    [Input] Base Orientation Euler Angles (theta_x0, theta_y0, theta_z0)
 * @param base_dori   [Input] Base Orientation Velocity (dtheta_x0...)
 * @param base_ddori  [Input] Base Orientation Acceleration (ddtheta_x0...)
 * * @param L1          [Input] Link Length 1
 * @param L2          [Input] Link Length 2
 * * @param M           [Output] Mass Matrix (3x3)
 * @param C           [Output] Coriolis Matrix (3x3) Note: This is the matrix C, not vector c.
 * @param G           [Output] Gravity Vector (3x1)
 * @param tau         [Output] Calculated Torque Vector (3x1)
 */
void compute_dynamics(
    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    double L1, double L2,
    double M[3][3], double C[3][3], double G[3], double tau[3]
);

#ifdef __cplusplus
}
#endif

#endif // MODEL_H