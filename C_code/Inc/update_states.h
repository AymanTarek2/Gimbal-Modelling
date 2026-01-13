#ifndef UPDATE_STATES_H
#define UPDATE_STATES_H

// Ensure types are defined. 
// If these are defined in another header included before this one, 
// the compiler might complain about redefinition depending on the environment.
// Ideally, these typedefs should be in a shared "types.h".
typedef double Vector3[3];
typedef double Matrix3x3[3][3];

// Updated prototype with acc_out parameter
void update_robot_states(
    Vector3 current_x,
    Vector3 current_xi,
    const Vector3 u_applied,
    const Matrix3x3 M,
    const Matrix3x3 C,
    const Vector3 G,
    double dt,
    Vector3 acc_out // Output parameter for acceleration
);

#endif