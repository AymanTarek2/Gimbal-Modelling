

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_1_8(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1];
  double x1 = sq[0];
  double x2 = cq[0];
  double x3 = cbo[2];
  double x4 = cbo[1];
  double x5 = x3*x4;
  double x6 = 4*cq[1];
  double x7 = sq[1];
  double x8 = sbo[2];
  double x9 = M_SQRT2;
  double x10 = sqrt(6);
  double x11 = x10 + x9;
  double x12 = -x10 + x9;
  double x13 = x0*(-x6*(x0*x1 - x2*x5) + x7*(x11*x4*x8 + x12*(x0*x2 + x1*x5)));
  double x14 = -0.0040352665499999996*x10 + 0.0039738982499999999*x9;
  double x15 = -0.0010152075000000001*x10 + 0.0023751302999999997*x9;
  double x16 = sbo[0];
  double x17 = x16*x4;
  double x18 = cbo[0];
  double x19 = x18*x8;
  double x20 = x16*x3;
  double x21 = x0*x20 + x19;
  double x22 = x18*x3;
  double x23 = x16*x8;
  double x24 = x17*(x6*(x1*x17 + x2*x21) + x7*(x11*(x0*x23 - x22) + x12*(x1*x21 - x17*x2)));
  double x25 = x18*x4;
  double x26 = -x0*x22 + x23;
  double x27 = x25*(x6*(-x1*x25 + x2*x26) + x7*(-x11*(x0*x19 + x20) + x12*(x1*x26 + x2*x25)));
  *val = (1.0/4.0)*x13*x14 + (1.0/4.0)*x13*x15 - 1.0/4.0*x14*x24 + (1.0/4.0)*x14*x27 - 1.0/4.0*x15*x24 + (1.0/4.0)*x15*x27;
}
