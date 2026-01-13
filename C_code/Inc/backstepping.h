#ifndef BACKSTEPPING_H
#define BACKSTEPPING_H

#define DOF 3

// Type Definitions
typedef double Vector3[DOF];
typedef double Matrix3x3[DOF][DOF];

typedef struct {
    Matrix3x3 Lambda; // Position Control Gain Matrix
    Matrix3x3 K;      // Velocity/Damping Gain Matrix
} ControlGains;

typedef struct {
    Vector3 x_d;   // Desired Position
    Vector3 dx_d;  // Desired Velocity
    Vector3 ddx_d; // Desired Acceleration
} TrajectoryPoint;

// Function Prototype (Updated with e_gain argument)
void compute_backstepping_control(
    const Vector3 current_x,
    const Vector3 current_xi,
    const TrajectoryPoint desired,
    const Matrix3x3 M,
    const Matrix3x3 C,
    const Vector3 G,
    const ControlGains gains,
    double e_gain,  // <--- NEW ARGUMENT
    Vector3 u_output,
    // Debug Outputs for individual terms
    Vector3 debug_M_term,
    Vector3 debug_C_term,
    Vector3 debug_G_term,
    Vector3 debug_e_term,
    Vector3 debug_K_term
);

#endif