

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_8_8(const double base_dori[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1];
  double x1 = cbo[1];
  double x2 = 1.5274700000000001*x0*x1;
  *val = base_dori[1]*(-pow(cbo[0], 2)*x2 - pow(sbo[0], 2)*x2 + 1.5274700000000001*x0*x1);
}
