

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_8_6(const double base_dori[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[0];
  double x1 = sbo[2];
  double x2 = x0*x1;
  double x3 = cbo[0];
  double x4 = sbo[1];
  double x5 = cbo[2];
  double x6 = x4*x5;
  double x7 = x2 - x3*x6;
  double x8 = cbo[1];
  double x9 = 0.76373500000000005*x8;
  double x10 = x1*x3;
  double x11 = x5*x8;
  *val = base_dori[1]*(-0.76373500000000005*x4*(-x0*(x0*x6 + x10) + x3*x7 + x6) + 0.76373500000000005*x8*(-pow(x0, 2)*x11 - x11*pow(x3, 2) + x5*x8)) + base_dori[2]*x9*(-x0*(-x2*x4 + x3*x5) - x1*x4 + x3*(x0*x5 + x10*x4));
}
