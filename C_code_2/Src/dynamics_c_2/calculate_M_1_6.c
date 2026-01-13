

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_1_6(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = M_SQRT2;
  double x1 = sqrt(6);
  double x2 = 0.0039738982499999999*x0 - 0.0040352665499999996*x1;
  double x3 = sbo[1];
  double x4 = sq[0];
  double x5 = cq[0];
  double x6 = cbo[2];
  double x7 = cbo[1];
  double x8 = x6*x7;
  double x9 = 4*cq[1];
  double x10 = sq[1];
  double x11 = sbo[2];
  double x12 = x0 + x1;
  double x13 = x0 - x1;
  double x14 = x8*(x10*(x11*x12*x7 + x13*(x3*x5 + x4*x8)) - x9*(x3*x4 - x5*x8));
  double x15 = 0.0023751302999999997*x0 - 0.0010152075000000001*x1;
  double x16 = cbo[0];
  double x17 = x11*x16;
  double x18 = sbo[0];
  double x19 = x18*x6;
  double x20 = x17 + x19*x3;
  double x21 = x18*x7;
  double x22 = x16*x6;
  double x23 = x11*x18;
  double x24 = x20*(x10*(x12*(-x22 + x23*x3) + x13*(x20*x4 - x21*x5)) + x9*(x20*x5 + x21*x4));
  double x25 = -x22*x3 + x23;
  double x26 = x16*x7;
  double x27 = x25*(x10*(-x12*(x17*x3 + x19) + x13*(x25*x4 + x26*x5)) + x9*(x25*x5 - x26*x4));
  *val = (1.0/4.0)*x14*x15 + (1.0/4.0)*x14*x2 + (1.0/4.0)*x15*x24 + (1.0/4.0)*x15*x27 + (1.0/4.0)*x2*x24 + (1.0/4.0)*x2*x27;
}
