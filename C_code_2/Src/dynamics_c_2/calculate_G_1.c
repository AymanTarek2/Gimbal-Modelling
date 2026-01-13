

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_G_1(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = M_SQRT2;
  double x1 = sqrt(6);
  double x2 = sq[0];
  double x3 = sbo[0];
  double x4 = cbo[1]*x3;
  double x5 = cq[0];
  double x6 = sbo[2];
  double x7 = cbo[0];
  double x8 = cbo[2];
  double x9 = sbo[1]*x3;
  double x10 = x6*x7 + x8*x9;
  double x11 = (1.0/4.0)*x0;
  double x12 = (1.0/4.0)*x1;
  double x13 = -cq[1]*(x10*x5 + x2*x4) - sq[1]*((-x11 - x12)*(-x6*x9 + x7*x8) + (x11 - x12)*(x10*x2 - x4*x5));
  *val = 0.7145604000000001*x13*(-0.032607499999999998*x0 + 0.013937500000000002*x1) + 2.3608746000000003*x13*(-0.016512499999999999*x0 + 0.016767499999999998*x1);
}
