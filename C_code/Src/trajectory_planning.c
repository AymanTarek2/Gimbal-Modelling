#include "trajectory_planning.h"
#include <math.h>

void generate_trajectory(
    double t,              // Current time
    double duration,       // Total movement time
    double start_val,      // Starting position
    double end_val,        // Target position
    double *pos_out,       // Output: Desired Position
    double *vel_out,       // Output: Desired Velocity
    double *acc_out        // Output: Desired Acceleration
) {
    // If time is past duration, stay at the end
    if (t >= duration) {
        *pos_out = end_val;
        *vel_out = 0.0;
        *acc_out = 0.0;
        return;
    }
    
    // Normalized time (0.0 to 1.0)
    double tau = t / duration;
    
    // Quintic Polynomial (Minimum Jerk Trajectory)
    // s(tau) = 10*tau^3 - 15*tau^4 + 6*tau^5
    
    // Coefficients for Position
    double s = 10*pow(tau,3) - 15*pow(tau,4) + 6*pow(tau,5);
    
    // Derivative for Velocity (scaled by 1/duration)
    double s_dot = 30*pow(tau,2) - 60*pow(tau,3) + 30*pow(tau,4);
    
    // Derivative for Acceleration (scaled by 1/duration^2)
    double s_ddot = 60*tau - 180*pow(tau,2) + 120*pow(tau,3);
    
    double dist = end_val - start_val;
    
    *pos_out = start_val + dist * s;
    *vel_out = (dist * s_dot) / duration;
    *acc_out = (dist * s_ddot) / (duration * duration);
}