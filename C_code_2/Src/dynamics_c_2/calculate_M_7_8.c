

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_7_8(const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1]*sbo[2];
  double x1 = cbo[0];
  double x2 = sbo[0];
  double x3 = cbo[2];
  *val = 1.5274700000000001*cbo[1]*(-x0 + x1*(x0*x1 + x2*x3) + x2*(x0*x2 - x1*x3));
}
