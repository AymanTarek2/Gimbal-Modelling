

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_3_7(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1];
  double x1 = sbo[2];
  double x2 = cbo[1];
  double x3 = pow(x1, 2);
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
  double x16 = pow(x0, 2);
  double x17 = pow(x2, 2);
  double x18 = 1.0/(x12*x16 + x12*x17 + x13*x16 + x13*x17 + x16*x6 + x16*x9 + x17*x6 + x17*x9);
  double x19 = x0*x1;
  double x20 = cq[0];
  double x21 = x2*x20;
  double x22 = sq[0];
  double x23 = x0*x22;
  double x24 = x23*x7;
  double x25 = x1*x14;
  double x26 = 0.02554*x22;
  double x27 = x18*x7;
  double x28 = x0*x27;
  double x29 = x1*x2;
  double x30 = x10*x7;
  double x31 = x1*x4;
  double x32 = x0*x31;
  double x33 = -x30 + x32;
  double x34 = x15*x2;
  double x35 = x1*x10;
  double x36 = x4*x7;
  double x37 = x0*x36;
  double x38 = x35 + x37;
  double x39 = 1.0/x2;
  double x40 = x28*x39;
  double x41 = x0*x35;
  double x42 = x36 + x41;
  double x43 = x27*x39*(x11*x17 + x16 + x17*x5);
  double x44 = x0*x30;
  double x45 = x31 - x44;
  double x46 = 0.54191999999999996*x19;
  double x47 = M_SQRT2;
  double x48 = sqrt(6);
  double x49 = 0.013937500000000002*x47 + 0.032607499999999998*x48;
  double x50 = x47 - x48;
  double x51 = x47 + x48;
  double x52 = -x21 + x24;
  double x53 = -x19*x50 + x51*x52;
  double x54 = 0.032607499999999998*x47 - 0.013937500000000002*x48;
  double x55 = sq[1];
  double x56 = x2*x22;
  double x57 = x0*x20;
  double x58 = cq[1];
  double x59 = 4*x55*(x56 + x57*x7) - x58*(x19*x51 + x50*x52);
  double x60 = 0.54191999999999996*x7;
  double x61 = x1*x22;
  double x62 = -x50*x7 - x51*x61;
  double x63 = 4*x1*x20*x55 - x58*(x50*x61 - x51*x7);
  double x64 = 0.016767499999999998*x47 + 0.016512499999999999*x48;
  double x65 = 0.016512499999999999*x47 - 0.016767499999999998*x48;
  double x66 = x56*x7;
  double x67 = -0.088220000000000007*x29 + 0.02554*x57 + 0.02554*x66;
  double x68 = x14*x35;
  double x69 = x21*x4;
  double x70 = x22*x38;
  double x71 = x14*x31;
  double x72 = x10*x21;
  double x73 = x22*x45;
  double x74 = 0.54191999999999996*x29;
  double x75 = x57 + x66;
  double x76 = -x29*x50 + x51*x75;
  double x77 = 4*x55;
  double x78 = x58*(x29*x51 + x50*x75) + x77*(-x21*x7 + x23);
  double x79 = x49*x76 + x54*x78 + x74;
  double x80 = -x22*x42*x51 + x45*x50;
  double x81 = x42*x50;
  double x82 = -x20*x42*x77 + x58*(x22*x81 + x45*x51);
  double x83 = -0.54191999999999996*x31 + 0.54191999999999996*x44;
  double x84 = x33*x51;
  double x85 = -x69 + x70;
  double x86 = x58*(x50*x85 + x84) - x77*(x20*x38 + x4*x56);
  double x87 = x33*x50;
  double x88 = x51*x85 - x87;
  double x89 = -0.54191999999999996*x30 + 0.54191999999999996*x32;
  double x90 = x64*x76 + x65*x78 + x74;
  double x91 = 4*x20*x33*x55 - x58*(x22*x87 - x38*x51);
  double x92 = x22*x84 + x38*x50;
  double x93 = 0.54191999999999996*x36;
  double x94 = x0*x93 + 0.54191999999999996*x35;
  double x95 = x72 + x73;
  double x96 = x58*(x42*x51 - x50*x95) + x77*(-x10*x56 + x20*x45);
  double x97 = x51*x95 + x81;
  double x98 = 0.54191999999999996*x41 + x93;
  *val = 0.052914523900000003*x0*x1*x2*(x15 + x18*x8) - 0.25728000000000001*x29*(x25*(0.088220000000000007*x19 + 0.02554*x21 - 0.02554*x24) + x28*(x1*x26 + 0.088220000000000007*x7)) - 0.01821*x29*(x25*(x46 + x49*x53 - x54*x59) + x28*(x49*x62 + x54*x63 + x60)) - 0.060165000000000003*x29*(x25*(x46 + x53*x64 - x59*x65) + x28*(x60 + x62*x64 + x63*x65)) - 0.052914523900000003*x33*(x34*x4 - x38*x40 + x42*x43) - 0.25728000000000001*x33*(x40*(x26*x33 + 0.088220000000000007*x35 + 0.088220000000000007*x37) - x43*(0.088220000000000007*x36 + 0.088220000000000007*x41 + 0.02554*x72 + 0.02554*x73) + x67*x71) + 0.01821*x33*(-x40*(-x49*x92 + x54*x91 + x94) + x43*(-x49*x97 + x54*x96 + x98) + x71*x79) + 0.060165000000000003*x33*(-x40*(-x64*x92 + x65*x91 + x94) + x43*(-x64*x97 + x65*x96 + x98) + x71*x90) - 0.052914523900000003*x42*(x10*x34 - x33*x43 + x40*x45) - 0.25728000000000001*x42*(x40*(x26*x42 - 0.088220000000000007*x31 + 0.088220000000000007*x44) - x43*(0.088220000000000007*x30 - 0.088220000000000007*x32 - 0.02554*x69 + 0.02554*x70) + x67*x68) - 0.01821*x42*(x40*(x49*x80 - x54*x82 + x83) + x43*(x49*x88 + x54*x86 + x89) - x68*x79) - 0.060165000000000003*x42*(x40*(x64*x80 - x65*x82 + x83) + x43*(x64*x88 + x65*x86 + x89) - x68*x90);
}
