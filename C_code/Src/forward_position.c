#include "forward_position.h"
#include <math.h>

void fast_fk(double base_roll, double base_pitch, double base_yaw, 
             double q1, double q2, double q3, 
             double *ee_roll, double *ee_pitch, double *ee_yaw) {

    // Optimized Intermediate Variables (Auto-Generated via SymPy)
    double tmp_0 = sin(base_yaw);
    double tmp_1 = cos(base_pitch);
    double tmp_2 = cos(q3);
    double tmp_3 = sin(q2);
    double tmp_4 = 0.96606771244047496*tmp_3;
    double tmp_5 = cos(q2);
    double tmp_6 = 0.24952460252270092*tmp_5 - 0.24952460252270092;
    double tmp_7 = sin(q3);
    double tmp_8 = 1.0*tmp_7;
    double tmp_9 = -tmp_2*tmp_4 - tmp_6*tmp_8;
    double tmp_10 = sin(base_pitch);
    double tmp_11 = sin(q1);
    double tmp_12 = cos(q1);
    double tmp_13 = 0.25828893700665478*tmp_3;
    double tmp_14 = tmp_12*tmp_13;
    double tmp_15 = -1.0*tmp_11*tmp_5 - tmp_14;
    double tmp_16 = tmp_11*tmp_13;
    double tmp_17 = 0.066713174980027823*tmp_5 + 0.93328682501997218;
    double tmp_18 = tmp_12*tmp_17 - tmp_16;
    double tmp_19 = 1.0*tmp_15*tmp_2 - tmp_18*tmp_8;
    double tmp_20 = cos(base_yaw);
    double tmp_21 = 1.0*tmp_12*tmp_5 - tmp_16;
    double tmp_22 = tmp_11*tmp_17 + tmp_14;
    double tmp_23 = 1.0*tmp_2*tmp_21 - tmp_22*tmp_8;
    double tmp_24 = sin(base_roll);
    double tmp_25 = tmp_20*tmp_24;
    double tmp_26 = cos(base_roll);
    double tmp_27 = tmp_0*tmp_26;
    double tmp_28 = tmp_1*tmp_19;
    double tmp_29 = -tmp_0*tmp_10*tmp_24 + tmp_20*tmp_26;
    double tmp_30 = tmp_10*tmp_25 + tmp_27;
    double tmp_31 = 1.0*tmp_6;
    double tmp_32 = tmp_1*tmp_24;
    double tmp_33 = 1.0*tmp_2;

    // Rotation Matrix Elements
    double r11 = tmp_0*tmp_1*tmp_9 - tmp_1*tmp_20*tmp_23 - tmp_10*tmp_19;
    double r21 = tmp_23*(tmp_0*tmp_24 - tmp_10*tmp_20*tmp_26) + tmp_26*tmp_28 + tmp_9*(tmp_10*tmp_27 + tmp_25);
    double r31 = tmp_23*tmp_30 - tmp_24*tmp_28 + tmp_29*tmp_9;
    double r32 = tmp_29*(0.93328682501997229*tmp_5 + 0.066713174980027684) + tmp_30*(tmp_11*tmp_31 + tmp_12*tmp_4) - tmp_32*(-tmp_11*tmp_4 + tmp_12*tmp_31);
    double r33 = tmp_29*(tmp_33*tmp_6 - tmp_4*tmp_7) + tmp_30*(tmp_21*tmp_8 + tmp_22*tmp_33) - tmp_32*(tmp_15*tmp_8 + tmp_18*tmp_33);

    // Final RPY Extraction
    *ee_pitch = asin(-r31);
    
    // Check for Gimbal Lock (Singularity at +/- 90 degrees pitch)
    if (fabs(*ee_pitch) >= 1.5707) {
        *ee_roll = 0.0;
        *ee_yaw = 0.0; // In lock, roll/yaw are coupled; zeroing one solves the other
    } else {
        *ee_roll = atan2(r32, r33);
        *ee_yaw  = atan2(r21, r11);
    }
}