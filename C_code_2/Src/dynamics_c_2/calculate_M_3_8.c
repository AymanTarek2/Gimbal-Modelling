

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_3_8(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1];
  double x1 = pow(x0, 2);
  double x2 = sbo[2];
  double x3 = pow(x2, 2);
  double x4 = sbo[0];
  double x5 = pow(x4, 2);
  double x6 = x3*x5;
  double x7 = cbo[2];
  double x8 = pow(x7, 2);
  double x9 = x5*x8;
  double x10 = cbo[0];
  double x11 = pow(x10, 2);
  double x12 = x11*x3;
  double x13 = x11*x8;
  double x14 = 1.0/(x12 + x13 + x6 + x9);
  double x15 = x14*x3;
  double x16 = cbo[1];
  double x17 = pow(x16, 2);
  double x18 = 1.0/(x1*x12 + x1*x13 + x1*x6 + x1*x9 + x12*x17 + x13*x17 + x17*x6 + x17*x9);
  double x19 = x0*x2;
  double x20 = cq[0];
  double x21 = x16*x20;
  double x22 = 0.02554*x21;
  double x23 = sq[0];
  double x24 = x0*x23;
  double x25 = x24*x7;
  double x26 = x14*x2;
  double x27 = 0.088220000000000007*x7;
  double x28 = x2*x23;
  double x29 = x18*x7;
  double x30 = x0*x29;
  double x31 = x16*x4;
  double x32 = x10*x2;
  double x33 = x4*x7;
  double x34 = x0*x33 + x32;
  double x35 = 1.0/x16;
  double x36 = x30*x35;
  double x37 = x0*x32;
  double x38 = x33 + x37;
  double x39 = x29*x35*(x1 + x11*x17 + x17*x5);
  double x40 = x10*x16;
  double x41 = x2*x4;
  double x42 = x10*x7;
  double x43 = -x0*x42 + x41;
  double x44 = x0*x41;
  double x45 = -x42 + x44;
  double x46 = 0.54191999999999996*x19;
  double x47 = M_SQRT2;
  double x48 = sqrt(6);
  double x49 = 0.013937500000000002*x47 + 0.032607499999999998*x48;
  double x50 = x47 - x48;
  double x51 = x47 + x48;
  double x52 = -x21 + x25;
  double x53 = -x19*x50 + x51*x52;
  double x54 = 0.032607499999999998*x47 - 0.013937500000000002*x48;
  double x55 = sq[1];
  double x56 = x16*x23;
  double x57 = x0*x20;
  double x58 = cq[1];
  double x59 = 4*x55*(x56 + x57*x7) - x58*(x19*x51 + x50*x52);
  double x60 = 0.54191999999999996*x7;
  double x61 = -x28*x51 - x50*x7;
  double x62 = 4*x2*x20*x55 - x58*(x28*x50 - x51*x7);
  double x63 = 0.016767499999999998*x47 + 0.016512499999999999*x48;
  double x64 = 0.016512499999999999*x47 - 0.016767499999999998*x48;
  double x65 = x16*x2;
  double x66 = x56*x7;
  double x67 = 0.02554*x57 - 0.088220000000000007*x65 + 0.02554*x66;
  double x68 = x10*x27;
  double x69 = 0.02554*x23;
  double x70 = x23*x34;
  double x71 = 0.25728000000000001*x16;
  double x72 = x14*x41;
  double x73 = x27*x4;
  double x74 = x23*x43;
  double x75 = x57 + x66;
  double x76 = -x50*x65 + x51*x75;
  double x77 = 4*x55;
  double x78 = x58*(x50*x75 + x51*x65) + x77*(-x21*x7 + x24);
  double x79 = 0.54191999999999996*x65;
  double x80 = x54*x78 + x79;
  double x81 = -x23*x38*x51 + x43*x50;
  double x82 = x20*x77;
  double x83 = x38*x50;
  double x84 = -x38*x82 + x58*(x23*x83 + x43*x51);
  double x85 = x10*x60;
  double x86 = x0*x85 - 0.54191999999999996*x41;
  double x87 = x45*x51;
  double x88 = -x21*x4 + x70;
  double x89 = x58*(x50*x88 + x87) - x77*(x20*x34 + x4*x56);
  double x90 = x45*x50;
  double x91 = x51*x88 - x90;
  double x92 = 0.54191999999999996*x44 - x85;
  double x93 = 0.01821*x16;
  double x94 = x64*x78 + x79;
  double x95 = 0.060165000000000003*x16;
  double x96 = -x76;
  double x97 = x45*x82 + x58*(-x23*x90 + x34*x51);
  double x98 = x23*x87 + x34*x50;
  double x99 = x4*x60;
  double x100 = x0*x99 + 0.54191999999999996*x32;
  double x101 = x10*x21 + x74;
  double x102 = x58*(-x101*x50 + x38*x51) - x77*(x10*x16*x23 - x20*x43);
  double x103 = x101*x51 + x83;
  double x104 = 0.54191999999999996*x37 + x99;
  *val = 0.25728000000000001*x0*(x26*(0.088220000000000007*x19 + x22 - 0.02554*x25) + x30*(x27 + 0.02554*x28)) + 0.01821*x0*(x26*(x46 + x49*x53 - x54*x59) + x30*(x49*x61 + x54*x62 + x60)) + 0.060165000000000003*x0*(x26*(x46 + x53*x63 - x59*x64) + x30*(x60 + x61*x63 + x62*x64)) - 0.052914523900000003*x1*(x15 + x18*x8) - x10*x71*(x14*x32*x67 + x36*(x0*x68 + x38*x69 - 0.088220000000000007*x41) - x39*(-x22*x4 - 0.088220000000000007*x44 + x68 + 0.02554*x70)) + x10*x93*(x10*x14*x2*(x49*x76 + x80) - x36*(x49*x81 - x54*x84 + x86) - x39*(x49*x91 + x54*x89 + x92)) + x10*x95*(x10*x14*x2*(x63*x76 + x94) - x36*(x63*x81 - x64*x84 + x86) - x39*(x63*x91 + x64*x89 + x92)) - 0.052914523900000003*x31*(x15*x31 - x34*x36 + x38*x39) - x4*x71*(x36*(x0*x73 + 0.088220000000000007*x32 + x45*x69) - x39*(x10*x22 + 0.088220000000000007*x37 + x73 + 0.02554*x74) + x67*x72) + x4*x93*(-x36*(x100 - x49*x98 + x54*x97) + x39*(x102*x54 - x103*x49 + x104) + x72*(-x49*x96 + x80)) + x4*x95*(-x36*(x100 - x63*x98 + x64*x97) + x39*(x102*x64 - x103*x63 + x104) + x72*(-x63*x96 + x94)) - 0.052914523900000003*x40*(x15*x40 + x36*x43 - x39*x45);
}
