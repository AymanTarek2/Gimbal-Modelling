

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_G_3(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[0];
  double x1 = cbo[2];
  double x2 = x0*x1;
  double x3 = sbo[2];
  double x4 = cbo[0];
  double x5 = sbo[1];
  double x6 = x3*x4*x5;
  double x7 = cq[0];
  double x8 = cbo[1]*x4;
  double x9 = x7*x8;
  double x10 = sq[0];
  double x11 = -x0*x3 + x1*x4*x5;
  double x12 = x10*x11;
  double x13 = M_SQRT2;
  double x14 = sqrt(6);
  double x15 = (1.0/4.0)*x13;
  double x16 = (1.0/4.0)*x14;
  double x17 = x15 - x16;
  double x18 = -x2 - x6;
  double x19 = -x15 - x16;
  double x20 = x12 - x9;
  double x21 = -x17*x18 + x19*x20;
  double x22 = cq[1]*(x17*x20 + x18*x19) - sq[1]*(x10*x8 + x11*x7);
  *val = 0.064460835072000011*x12 - 0.12022839443699997*x2 + 0.7145604000000001*x21*(0.013937500000000002*x13 + 0.032607499999999998*x14) + 2.3608746000000003*x21*(0.016767499999999998*x13 + 0.016512499999999999*x14) + 0.7145604000000001*x22*(-0.032607499999999998*x13 + 0.013937500000000002*x14) + 2.3608746000000003*x22*(-0.016512499999999999*x13 + 0.016767499999999998*x14) - 0.12022839443699997*x6 - 0.064460835072000011*x9;
}
