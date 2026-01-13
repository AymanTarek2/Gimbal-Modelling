

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_2_1(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = M_SQRT2;
  double x1 = sqrt(6);
  double x2 = x0 - x1;
  double x3 = sbo[2];
  double x4 = cbo[1];
  double x5 = x0 + x1;
  double x6 = sbo[1];
  double x7 = cq[0];
  double x8 = sq[0];
  double x9 = cbo[2];
  double x10 = x4*x9;
  double x11 = x10*x8 + x6*x7;
  double x12 = x11*x5 - x2*x3*x4;
  double x13 = sq[1];
  double x14 = -4*x10*x7 + 4*x6*x8;
  double x15 = cq[1];
  double x16 = x11*x2 + x3*x4*x5;
  double x17 = x13*x14 + x15*x16;
  double x18 = x12*x2 - x17*x5;
  double x19 = sbo[0];
  double x20 = x19*x9;
  double x21 = cbo[0];
  double x22 = x21*x3;
  double x23 = x20 + x22*x6;
  double x24 = x21*x4;
  double x25 = x19*x3;
  double x26 = x21*x9;
  double x27 = x25 - x26*x6;
  double x28 = x24*x7 + x27*x8;
  double x29 = x2*x23 + x28*x5;
  double x30 = -4*x24*x8 + 4*x27*x7;
  double x31 = x2*x28 - x23*x5;
  double x32 = -x13*x30 + x15*x31;
  double x33 = x2*x29 - x32*x5;
  double x34 = x25*x6 - x26;
  double x35 = x19*x4;
  double x36 = x20*x6 + x22;
  double x37 = -x35*x7 + x36*x8;
  double x38 = -x2*x34 + x37*x5;
  double x39 = 4*x35*x8 + 4*x36*x7;
  double x40 = x2*x37 + x34*x5;
  double x41 = -x13*x39 + x15*x40;
  double x42 = x2*x38 - x41*x5;
  double x43 = cq[2];
  double x44 = x43*x5;
  double x45 = x13*x16 - x14*x15;
  double x46 = sq[2];
  double x47 = 4*x46;
  double x48 = x2*x43;
  double x49 = x12*x44 + x17*x48 + x45*x47;
  double x50 = x13*x31 + x15*x30;
  double x51 = x29*x44 + x32*x48 + x47*x50;
  double x52 = x13*x40 + x15*x39;
  double x53 = x38*x44 + x41*x48 + x47*x52;
  double x54 = -x33;
  double x55 = -x12;
  double x56 = x46*x5;
  double x57 = 4*x43;
  double x58 = x17*x2*x46 - x45*x57 - x55*x56;
  double x59 = x2*x32*x46 + x29*x56 - x50*x57;
  double x60 = -x38;
  double x61 = x2*x41*x46 - x52*x57 - x56*x60;
  *val = -3.2492791748046877e-9*(pow(x18, 2) + pow(x33, 2) + pow(x42, 2))*(x12*x18 + x29*x33 + x38*x42) + 1.7640350341796876e-9*(x12*x49 + x29*x51 + x38*x53)*(-x18*x49 - x42*x53 + x51*x54) + 1.7640350341796876e-9*(x12*x58 + x29*x59 + x38*x61)*(x54*x59 + x58*(x17*x5 + x2*x55) + x61*(x2*x60 + x41*x5));
}
