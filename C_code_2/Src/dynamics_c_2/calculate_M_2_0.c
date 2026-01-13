

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_2_0(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = M_SQRT2;
  double x1 = sqrt(6);
  double x2 = x0 - x1;
  double x3 = sbo[2];
  double x4 = cbo[1];
  double x5 = x3*x4;
  double x6 = x0 + x1;
  double x7 = sbo[1];
  double x8 = cq[0];
  double x9 = sq[0];
  double x10 = cbo[2];
  double x11 = x10*x4;
  double x12 = x11*x9 + x7*x8;
  double x13 = x12*x6 - x2*x5;
  double x14 = -x11*x8 + x7*x9;
  double x15 = sq[1];
  double x16 = 4*x15;
  double x17 = cq[1];
  double x18 = x12*x2 + x5*x6;
  double x19 = x14*x16 + x17*x18;
  double x20 = x19*x6;
  double x21 = x13*x2 - x20;
  double x22 = sbo[0];
  double x23 = x10*x22;
  double x24 = cbo[0];
  double x25 = x24*x3;
  double x26 = x23 + x25*x7;
  double x27 = x24*x4;
  double x28 = x22*x3;
  double x29 = x10*x24;
  double x30 = x28 - x29*x7;
  double x31 = x27*x8 + x30*x9;
  double x32 = x2*x26 + x31*x6;
  double x33 = -x27*x9 + x30*x8;
  double x34 = x2*x31 - x26*x6;
  double x35 = -x16*x33 + x17*x34;
  double x36 = x2*x32 - x35*x6;
  double x37 = x28*x7 - x29;
  double x38 = x22*x4;
  double x39 = x23*x7 + x25;
  double x40 = -x38*x8 + x39*x9;
  double x41 = -x2*x37 + x40*x6;
  double x42 = x38*x9 + x39*x8;
  double x43 = x2*x40 + x37*x6;
  double x44 = -x16*x42 + x17*x43;
  double x45 = x44*x6;
  double x46 = x2*x41 - x45;
  double x47 = -x13;
  double x48 = x2*x47 + x20;
  double x49 = -x41;
  double x50 = x2*x49 + x45;
  double x51 = -x36;
  double x52 = cq[2];
  double x53 = x52*x6;
  double x54 = 4*x17;
  double x55 = -x14*x54 + x15*x18;
  double x56 = sq[2];
  double x57 = 4*x56;
  double x58 = x2*x52;
  double x59 = x13*x53 + x19*x58 + x55*x57;
  double x60 = x15*x43 + x42*x54;
  double x61 = x41*x53 + x44*x58 + x57*x60;
  double x62 = x15*x34 + x33*x54;
  double x63 = x32*x53 + x35*x58 + x57*x62;
  double x64 = x56*x6;
  double x65 = 4*x52;
  double x66 = -x19*x2*x56 + x47*x64 + x55*x65;
  double x67 = -x2*x44*x56 + x49*x64 + x60*x65;
  double x68 = x2*x35*x56 + x32*x64 - x62*x65;
  *val = 1.2997116699218751e-8*(pow(x21, 2) + pow(x36, 2) + pow(x46, 2))*(-x26*x51 + x37*x50 + x48*x5) + 7.0561401367187505e-9*(-x21*x59 - x46*x61 + x51*x63)*(-x26*x63 + x37*x61 + x5*x59) - 7.0561401367187505e-9*(x26*x68 + x37*x67 + x5*x66)*(-x48*x66 - x50*x67 + x51*x68);
}
