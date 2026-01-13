#include "inverse_velocity.h"
#include <math.h>

// --- Constants derived from roots ---
#define SQRT2  1.41421356
#define SQRT3  1.73205081
#define SQRT6  2.44948974
#define L2     9.6370
#define L2_SQ  92.871769 // 9.637^2

void calculate_inverse_velocity(double q1, double q2, double q3, CartesianVelocities* in, JointVelocities* out) {
    // 1. Precompute Trig
    double s1 = sin(q1);
    double c1 = cos(q1);
    double s2 = sin(q2);
    double c2 = cos(q2);
    double s2_sq = s2 * s2;
    double c2_sq = c2 * c2;

    // 2. Precompute Common Denominator Base
    // All denominators in the matrix share the factor (L2^2 + sin^2(q2))
    double base_factor = L2_SQ + s2_sq;

    // --- ROW 1 (dq1) ---
    // Denominator Factor for Row 1: (4*sqrt(3) + 7)
    double D1_const = (4.0 * SQRT3) + 7.0; 
    double Denom1 = D1_const * base_factor;

    // Element (1,1) Term: L2*(5*sqrt(2) + 3*sqrt(6)) * cos(q1)
    double N11 = L2 * ((5.0 * SQRT2) + (3.0 * SQRT6)) * c1;
    
    // Element (1,2) Term: L2*(5*sqrt(2) + 3*sqrt(6)) * sin(q1)
    double N12 = L2 * ((5.0 * SQRT2) + (3.0 * SQRT6)) * s1;

    // Element (1,4) Term: Big trigonometric mess
    double term14_A = -2.0*s1*s2 - SQRT3*s1*s2 + 5.0*SQRT2*c1*c2 + 3.0*SQRT6*c1*c2;
    double N14 = term14_A * s2;

    // Element (1,5) Term
    double term15_A = 5.0*SQRT2*s1*c2 + 3.0*SQRT6*s1*c2 + SQRT3*s2*c1 + 2.0*s2*c1;
    double N15 = term15_A * s2;

    // Element (1,6) is simpler: sin^2(q2) / base_factor
    // Note: The denominator for (1,6) is just base_factor, not Denom1
    double val16 = s2_sq / base_factor;

    // Compute dq1
    out->dq1 = (N11/Denom1) * in->v_x 
             + (N12/Denom1) * in->v_y 
             + 0.0          * in->v_z // (1,3) is 0
             + (N14/Denom1) * in->w_x 
             + (N15/Denom1) * in->w_y 
             + val16        * in->w_z;


    // --- ROW 2 (dq2) ---
    // Denominator Factor for Row 2: (19 + 11*sqrt(3))
    // Note: Some terms in Row 2 have a '4' in front of this, some '2'.
    double D2_const = 19.0 + (11.0 * SQRT3);
    double Denom2_Full = D2_const * base_factor; // The base denominator

    // Element (2,1)
    double term21_inner = 5.0*c2 + 3.0*SQRT3*c2 - 3.0*SQRT3 - 5.0;
    double N21 = L2 * term21_inner * c1;

    // Element (2,2)
    double N22 = L2 * term21_inner * s1;

    // Element (2,4) - Denominator is 4 * Denom2_Full
    double term24_part1 = (s1*c2 - s1 + SQRT2*s2*c1 + SQRT6*s2*c1);
    double term24_part2 = (SQRT6*L2_SQ + 2.0*SQRT2*L2_SQ - 2.0*SQRT2*c2 - SQRT6*c2 + SQRT6 + 2.0*SQRT2);
    double term24_part3 = (SQRT2 + SQRT6) * (-12.0*SQRT3*L2_SQ - 20.0*L2_SQ + 19.0*c2_sq + 11.0*SQRT3*c2_sq + 2.0*c2 + 2.0*SQRT3*c2 - 13.0*SQRT3 - 21.0);
    double N24 = (2.0 * term24_part1 * term24_part2) - (term24_part3 * s1);

    // Element (2,5) - Denominator is 4 * Denom2_Full
    double term25_part1 = (SQRT2*s1*s2 + SQRT6*s1*s2 - c1*c2 + c1);
    // term24_part2 is reused here!
    // term24_part3 is reused here!
    double N25 = (2.0 * term25_part1 * term24_part2) + (term24_part3 * c1);

    // Element (2,6) - Denominator is 2 * Denom2_Full
    double term26_inner = -7.0*SQRT2*c2 - 4.0*SQRT6*c2 + 4.0*SQRT6 + 7.0*SQRT2;
    double N26 = L2_SQ * term26_inner;

    // Compute dq2
    out->dq2 = (N21 / Denom2_Full)       * in->v_x
             + (N22 / Denom2_Full)       * in->v_y
             + 0.0                       * in->v_z
             + (N24 / (4.0*Denom2_Full)) * in->w_x
             + (N25 / (4.0*Denom2_Full)) * in->w_y
             + (N26 / (2.0*Denom2_Full)) * in->w_z;


    // --- ROW 3 (dq3) ---
    // Denominator Factor for Row 3: (5 + 3*sqrt(3))
    double D3_const = 5.0 + (3.0 * SQRT3);
    double Denom3_Full = D3_const * base_factor;

    // Element (3,1)
    double N31 = -2.0 * L2 * (SQRT6 + 2.0*SQRT2) * c1 * c2;

    // Element (3,2)
    double N32 = -2.0 * L2 * (SQRT6 + 2.0*SQRT2) * s1 * c2;

    // Element (3,4) - Denom is 2 * Denom3_Full
    double term34_A = SQRT2*(SQRT2+SQRT6)*(L2_SQ - c2 + 1.0) * s1;
    double term34_B = 2.0*(L2_SQ + SQRT3*L2_SQ + 1.0 + SQRT3) * (s1*c2 - s1 + SQRT2*s2*c1 + SQRT6*s2*c1);
    double N34 = -term34_A - term34_B; // Note the negative sign in front of the fraction in matrix

    // Element (3,5) - Denom is 2 * Denom3_Full
    double term35_A = SQRT2*(SQRT2+SQRT6)*(L2_SQ - c2 + 1.0) * c1;
    double term35_B = 2.0*(L2_SQ + SQRT3*L2_SQ + 1.0 + SQRT3) * (SQRT2*s1*s2 + SQRT6*s1*s2 - c1*c2 + c1);
    double N35 = term35_A - term35_B;

    // Element (3,6) is simpler: L2^2 * cos(q2) / base_factor
    double val36 = (L2_SQ * c2) / base_factor;

    // Compute dq3
    out->dq3 = (N31 / Denom3_Full)       * in->v_x
             + (N32 / Denom3_Full)       * in->v_y
             + 0.0                       * in->v_z
             + (N34 / (2.0*Denom3_Full)) * in->w_x
             + (N35 / (2.0*Denom3_Full)) * in->w_y
             + val36                     * in->w_z;
}