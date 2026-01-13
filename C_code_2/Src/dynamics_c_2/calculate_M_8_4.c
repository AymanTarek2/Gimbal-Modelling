

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_8_4(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[2];
  double x1 = cbo[2];
  double x2 = sbo[1];
  double x3 = pow(x2, 2);
  double x4 = sbo[0];
  double x5 = pow(x4, 2);
  double x6 = pow(x0, 2);
  double x7 = x5*x6;
  double x8 = pow(x1, 2);
  double x9 = x5*x8;
  double x10 = cbo[0];
  double x11 = pow(x10, 2);
  double x12 = x11*x6;
  double x13 = x11*x8;
  double x14 = 1.0/(x12 + x13 + x7 + x9);
  double x15 = cbo[1];
  double x16 = pow(x15, 2);
  double x17 = 1.0/(x12*x16 + x12*x3 + x13*x16 + x13*x3 + x16*x7 + x16*x9 + x3*x7 + x3*x9);
  double x18 = x0*x2;
  double x19 = cq[0];
  double x20 = x15*x19;
  double x21 = 0.02554*x20;
  double x22 = sq[0];
  double x23 = x2*x22;
  double x24 = x1*x23;
  double x25 = x1*x14;
  double x26 = 0.088220000000000007*x1;
  double x27 = x0*x22;
  double x28 = x17*x18;
  double x29 = x1*x4;
  double x30 = x14*x15;
  double x31 = x0*x10;
  double x32 = x2*x29 + x31;
  double x33 = 1.0/x15;
  double x34 = x17*x33;
  double x35 = x2*x34;
  double x36 = x2*x31;
  double x37 = x29 + x36;
  double x38 = x34*(x11*x16 + x16*x5 + x3);
  double x39 = x0*x4;
  double x40 = 0.052914523900000003*x15;
  double x41 = x1*x10;
  double x42 = -x2*x41 + x39;
  double x43 = x2*x39;
  double x44 = -x41 + x43;
  double x45 = 0.54191999999999996*x18;
  double x46 = M_SQRT2;
  double x47 = sqrt(6);
  double x48 = 0.013937500000000002*x46 + 0.032607499999999998*x47;
  double x49 = x46 - x47;
  double x50 = x46 + x47;
  double x51 = -x20 + x24;
  double x52 = -x18*x49 + x50*x51;
  double x53 = 0.032607499999999998*x46 - 0.013937500000000002*x47;
  double x54 = x15*x22;
  double x55 = x19*x2;
  double x56 = sq[1];
  double x57 = 4*x56;
  double x58 = cq[1];
  double x59 = -x57*(x1*x55 + x54) + x58*(x18*x50 + x49*x51);
  double x60 = -0.54191999999999996*x1;
  double x61 = x1*x49 + x27*x50;
  double x62 = x19*x57;
  double x63 = -x0*x62 + x58*(-x1*x50 + x27*x49);
  double x64 = 0.016767499999999998*x46 + 0.016512499999999999*x47;
  double x65 = 0.016512499999999999*x46 - 0.016767499999999998*x47;
  double x66 = x0*x15;
  double x67 = x1*x54;
  double x68 = x14*(0.02554*x55 - 0.088220000000000007*x66 + 0.02554*x67);
  double x69 = x10*x26;
  double x70 = 0.02554*x22;
  double x71 = x28*x33;
  double x72 = x22*x32;
  double x73 = x0*x38;
  double x74 = 0.25728000000000001*x15;
  double x75 = x26*x4;
  double x76 = x22*x42;
  double x77 = 0.54191999999999996*x66;
  double x78 = x55 + x67;
  double x79 = -x49*x66 + x50*x78;
  double x80 = x57*(-x1*x20 + x23) + x58*(x49*x78 + x50*x66);
  double x81 = x14*(x48*x79 + x53*x80 + x77);
  double x82 = -x22*x37*x50 + x42*x49;
  double x83 = x37*x49;
  double x84 = -x37*x62 + x58*(x22*x83 + x42*x50);
  double x85 = 0.54191999999999996*x1;
  double x86 = x10*x85;
  double x87 = x2*x86 - 0.54191999999999996*x39;
  double x88 = x44*x50;
  double x89 = -x20*x4 + x72;
  double x90 = -x57*(x19*x32 + x4*x54) + x58*(x49*x89 + x88);
  double x91 = x44*x49;
  double x92 = x50*x89 - x91;
  double x93 = 0.54191999999999996*x43 - x86;
  double x94 = 0.01821*x15;
  double x95 = x14*(x64*x79 + x65*x80 + x77);
  double x96 = 0.060165000000000003*x15;
  double x97 = 4*x19*x44*x56 - x58*(x22*x91 - x32*x50);
  double x98 = x22*x88 + x32*x49;
  double x99 = x4*x85;
  double x100 = x2*x99 + 0.54191999999999996*x31;
  double x101 = x10*x20 + x76;
  double x102 = x57*(-x10*x54 + x19*x42) + x58*(-x101*x49 + x37*x50);
  double x103 = x101*x50 + x83;
  double x104 = 0.54191999999999996*x36 + x99;
  *val = 0.052914523900000003*x0*x1*x3*(-x14 + x17) - x10*x74*(x41*x68 - x71*(x2*x69 + x37*x70 - 0.088220000000000007*x39) + x73*(-x21*x4 - 0.088220000000000007*x43 + x69 + 0.02554*x72)) + x10*x94*(x41*x81 + x71*(x48*x82 - x53*x84 + x87) + x73*(x48*x92 + x53*x90 + x93)) + x10*x96*(x41*x95 + x71*(x64*x82 - x65*x84 + x87) + x73*(x64*x92 + x65*x90 + x93)) - 0.25728000000000001*x2*(-x25*(0.088220000000000007*x18 + x21 - 0.02554*x24) + x28*(x26 + 0.02554*x27)) + 0.01821*x2*(x25*(x45 + x48*x52 + x53*x59) - x28*(-x48*x61 - x53*x63 - x60)) + 0.060165000000000003*x2*(x25*(x45 + x52*x64 + x59*x65) - x28*(-x60 - x61*x64 - x63*x65)) - x31*x40*(x30*x41 - x35*x42 + x38*x44) - x39*x40*(x29*x30 + x32*x35 - x37*x38) - x4*x74*(x29*x68 - x71*(x2*x75 + 0.088220000000000007*x31 + x44*x70) + x73*(x10*x21 + 0.088220000000000007*x36 + x75 + 0.02554*x76)) + x4*x94*(x29*x81 + x71*(x100 - x48*x98 + x53*x97) - x73*(x102*x53 - x103*x48 + x104)) + x4*x96*(x29*x95 + x71*(x100 - x64*x98 + x65*x97) - x73*(x102*x65 - x103*x64 + x104));
}
