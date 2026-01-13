

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_7_7(const double base_dori[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1];
  double x1 = sbo[2];
  double x2 = cbo[1];
  double x3 = 1.5274700000000001*x2;
  double x4 = cbo[0];
  double x5 = sbo[0];
  double x6 = cbo[2];
  double x7 = x5*x6;
  double x8 = x0*x1;
  double x9 = x4*x8;
  double x10 = x7 + x9;
  double x11 = x1*x3;
  double x12 = x5*x8;
  double x13 = x12 - x4*x6;
  double x14 = 0.76373500000000005*x10;
  double x15 = 2*x7;
  double x16 = 0.76373500000000005*x13;
  double x17 = 2*x1;
  *val = base_dori[0]*(x14*(-2*x12 + 2*x4*x6) + x16*(x15 + 2*x9)) + base_dori[1]*(-x0*pow(x1, 2)*x3 + x10*x11*x4 + x11*x13*x5) + base_dori[2]*(1.5274700000000001*x1*pow(x2, 2)*x6 + x14*(2*x0*x4*x6 - x17*x5) + x16*(x0*x15 + x17*x4));
}
