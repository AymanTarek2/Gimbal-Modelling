

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_G_0(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sq[0];
  double x1 = sbo[0];
  double x2 = cbo[1];
  double x3 = x0*x1*x2;
  double x4 = cq[0];
  double x5 = cbo[0]*sbo[2] + cbo[2]*sbo[1]*x1;
  double x6 = x4*x5;
  double x7 = M_SQRT2;
  double x8 = sqrt(6);
  double x9 = x3 + x6;
  double x10 = (1.0/4.0)*x7;
  double x11 = (1.0/4.0)*x8;
  double x12 = x9*(-x10 - x11);
  double x13 = cq[1]*x9*(x10 - x11) - sq[1]*(-x0*x5 + x1*x2*x4);
  *val = 0.7145604000000001*x12*(0.013937500000000002*x7 + 0.032607499999999998*x8) + 2.3608746000000003*x12*(0.016767499999999998*x7 + 0.016512499999999999*x8) + 0.7145604000000001*x13*(-0.032607499999999998*x7 + 0.013937500000000002*x8) + 2.3608746000000003*x13*(-0.016512499999999999*x7 + 0.016767499999999998*x8) + 0.064460835072000011*x3 + 0.064460835072000011*x6;
}
