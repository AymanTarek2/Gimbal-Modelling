

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_7_8(const double base_dori[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = cbo[0];
  double x1 = cbo[2];
  double x2 = sbo[0];
  double x3 = sbo[1];
  double x4 = sbo[2];
  double x5 = x3*x4;
  double x6 = -x0*x1 + x2*x5;
  double x7 = cbo[1];
  double x8 = 0.76373500000000005*x7;
  double x9 = x1*x2;
  double x10 = x4*x7;
  *val = base_dori[1]*(-0.76373500000000005*x3*(x0*(x0*x5 + x9) + x2*x6 - x5) + 0.76373500000000005*x7*(pow(x0, 2)*x10 + x10*pow(x2, 2) - x10)) + base_dori[2]*x8*(x0*(x0*x1*x3 - x2*x4) - x1*x3 + x2*(x0*x4 + x3*x9));
}
