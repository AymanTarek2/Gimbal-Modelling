

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_8_8(const double sbo[3], const double cbo[3], double *val) {
  double x0 = pow(cbo[1], 2);
  *val = 1.5274700000000001*pow(cbo[0], 2)*x0 + 1.5274700000000001*pow(sbo[0], 2)*x0 + 1.5274700000000001*pow(sbo[1], 2);
}
