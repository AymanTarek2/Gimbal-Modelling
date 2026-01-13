

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_6_6(const double sbo[3], const double cbo[3], double *val) {
  double x0 = cbo[2];
  double x1 = sbo[2];
  double x2 = cbo[0];
  double x3 = sbo[0];
  double x4 = sbo[1]*x0;
  *val = 1.5274700000000001*pow(cbo[1], 2)*pow(x0, 2) + 1.5274700000000001*pow(x1*x2 + x3*x4, 2) + 1.5274700000000001*pow(x1*x3 - x2*x4, 2);
}
