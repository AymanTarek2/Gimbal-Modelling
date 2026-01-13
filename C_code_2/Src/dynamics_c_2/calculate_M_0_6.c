

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_0_6(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1];
  double x1 = sq[0];
  double x2 = cbo[2];
  double x3 = cq[0];
  double x4 = cbo[1];
  double x5 = x3*x4;
  double x6 = x0*x1 - x2*x5;
  double x7 = sbo[2];
  double x8 = cbo[0];
  double x9 = sbo[0];
  double x10 = x0*x2;
  double x11 = x10*x9 + x7*x8;
  double x12 = x1*x4;
  double x13 = x11*x3 + x12*x9;
  double x14 = -x10*x8 + x7*x9;
  double x15 = -x12*x8 + x14*x3;
  double x16 = M_SQRT2;
  double x17 = sqrt(6);
  double x18 = x16 + x17;
  double x19 = x18*(0.013937500000000002*x16 + 0.032607499999999998*x17);
  double x20 = 0.032607499999999998*x16 - 0.013937500000000002*x17;
  double x21 = 4*sq[1];
  double x22 = cq[1]*(x16 - x17);
  double x23 = -x21*(x0*x3 + x12*x2) + x22*x6;
  double x24 = x18*(0.016767499999999998*x16 + 0.016512499999999999*x17);
  double x25 = 0.016512499999999999*x16 - 0.016767499999999998*x17;
  double x26 = x13*x22 + x21*(x1*x11 - x5*x9);
  double x27 = x15*x22 + x21*(x1*x14 + x5*x8);
  *val = 0.0065709312000000004*x11*x13 - 0.01821*x11*(x13*x19 + x20*x26) - 0.060165000000000003*x11*(x13*x24 + x25*x26) + 0.0065709312000000004*x14*x15 - 0.01821*x14*(x15*x19 + x20*x27) - 0.060165000000000003*x14*(x15*x24 + x25*x27) - 0.0065709312000000004*x2*x4*x6 + 0.01821*x2*x4*(x19*x6 + x20*x23) + 0.060165000000000003*x2*x4*(x23*x25 + x24*x6);
}
