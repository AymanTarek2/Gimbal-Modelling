

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_7_1(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = M_SQRT2;
  double x1 = sqrt(6);
  double x2 = 0.016512499999999999*x0 - 0.016767499999999998*x1;
  double x3 = 0.24066000000000001*x2;
  double x4 = sbo[1];
  double x5 = sq[0];
  double x6 = cq[0];
  double x7 = cbo[2];
  double x8 = cbo[1];
  double x9 = x7*x8;
  double x10 = 4*cq[1];
  double x11 = sq[1];
  double x12 = x0 + x1;
  double x13 = sbo[2];
  double x14 = x13*x8;
  double x15 = x0 - x1;
  double x16 = x14*(-x10*(x4*x5 - x6*x9) + x11*(x12*x14 + x15*(x4*x6 + x5*x9)));
  double x17 = 0.032607499999999998*x0 - 0.013937500000000002*x1;
  double x18 = 0.072840000000000002*x17;
  double x19 = cbo[0];
  double x20 = x19*x7;
  double x21 = sbo[0];
  double x22 = x13*x21;
  double x23 = -x20 + x22*x4;
  double x24 = x21*x8;
  double x25 = x13*x19;
  double x26 = x21*x7;
  double x27 = x25 + x26*x4;
  double x28 = x23*(x10*(x24*x5 + x27*x6) + x11*(x12*x23 + x15*(-x24*x6 + x27*x5)));
  double x29 = x25*x4 + x26;
  double x30 = x19*x8;
  double x31 = -x20*x4 + x22;
  double x32 = x10*(-x30*x5 + x31*x6) + x11*(-x12*x29 + x15*(x30*x6 + x31*x5));
  *val = -1.0/4.0*x16*x18 - 1.0/4.0*x16*x3 + 0.01821*x17*x29*x32 - 1.0/4.0*x18*x28 + 0.060165000000000003*x2*x29*x32 - 1.0/4.0*x28*x3;
}
