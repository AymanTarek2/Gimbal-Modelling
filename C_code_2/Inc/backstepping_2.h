#ifndef BACKSTEPPING_2_H
#define BACKSTEPPING_2_H

#include "communication_2.h" // For DOF definition

typedef struct {
    double Lambda[DOF][DOF];
    double K[DOF][DOF];
} ControlGains;

void compute_backstepping_control(
    const double current_q[DOF],      // Current Position [Joints, Rot, Pos]
    const double current_dq[DOF],     // Current Velocity
    const double des_q[DOF],          // Desired Position
    const double des_dq[DOF],         // Desired Velocity
    const double des_ddq[DOF],        // Desired Acceleration (usually 0)
    double M[DOF][DOF],               // Mass Matrix
    double C[DOF][DOF],               // Coriolis Matrix
    double G[DOF],                    // Gravity Vector
    const ControlGains *gains,
    double pos_error_gain,
    double u_output[DOF]              // Output Control
);

#endif // BACKSTEPPING_2_H