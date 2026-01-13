#include "inverse_position.h"
#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define RAD2DEG(x) ((x) * 180.0 / M_PI)

// Constants
static const double J2_uy = 0.2582889370066548;
static const double J2_uz = -0.966067712440475;
static const double K1 = 0.06671317498; 
static const double K2 = 0.93328682502; 

// Normalize Angle to [-180, 180]
static double normalize_angle_deg(double angle) {
    while (angle > 180.0)  angle -= 360.0;
    while (angle < -180.0) angle += 360.0;
    return angle;
}

// Helper: Quat to Rotation Matrix
static void quat_to_rot(const double q[4], double R[3][3]) {
    double w=q[0], x=q[1], y=q[2], z=q[3];
    double xx=x*x, yy=y*y, zz=z*z;
    double xy=x*y, xz=x*z, yz=y*z;
    double wx=w*x, wy=w*y, wz=w*z;

    R[0][0] = 1-2*(yy+zz); R[0][1] = 2*(xy-wz);   R[0][2] = 2*(xz+wy);
    R[1][0] = 2*(xy+wz);   R[1][1] = 1-2*(xx+zz); R[1][2] = 2*(yz-wx);
    R[2][0] = 2*(xz-wy);   R[2][1] = 2*(yz+wx);   R[2][2] = 1-2*(xx+yy);
}

int inverse_position_kinematics_quat(
    const double base_quat[4], 
    const double target_quat[4], 
    double *q1_deg, double *q2_deg, double *q3_deg)
{
    // 1. Convert Quaternions to Matrices
    double R_base_raw[3][3], R_tgt[3][3];
    quat_to_rot(base_quat, R_base_raw);
    quat_to_rot(target_quat, R_tgt);

    // 2. Apply Mount Offset Correctly
    // The Forward Kinematics is: T_ee = T_base_0 * R_base * T_chain
    // So R_total_base = R_mount * R_base_raw
    // R_mount = [[-1, 0, 0], [0, 0, 1], [0, 1, 0]]
    //
    // Matrix Multiplication (Row * Matrix):
    // Row 0 = [-1, 0, 0] * R_base_raw = -Row0(R_base_raw)
    // Row 1 = [ 0, 0, 1] * R_base_raw =  Row2(R_base_raw)
    // Row 2 = [ 0, 1, 0] * R_base_raw =  Row1(R_base_raw)
    
    double R_base[3][3];
    // Row 0 = -Row 0 of Raw
    R_base[0][0] = -R_base_raw[0][0]; R_base[0][1] = -R_base_raw[0][1]; R_base[0][2] = -R_base_raw[0][2];
    // Row 1 = Row 2 of Raw
    R_base[1][0] =  R_base_raw[2][0]; R_base[1][1] =  R_base_raw[2][1]; R_base[1][2] =  R_base_raw[2][2];
    // Row 2 = Row 1 of Raw
    R_base[2][0] =  R_base_raw[1][0]; R_base[2][1] =  R_base_raw[1][1]; R_base[2][2] =  R_base_raw[1][2];

    // 3. Compute Relative Rotation: R_loc = R_base^T * R_tgt
    // This finds the rotation the chain must provide
    double R_loc[3][3];
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            R_loc[i][j] = 0.0;
            for(int k=0; k<3; k++) {
                R_loc[i][j] += R_base[k][i] * R_tgt[k][j]; // Transpose multiply
            }
        }
    }

    // 4. Analytical Solution (Derived for Y -> Canted -> Y chain)
    
    // Step A: Solve q2
    // R22 = K1 + K2*cos(q2) -> cos(q2) = (R22 - K1)/K2
    double val = (R_loc[1][1] - K1) / K2;
    
    // Clamp for numerical safety
    if (val > 1.0) val = 1.0; 
    if (val < -1.0) val = -1.0;
    
    double q2_rad = acos(val);
    // acos returns [0, pi]. This assumes the "positive" elbow solution.
    *q2_deg = RAD2DEG(q2_rad);

    // Step B: Solve q1
    double c2 = cos(q2_rad);
    double s2 = sin(q2_rad);
    
    double v_x = -J2_uz * s2;
    double v_z = J2_uy * J2_uz * (1.0 - c2);
    
    double w_x = R_loc[0][1];
    double w_z = R_loc[2][1];

    double q1_rad = atan2(w_x, w_z) - atan2(v_x, v_z);
    *q1_deg = normalize_angle_deg(RAD2DEG(q1_rad));

    // Step C: Solve q3
    double c1 = cos(q1_rad);
    double s1 = sin(q1_rad);
    
    // Un-rotate by q1
    double t00 = c1 * R_loc[0][0] - s1 * R_loc[2][0];
    double t10 = R_loc[1][0];
    double t20 = s1 * R_loc[0][0] + c1 * R_loc[2][0];

    // Un-rotate by q2 (canted)
    double rem00 = c2*t00 + (J2_uz*s2)*t10 - (J2_uy*s2)*t20;
    
    double r21_inv = J2_uz*J2_uy*(1.0-c2);
    double r22_inv = c2 + J2_uz*J2_uz*(1.0-c2);
    double rem20 = (J2_uy*s2)*t00 + r21_inv*t10 + r22_inv*t20;

    double q3_rad = atan2(-rem20, rem00);
    *q3_deg = normalize_angle_deg(RAD2DEG(q3_rad));

    return 0;
}