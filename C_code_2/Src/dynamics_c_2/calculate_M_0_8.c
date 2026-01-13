

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_0_8(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1];
  double x1 = sq[0];
  double x2 = cq[0];
  double x3 = cbo[1];
  double x4 = cbo[2];
  double x5 = x3*x4;
  double x6 = x0*x1 - x2*x5;
  double x7 = sbo[0];
  double x8 = x3*x7;
  double x9 = sbo[2];
  double x10 = cbo[0];
  double x11 = x0*x4;
  double x12 = x10*x9 + x11*x7;
  double x13 = x1*x8 + x12*x2;
  double x14 = x10*x3;
  double x15 = -x10*x11 + x7*x9;
  double x16 = -x1*x14 + x15*x2;
  double x17 = M_SQRT2;
  double x18 = sqrt(6);
  double x19 = 0.013937500000000002*x17 + 0.032607499999999998*x18;
  double x20 = x17 + x18;
  double x21 = x20*x6;
  double x22 = 0.032607499999999998*x17 - 0.013937500000000002*x18;
  double x23 = 4*sq[1];
  double x24 = cq[1]*(x17 - x18);
  double x25 = -x23*(x0*x2 + x1*x5) + x24*x6;
  double x26 = 0.016767499999999998*x17 + 0.016512499999999999*x18;
  double x27 = 0.016512499999999999*x17 - 0.016767499999999998*x18;
  double x28 = x13*x20;
  double x29 = x13*x24 + x23*(x1*x12 - x2*x8);
  double x30 = x16*x20;
  double x31 = x16*x24 + x23*(x1*x15 + x14*x2);
  *val = -0.0065709312000000004*x0*x6 + 0.01821*x0*(x19*x21 + x22*x25) + 0.060165000000000003*x0*(x21*x26 + x25*x27) - 0.0065709312000000004*x13*x8 + 0.0065709312000000004*x14*x16 - 0.01821*x14*(x19*x30 + x22*x31) - 0.060165000000000003*x14*(x26*x30 + x27*x31) + 0.01821*x8*(x19*x28 + x22*x29) + 0.060165000000000003*x8*(x26*x28 + x27*x29);
}
