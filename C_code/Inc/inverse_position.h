#ifndef INVERSE_POSITION_H
#define INVERSE_POSITION_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inverse Kinematics using Quaternions.
 * Computes joint angles to align the End-Effector with a Target Orientation.
 * * @param base_quat   [Input] Base Orientation Quaternion [w, x, y, z]
 * @param target_quat [Input] Target EE Orientation Quaternion [w, x, y, z]
 * @param q1_deg      [Output] Joint 1 Angle (Degrees)
 * @param q2_deg      [Output] Joint 2 Angle (Degrees)
 * @param q3_deg      [Output] Joint 3 Angle (Degrees)
 * @return int        0 on Success
 */
int inverse_position_kinematics_quat(
    const double base_quat[4], 
    const double target_quat[4], 
    double *q1_deg, 
    double *q2_deg, 
    double *q3_deg
);

#ifdef __cplusplus
}
#endif

#endif