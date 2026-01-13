/*
 * forward_position.h
 * Optimized Symbolic Forward Kinematics for Gimbal
 */

#ifndef FORWARD_POSITION_H
#define FORWARD_POSITION_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculates the End-Effector Orientation (Roll, Pitch, Yaw)
 * using optimized symbolic math (CSE).
 * * @param base_roll   Base roll in radians
 * @param base_pitch  Base pitch in radians
 * @param base_yaw    Base yaw in radians
 * @param q1          Joint 1 angle in radians
 * @param q2          Joint 2 angle in radians
 * @param q3          Joint 3 angle in radians
 * @param ee_roll     [Output] End-effector roll in radians
 * @param ee_pitch    [Output] End-effector pitch in radians
 * @param ee_yaw      [Output] End-effector yaw in radians
 */
void fast_fk(double base_roll, double base_pitch, double base_yaw, 
             double q1, double q2, double q3, 
             double *ee_roll, double *ee_pitch, double *ee_yaw);

#ifdef __cplusplus
}
#endif

#endif // FORWARD_POSITION_H