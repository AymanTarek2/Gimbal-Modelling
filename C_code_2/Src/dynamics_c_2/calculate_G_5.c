

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_G_5(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[2];
  double x1 = cbo[0];
  double x2 = x0*x1;
  double x3 = cbo[2];
  double x4 = sbo[0]*sbo[1];
  double x5 = x3*x4;
  double x6 = -x0*x4 + x1*x3;
  double x7 = sq[0]*x6;
  double x8 = M_SQRT2;
  double x9 = sqrt(6);
  double x10 = (1.0/4.0)*x8;
  double x11 = (1.0/4.0)*x9;
  double x12 = x10 - x11;
  double x13 = -x2 - x5;
  double x14 = -x10 - x11;
  double x15 = -x12*x13 + x14*x7;
  double x16 = -cq[0]*sq[1]*x6 + cq[1]*(x12*x7 + x13*x14);
  *val = 0.7145604000000001*x15*(0.013937500000000002*x8 + 0.032607499999999998*x9) + 2.3608746000000003*x15*(0.016767499999999998*x8 + 0.016512499999999999*x9) + 0.7145604000000001*x16*(-0.032607499999999998*x8 + 0.013937500000000002*x9) + 2.3608746000000003*x16*(-0.016512499999999999*x8 + 0.016767499999999998*x9) - 0.12022839443699997*x2 - 0.12022839443699997*x5 + 0.064460835072000011*x7;
}
