#ifndef FORWARD_VELOCITY_H
#define FORWARD_VELOCITY_H


// --- Data Structure for Output ---
typedef struct {
    double v_x;
    double v_y;
    double v_z;
    double w_x;
    double w_y;
    double w_z;
} CartesianVelocities;

// --- Function Prototype ---
void calculate_forward_velocity(
    double q1, double q2, double q3,       // Current Joint Angles (rad)
    double dq1, double dq2, double dq3,    // Current Joint Velocities (rad/s)
    CartesianVelocities* output            // Pointer to output struct
);

#endif // FORWARD_VELOCITY_H