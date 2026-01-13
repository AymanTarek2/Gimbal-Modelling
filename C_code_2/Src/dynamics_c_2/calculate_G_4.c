

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_G_4(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = cq[0];
  double x1 = sbo[0];
  double x2 = sbo[1]*x1;
  double x3 = x0*x2;
  double x4 = cbo[1];
  double x5 = x1*x4;
  double x6 = sbo[2]*x5;
  double x7 = sq[0];
  double x8 = cbo[2];
  double x9 = x5*x7*x8;
  double x10 = M_SQRT2;
  double x11 = sqrt(6);
  double x12 = (1.0/4.0)*x10;
  double x13 = (1.0/4.0)*x11;
  double x14 = x12 - x13;
  double x15 = -x12 - x13;
  double x16 = x3 + x9;
  double x17 = x14*x6 + x15*x16;
  double x18 = cq[1]*(x14*x16 - x15*x6) - sq[1]*(x0*x1*x4*x8 - x2*x7);
  *val = 0.7145604000000001*x17*(0.013937500000000002*x10 + 0.032607499999999998*x11) + 2.3608746000000003*x17*(0.016767499999999998*x10 + 0.016512499999999999*x11) + 0.7145604000000001*x18*(-0.032607499999999998*x10 + 0.013937500000000002*x11) + 2.3608746000000003*x18*(-0.016512499999999999*x10 + 0.016767499999999998*x11) + 0.064460835072000011*x3 - 0.12022839443699997*x6 + 0.064460835072000011*x9;
}
