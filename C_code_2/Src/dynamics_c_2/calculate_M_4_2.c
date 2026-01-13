

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_4_2(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
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
  double x26 = x25*x7;
  double x27 = x23 + x26;
  double x28 = x24*x4;
  double x29 = x22*x3;
  double x30 = x10*x24;
  double x31 = x29 - x30*x7;
  double x32 = x28*x8 + x31*x9;
  double x33 = x2*x27 + x32*x6;
  double x34 = -x28*x9 + x31*x8;
  double x35 = x2*x32 - x27*x6;
  double x36 = -x16*x34 + x17*x35;
  double x37 = x2*x33 - x36*x6;
  double x38 = x29*x7;
  double x39 = -x30 + x38;
  double x40 = x22*x4;
  double x41 = x23*x7 + x25;
  double x42 = -x40*x8 + x41*x9;
  double x43 = -x2*x39 + x42*x6;
  double x44 = x40*x9 + x41*x8;
  double x45 = x2*x42 + x39*x6;
  double x46 = -x16*x44 + x17*x45;
  double x47 = x46*x6;
  double x48 = x2*x43 - x47;
  double x49 = pow(x7, 2);
  double x50 = pow(x22, 2);
  double x51 = pow(x3, 2);
  double x52 = x50*x51;
  double x53 = pow(x10, 2);
  double x54 = x50*x53;
  double x55 = pow(x4, 2);
  double x56 = pow(x24, 2);
  double x57 = x51*x56;
  double x58 = x53*x56;
  double x59 = 1.0/(x49*x52 + x49*x54 + x49*x57 + x49*x58 + x52*x55 + x54*x55 + x55*x57 + x55*x58);
  double x60 = x3*x59*(x50*x55 + x55*x56)/x4;
  double x61 = 1.0/(x52 + x54 + x57 + x58);
  double x62 = x23*x61 + x26*x59;
  double x63 = -x30*x61 + x38*x59;
  double x64 = cq[2];
  double x65 = x6*x64;
  double x66 = 4*x17;
  double x67 = -x14*x66 + x15*x18;
  double x68 = sq[2];
  double x69 = 4*x68;
  double x70 = x2*x64;
  double x71 = x13*x65 + x19*x70 + x67*x69;
  double x72 = x15*x45 + x44*x66;
  double x73 = x43*x65 + x46*x70 + x69*x72;
  double x74 = x15*x35 + x34*x66;
  double x75 = x33*x65 + x36*x70 + x69*x74;
  double x76 = -x37;
  double x77 = -x13;
  double x78 = x6*x68;
  double x79 = 4*x64;
  double x80 = x19*x2*x68 - x67*x79 - x77*x78;
  double x81 = -x43;
  double x82 = x2*x46*x68 - x72*x79 - x78*x81;
  double x83 = x2*x36*x68 + x33*x78 - x74*x79;
  *val = 1.2997116699218751e-8*(pow(x21, 2) + pow(x37, 2) + pow(x48, 2))*(-x21*x60 + x37*x62 - x48*x63) + 7.0561401367187505e-9*(-x21*x71 - x48*x73 + x75*x76)*(x60*x71 - x62*x75 + x63*x73) + 7.0561401367187505e-9*(x60*x80 - x62*x83 + x63*x82)*(x76*x83 + x80*(x2*x77 + x20) + x82*(x2*x81 + x47));
}
