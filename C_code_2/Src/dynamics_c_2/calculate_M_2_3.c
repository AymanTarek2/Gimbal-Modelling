

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_2_3(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
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
  double x30 = x29*x7;
  double x31 = x28 - x30;
  double x32 = x27*x8 + x31*x9;
  double x33 = x2*x26 + x32*x6;
  double x34 = -x27*x9 + x31*x8;
  double x35 = x2*x32 - x26*x6;
  double x36 = -x16*x34 + x17*x35;
  double x37 = x2*x33 - x36*x6;
  double x38 = x28*x7 - x29;
  double x39 = x22*x4;
  double x40 = x23*x7;
  double x41 = x25 + x40;
  double x42 = -x39*x8 + x41*x9;
  double x43 = -x2*x38 + x42*x6;
  double x44 = x39*x9 + x41*x8;
  double x45 = x2*x42 + x38*x6;
  double x46 = -x16*x44 + x17*x45;
  double x47 = x46*x6;
  double x48 = x2*x43 - x47;
  double x49 = -x21;
  double x50 = pow(x7, 2);
  double x51 = pow(x22, 2);
  double x52 = pow(x3, 2);
  double x53 = x51*x52;
  double x54 = pow(x10, 2);
  double x55 = x51*x54;
  double x56 = pow(x4, 2);
  double x57 = pow(x24, 2);
  double x58 = x52*x57;
  double x59 = x54*x57;
  double x60 = 1.0/(x50*x53 + x50*x55 + x50*x58 + x50*x59 + x53*x56 + x55*x56 + x56*x58 + x56*x59);
  double x61 = x10*x60*(x51*x56 + x56*x57)/x4;
  double x62 = 1.0/(x53 + x55 + x58 + x59);
  double x63 = x25*x62 + x40*x60;
  double x64 = -x48;
  double x65 = -x28*x62 + x30*x60;
  double x66 = -x37;
  double x67 = cq[2];
  double x68 = x6*x67;
  double x69 = 4*x17;
  double x70 = -x14*x69 + x15*x18;
  double x71 = sq[2];
  double x72 = 4*x71;
  double x73 = x2*x67;
  double x74 = x13*x68 + x19*x73 + x70*x72;
  double x75 = x15*x45 + x44*x69;
  double x76 = x43*x68 + x46*x73 + x72*x75;
  double x77 = x15*x35 + x34*x69;
  double x78 = x33*x68 + x36*x73 + x72*x77;
  double x79 = -x13;
  double x80 = x6*x71;
  double x81 = 4*x67;
  double x82 = -x19*x2*x71 + x70*x81 + x79*x80;
  double x83 = -x43;
  double x84 = -x2*x46*x71 + x75*x81 + x80*x83;
  double x85 = x2*x36*x71 + x33*x80 - x77*x81;
  *val = -1.2997116699218751e-8*(pow(x21, 2) + pow(x37, 2) + pow(x48, 2))*(x49*x61 + x63*x64 - x65*x66) - 7.0561401367187505e-9*(x49*x74 + x64*x76 + x66*x78)*(x61*x74 + x63*x76 - x65*x78) - 7.0561401367187505e-9*(-x61*x82 - x63*x84 - x65*x85)*(x66*x85 - x82*(x2*x79 + x20) - x84*(x2*x83 + x47));
}
