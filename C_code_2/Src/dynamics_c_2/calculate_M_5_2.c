

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_5_2(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[0];
  double x1 = pow(x0, 2);
  double x2 = sbo[1];
  double x3 = pow(x2, 2);
  double x4 = cbo[1];
  double x5 = pow(x4, 2);
  double x6 = cbo[0];
  double x7 = pow(x6, 2);
  double x8 = M_SQRT2;
  double x9 = sqrt(6);
  double x10 = x8 - x9;
  double x11 = sbo[2];
  double x12 = x11*x4;
  double x13 = x8 + x9;
  double x14 = cq[0];
  double x15 = sq[0];
  double x16 = cbo[2];
  double x17 = x16*x4;
  double x18 = x14*x2 + x15*x17;
  double x19 = -x10*x12 + x13*x18;
  double x20 = -x14*x17 + x15*x2;
  double x21 = sq[1];
  double x22 = 4*x21;
  double x23 = cq[1];
  double x24 = x10*x18 + x12*x13;
  double x25 = x20*x22 + x23*x24;
  double x26 = x13*x25;
  double x27 = x10*x19 - x26;
  double x28 = x0*x16;
  double x29 = x11*x6;
  double x30 = x2*x29 + x28;
  double x31 = x4*x6;
  double x32 = x0*x11;
  double x33 = x16*x6;
  double x34 = -x2*x33 + x32;
  double x35 = x14*x31 + x15*x34;
  double x36 = x10*x30 + x13*x35;
  double x37 = x14*x34 - x15*x31;
  double x38 = x10*x35 - x13*x30;
  double x39 = -x22*x37 + x23*x38;
  double x40 = x10*x36 - x13*x39;
  double x41 = x2*x32 - x33;
  double x42 = x0*x4;
  double x43 = x2*x28 + x29;
  double x44 = -x14*x42 + x15*x43;
  double x45 = -x10*x41 + x13*x44;
  double x46 = x14*x43 + x15*x42;
  double x47 = x10*x44 + x13*x41;
  double x48 = -x22*x46 + x23*x47;
  double x49 = x13*x48;
  double x50 = x10*x45 - x49;
  double x51 = -x27;
  double x52 = x2*(x1 + x7);
  double x53 = -x40;
  double x54 = -x50;
  double x55 = cq[2];
  double x56 = x13*x55;
  double x57 = 4*x23;
  double x58 = -x20*x57 + x21*x24;
  double x59 = sq[2];
  double x60 = 4*x59;
  double x61 = x10*x55;
  double x62 = x19*x56 + x25*x61 + x58*x60;
  double x63 = x21*x47 + x46*x57;
  double x64 = x45*x56 + x48*x61 + x60*x63;
  double x65 = x21*x38 + x37*x57;
  double x66 = x36*x56 + x39*x61 + x60*x65;
  double x67 = -x19;
  double x68 = x13*x59;
  double x69 = 4*x55;
  double x70 = -x10*x25*x59 + x58*x69 + x67*x68;
  double x71 = -x45;
  double x72 = -x10*x48*x59 + x63*x69 + x68*x71;
  double x73 = x10*x39*x59 + x36*x68 - x65*x69;
  *val = -1.0/512.0*(6.6545237500000004e-6*(pow(x27, 2) + pow(x40, 2) + pow(x50, 2))*(x31*x53 - x42*x54 + x51*x52) + 3.6127437500000003e-6*(x31*x66 - x42*x64 + x52*x62)*(x51*x62 + x53*x66 + x54*x64) + 3.6127437500000003e-6*(x53*x73 - x70*(x10*x67 + x26) - x72*(x10*x71 + x49))*(x0*x4*x72 + x31*x73 - x52*x70))/(x1*x3 + x1*x5 + x3*x7 + x5*x7);
}
