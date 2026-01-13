

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_7_0(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[2];
  double x1 = cbo[1];
  double x2 = sbo[1];
  double x3 = sq[0];
  double x4 = cq[0];
  double x5 = cbo[2];
  double x6 = x1*x5;
  double x7 = x2*x3 - x4*x6;
  double x8 = cbo[0];
  double x9 = x5*x8;
  double x10 = sbo[0];
  double x11 = x0*x10;
  double x12 = x11*x2 - x9;
  double x13 = x1*x10;
  double x14 = x0*x8;
  double x15 = x10*x5;
  double x16 = x14 + x15*x2;
  double x17 = x13*x3 + x16*x4;
  double x18 = x14*x2 + x15;
  double x19 = x1*x8;
  double x20 = x11 - x2*x9;
  double x21 = -x19*x3 + x20*x4;
  double x22 = M_SQRT2;
  double x23 = sqrt(6);
  double x24 = 0.013937500000000002*x22 + 0.032607499999999998*x23;
  double x25 = x22 + x23;
  double x26 = x25*x7;
  double x27 = 0.032607499999999998*x22 - 0.013937500000000002*x23;
  double x28 = 4*sq[1];
  double x29 = cq[1]*(x22 - x23);
  double x30 = -x28*(x2*x4 + x3*x6) + x29*x7;
  double x31 = x0*x1;
  double x32 = 0.016767499999999998*x22 + 0.016512499999999999*x23;
  double x33 = 0.016512499999999999*x22 - 0.016767499999999998*x23;
  double x34 = x17*x25;
  double x35 = x17*x29 + x28*(-x13*x4 + x16*x3);
  double x36 = x21*x25;
  double x37 = x21*x29 + x28*(x19*x4 + x20*x3);
  *val = 0.0065709312000000004*x0*x1*x7 - 0.0065709312000000004*x12*x17 + 0.01821*x12*(x24*x34 + x27*x35) + 0.060165000000000003*x12*(x32*x34 + x33*x35) + 0.0065709312000000004*x18*x21 - 0.01821*x18*(x24*x36 + x27*x37) - 0.060165000000000003*x18*(x32*x36 + x33*x37) - 0.01821*x31*(x24*x26 + x27*x30) - 0.060165000000000003*x31*(x26*x32 + x30*x33);
}
