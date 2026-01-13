

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_7_6(const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[2];
  double x1 = cbo[2];
  double x2 = cbo[0];
  double x3 = x0*x2;
  double x4 = sbo[1];
  double x5 = sbo[0];
  double x6 = x1*x5;
  double x7 = x1*x2;
  double x8 = x0*x5;
  *val = -1.5274700000000001*pow(cbo[1], 2)*x0*x1 - 1.5274700000000001*(x3 + x4*x6)*(x4*x8 - x7) + 1.5274700000000001*(x3*x4 + x6)*(-x4*x7 + x8);
}
