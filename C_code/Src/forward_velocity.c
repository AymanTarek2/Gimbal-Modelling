#include "forward_velocity.h"
#include <math.h>

// --- Robot Physical Parameters ---
// L1 = 13.548, L2 = 9.637
#define LINK_L2 9.6370

// --- Pre-calculated Root Constants (4 decimal places) ---

// From J(1,1): (sqrt(2) + sqrt(6)) / 4
// (1.4142 + 2.4495) / 4 = 0.9659
#define K_SUM_ROOTS_DIV4  0.9659 

// From J(6,2): (-sqrt(2) + sqrt(6)) / 4
// (-1.4142 + 2.4495) / 4 = 0.2588
#define K_DIFF_ROOTS_DIV4 0.2588 

// From J(6,3): (sqrt(3) + 2) / 4
// (1.7321 + 2) / 4 = 0.9330
#define K_SQRT3_PLUS2_DIV4 0.9330

// From J(6,3): (2 - sqrt(3)) / 4
// (2 - 1.7321) / 4 = 0.0670
#define K_2_MINUS_SQRT3_DIV4 0.0670

// Combined Constant: L2 * ((sqrt(2) + sqrt(6)) / 4)
// 9.637 * 0.9659 = 9.3084
#define K_L2_SCALED  9.3084

void calculate_forward_velocity(
    double q1, double q2, double q3, 
    double dq1, double dq2, double dq3, 
    CartesianVelocities* output
) {
    // 1. Calculate Trigonometric primitives once
    double s1 = sin(q1);
    double c1 = cos(q1);
    double s2 = sin(q2);
    double c2 = cos(q2);
    // Note: q3 affects orientation position, but J_v3 and J_w3 in your model 
    // imply q3 doesn't drastically change the Jacobian structure shown.
    // Based on your LaTeX, J only depends on q1 and q2.

    // 2. Common Subexpressions (Temp variables)
    // These terms appear multiple times in the Jacobian
    
    // Term for J(4,3) and J(5,3): 0.25 * (1 - cos(q2))
    double term_orient_small = 0.25 * (1.0 - c2); 
    
    // Term for J(4,3) and J(5,3): -((sqrt(6)+sqrt(2))/4) * sin(q2)
    double term_orient_large = -1.0 * K_SUM_ROOTS_DIV4 * s2;

    // 3. Compute Jacobian * q_dot 
    // Formula: Output = Col1*dq1 + Col2*dq2 + Col3*dq3

    // --- Linear Velocity (v_x, v_y, v_z) ---
    
    // v_x = J(1,1)*dq1 + J(1,2)*dq2 + J(1,3)*dq3
    // J(1,1) = K_L2_SCALED * cos(q1)
    // J(1,2) = 0
    // J(1,3) = 0
    output->v_x = (K_L2_SCALED * c1) * dq1;

    // v_y = J(2,1)*dq1 + J(2,2)*dq2 + J(2,3)*dq3
    // J(2,1) = K_L2_SCALED * sin(q1)
    // J(2,2) = 0
    // J(2,3) = 0
    output->v_y = (K_L2_SCALED * s1) * dq1;

    // v_z = J(3,1)*dq1 + J(3,2)*dq2 + J(3,3)*dq3
    // All zeros in your LaTeX for Row 3
    output->v_z = 0.0;


    // --- Angular Velocity (w_x, w_y, w_z) ---

    // w_x (Row 4)
    // J(4,1) = 0
    // J(4,2) = K_SUM_ROOTS_DIV4 * sin(q1)
    // J(4,3) = sin(q1)*[0.25 - 0.25cos(q2)] + cos(q1)*[-term_large]
    // Simplified J(4,3) = s1 * term_orient_small + c1 * term_orient_large
    double J_42 = K_SUM_ROOTS_DIV4 * s1;
    double J_43 = (s1 * term_orient_small) + (c1 * term_orient_large);
    
    output->w_x = (J_42 * dq2) + (J_43 * dq3);


    // w_y (Row 5)
    // J(5,1) = 0
    // J(5,2) = -K_SUM_ROOTS_DIV4 * cos(q1)
    // J(5,3) = -term_large*sin(q1) + term_small*cos(q1) ... wait, checking LaTeX sign
    // LaTeX J(5,3): -Large*s1*s2 + small*c1 ... actually it's:
    // J(5,3) = s1 * term_orient_large - c1 * term_orient_small
    double J_52 = -1.0 * K_SUM_ROOTS_DIV4 * c1;
    double J_53 = (s1 * term_orient_large) - (c1 * term_orient_small);

    output->w_y = (J_52 * dq2) + (J_53 * dq3);


    // w_z (Row 6)
    // J(6,1) = 1
    // J(6,2) = K_DIFF_ROOTS_DIV4
    // J(6,3) = K_SQRT3_PLUS2_DIV4 * cos(q2) + K_2_MINUS_SQRT3_DIV4
    double J_63 = (K_SQRT3_PLUS2_DIV4 * c2) + K_2_MINUS_SQRT3_DIV4;

    output->w_z = (1.0 * dq1) + (K_DIFF_ROOTS_DIV4 * dq2) + (J_63 * dq3);
}