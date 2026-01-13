#ifndef INVERSE_VELOCITY_H
#define INVERSE_VELOCITY_H

#include "forward_velocity.h" // To reuse CartesianVelocities struct if needed

// We define a struct for the output (Joint Velocities)
typedef struct {
    double dq1;
    double dq2;
    double dq3;
} JointVelocities;

// The function prototype
void calculate_inverse_velocity(
    double q1, double q2, double q3,          // Current Joint Angles
    CartesianVelocities* input_vel,           // Input: End Effector Velocities
    JointVelocities* output_joint_vel         // Output: Joint Velocities
);

#endif // INVERSE_VELOCITY_H