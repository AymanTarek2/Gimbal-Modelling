#ifndef BASE_ESTIMATION_H
#define BASE_ESTIMATION_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Estimates Base Orientation (Quaternion) and Velocity.
 * Takes Quaternions as input (converted in main.c).
 */
void estimate_base_state(
    const double ee_quat[4], // [w, x, y, z]
    const double ee_vel[3],  
    const double q[3],       
    const double q_dot[3],   
    double base_quat[4],     // Output [w, x, y, z]
    double base_vel[3]       
);

#ifdef __cplusplus
}
#endif

#endif