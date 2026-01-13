

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_7_6(const double base_dori[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[0];
  double x1 = sbo[2];
  double x2 = x0*x1;
  double x3 = sbo[1];
  double x4 = cbo[0];
  double x5 = cbo[2];
  double x6 = x4*x5;
  double x7 = x2 - x3*x6;
  double x8 = -x7;
  double x9 = x2*x3 - x4*x5;
  double x10 = 0.76373500000000005*x9;
  double x11 = -x9;
  double x12 = cbo[1];
  double x13 = x0*x5;
  double x14 = x1*x4;
  double x15 = x13 + x14*x3;
  double x16 = 0.76373500000000005*x12;
  double x17 = x13*x3 + x14;
  double x18 = 0.76373500000000005*pow(x12, 2);
  *val = base_dori[0]*(-x10*x8 + 0.76373500000000005*x11*x7) + base_dori[1]*(1.5274700000000001*x1*x12*x3*x5 + 0.76373500000000005*x1*x12*x4*x7 - x10*x12*x13 - x15*x16*x6 - x16*x17*x2) + base_dori[2]*(pow(x1, 2)*x18 - x10*x11 + 0.76373500000000005*pow(x15, 2) - 0.76373500000000005*pow(x17, 2) - x18*pow(x5, 2) + 0.76373500000000005*x7*x8);
}
