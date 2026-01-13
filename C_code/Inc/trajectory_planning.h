#ifndef TRAJECTORY_PLANNING_H
#define TRAJECTORY_PLANNING_H

// ==========================================
// TRAJECTORY GENERATOR (Minimum Jerk)
// ==========================================
// This generates a smooth path from start_val to end_val over 'duration' seconds.
void generate_trajectory(
    double t,              // Current time
    double duration,       // Total movement time
    double start_val,      // Starting position
    double end_val,        // Target position
    double *pos_out,       // Output: Desired Position
    double *vel_out,       // Output: Desired Velocity
    double *acc_out        // Output: Desired Acceleration
);

#endif