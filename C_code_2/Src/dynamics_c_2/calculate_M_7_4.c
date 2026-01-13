

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_7_4(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1];
  double x1 = cbo[1];
  double x2 = cbo[2];
  double x3 = sbo[2];
  double x4 = pow(x3, 2);
  double x5 = sbo[0];
  double x6 = pow(x5, 2);
  double x7 = x4*x6;
  double x8 = pow(x2, 2);
  double x9 = x6*x8;
  double x10 = cbo[0];
  double x11 = pow(x10, 2);
  double x12 = x11*x4;
  double x13 = x11*x8;
  double x14 = 1.0/(x12 + x13 + x7 + x9);
  double x15 = pow(x0, 2);
  double x16 = pow(x1, 2);
  double x17 = 1.0/(x12*x15 + x12*x16 + x13*x15 + x13*x16 + x15*x7 + x15*x9 + x16*x7 + x16*x9);
  double x18 = x0*x3;
  double x19 = cq[0];
  double x20 = x1*x19;
  double x21 = sq[0];
  double x22 = x0*x21;
  double x23 = x2*x22;
  double x24 = x14*x2;
  double x25 = 0.02554*x21;
  double x26 = x17*x18;
  double x27 = x10*x2;
  double x28 = x3*x5;
  double x29 = x0*x28;
  double x30 = -x27 + x29;
  double x31 = x2*x5;
  double x32 = x14*x31;
  double x33 = x10*x3;
  double x34 = x0*x31;
  double x35 = x33 + x34;
  double x36 = 1.0/x1;
  double x37 = x17*x36;
  double x38 = x0*x37;
  double x39 = x0*x33;
  double x40 = x31 + x39;
  double x41 = x37*(x11*x16 + x15 + x16*x6);
  double x42 = 0.052914523900000003*x3;
  double x43 = x14*x27;
  double x44 = x0*x27;
  double x45 = x28 - x44;
  double x46 = 0.54191999999999996*x18;
  double x47 = M_SQRT2;
  double x48 = sqrt(6);
  double x49 = 0.013937500000000002*x47 + 0.032607499999999998*x48;
  double x50 = x47 - x48;
  double x51 = x47 + x48;
  double x52 = -x20 + x23;
  double x53 = -x18*x50 + x51*x52;
  double x54 = 0.032607499999999998*x47 - 0.013937500000000002*x48;
  double x55 = x1*x21;
  double x56 = x0*x19;
  double x57 = 4*sq[1];
  double x58 = cq[1];
  double x59 = -x57*(x2*x56 + x55) + x58*(x18*x51 + x50*x52);
  double x60 = -0.54191999999999996*x2;
  double x61 = x21*x3;
  double x62 = x2*x50 + x51*x61;
  double x63 = x19*x57;
  double x64 = -x3*x63 + x58*(-x2*x51 + x50*x61);
  double x65 = x1*x3;
  double x66 = 0.016767499999999998*x47 + 0.016512499999999999*x48;
  double x67 = 0.016512499999999999*x47 - 0.016767499999999998*x48;
  double x68 = x2*x55;
  double x69 = 0.02554*x56 - 0.088220000000000007*x65 + 0.02554*x68;
  double x70 = x26*x36;
  double x71 = x20*x5;
  double x72 = x21*x35;
  double x73 = x3*x41;
  double x74 = x10*x20;
  double x75 = x21*x45;
  double x76 = x56 + x68;
  double x77 = -x50*x65 + x51*x76;
  double x78 = x57*(-x2*x20 + x22) + x58*(x50*x76 + x51*x65);
  double x79 = 0.54191999999999996*x65;
  double x80 = x54*x78 + x79;
  double x81 = -x21*x40*x51 + x45*x50;
  double x82 = x40*x50;
  double x83 = -x40*x63 + x58*(x21*x82 + x45*x51);
  double x84 = 0.54191999999999996*x27;
  double x85 = x0*x84 - 0.54191999999999996*x28;
  double x86 = x30*x51;
  double x87 = -x71 + x72;
  double x88 = -x57*(x19*x35 + x5*x55) + x58*(x50*x87 + x86);
  double x89 = x30*x50;
  double x90 = x51*x87 - x89;
  double x91 = 0.54191999999999996*x29 - x84;
  double x92 = x67*x78 + x79;
  double x93 = -x77;
  double x94 = x30*x63 + x58*(-x21*x89 + x35*x51);
  double x95 = x21*x86 + x35*x50;
  double x96 = 0.54191999999999996*x33 + 0.54191999999999996*x34;
  double x97 = x74 + x75;
  double x98 = -x57*(x1*x10*x21 - x19*x45) + x58*(x40*x51 - x50*x97);
  double x99 = x51*x97 + x82;
  double x100 = 0.54191999999999996*x31 + 0.54191999999999996*x39;
  *val = -0.052914523900000003*x0*x1*x2*x4*(-x14 + x17) + 0.25728000000000001*x1*x3*(-x24*(0.088220000000000007*x18 + 0.02554*x20 - 0.02554*x23) + x26*(0.088220000000000007*x2 + x25*x3)) - x30*x42*(x1*x32 + x35*x38 - x40*x41) - 0.25728000000000001*x30*(x32*x69 - x70*(x25*x30 + 0.088220000000000007*x33 + 0.088220000000000007*x34) + x73*(0.088220000000000007*x31 + 0.088220000000000007*x39 + 0.02554*x74 + 0.02554*x75)) + 0.01821*x30*(x32*(-x49*x93 + x80) + x70*(-x49*x95 + x54*x94 + x96) - x73*(x100 - x49*x99 + x54*x98)) + 0.060165000000000003*x30*(x32*(-x66*x93 + x92) + x70*(-x66*x95 + x67*x94 + x96) - x73*(x100 - x66*x99 + x67*x98)) - x40*x42*(x1*x43 + x30*x41 - x38*x45) - 0.25728000000000001*x40*(x43*x69 - x70*(x25*x40 - 0.088220000000000007*x28 + 0.088220000000000007*x44) + x73*(0.088220000000000007*x27 - 0.088220000000000007*x29 - 0.02554*x71 + 0.02554*x72)) + 0.01821*x40*(x43*(x49*x77 + x80) + x70*(x49*x81 - x54*x83 + x85) + x73*(x49*x90 + x54*x88 + x91)) + 0.060165000000000003*x40*(x43*(x66*x77 + x92) + x70*(x66*x81 - x67*x83 + x85) + x73*(x66*x90 + x67*x88 + x91)) - 0.01821*x65*(x24*(x46 + x49*x53 + x54*x59) - x26*(-x49*x62 - x54*x64 - x60)) - 0.060165000000000003*x65*(x24*(x46 + x53*x66 + x59*x67) - x26*(-x60 - x62*x66 - x64*x67));
}
