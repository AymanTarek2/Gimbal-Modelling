

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_6_4(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = cbo[2];
  double x1 = pow(x0, 2);
  double x2 = sbo[1];
  double x3 = sbo[0];
  double x4 = pow(x3, 2);
  double x5 = sbo[2];
  double x6 = pow(x5, 2);
  double x7 = x4*x6;
  double x8 = x1*x4;
  double x9 = cbo[0];
  double x10 = pow(x9, 2);
  double x11 = x10*x6;
  double x12 = x1*x10;
  double x13 = 1.0/(x11 + x12 + x7 + x8);
  double x14 = pow(x2, 2);
  double x15 = cbo[1];
  double x16 = pow(x15, 2);
  double x17 = 1.0/(x11*x14 + x11*x16 + x12*x14 + x12*x16 + x14*x7 + x14*x8 + x16*x7 + x16*x8);
  double x18 = x15*x5;
  double x19 = x2*x5;
  double x20 = cq[0];
  double x21 = x15*x20;
  double x22 = sq[0];
  double x23 = x2*x22;
  double x24 = x0*x23;
  double x25 = x0*x13;
  double x26 = 0.02554*x22;
  double x27 = x17*x19;
  double x28 = x0*x15;
  double x29 = x5*x9;
  double x30 = x0*x3;
  double x31 = x2*x30;
  double x32 = x29 + x31;
  double x33 = x13*x30;
  double x34 = 1.0/x15;
  double x35 = x17*x34;
  double x36 = x2*x35;
  double x37 = x2*x29;
  double x38 = x30 + x37;
  double x39 = x35*(x10*x16 + x14 + x16*x4);
  double x40 = 0.052914523900000003*x5;
  double x41 = x3*x5;
  double x42 = x0*x9;
  double x43 = x2*x42;
  double x44 = x41 - x43;
  double x45 = x13*x42;
  double x46 = x2*x41;
  double x47 = -x42 + x46;
  double x48 = 0.54191999999999996*x19;
  double x49 = M_SQRT2;
  double x50 = sqrt(6);
  double x51 = 0.013937500000000002*x49 + 0.032607499999999998*x50;
  double x52 = x49 - x50;
  double x53 = x49 + x50;
  double x54 = -x21 + x24;
  double x55 = -x19*x52 + x53*x54;
  double x56 = 0.032607499999999998*x49 - 0.013937500000000002*x50;
  double x57 = x15*x22;
  double x58 = x2*x20;
  double x59 = sq[1];
  double x60 = 4*x59;
  double x61 = cq[1];
  double x62 = -x60*(x0*x58 + x57) + x61*(x19*x53 + x52*x54);
  double x63 = -0.54191999999999996*x0;
  double x64 = x22*x5;
  double x65 = x0*x52 + x53*x64;
  double x66 = x20*x60;
  double x67 = -x5*x66 + x61*(-x0*x53 + x52*x64);
  double x68 = 0.016767499999999998*x49 + 0.016512499999999999*x50;
  double x69 = 0.016512499999999999*x49 - 0.016767499999999998*x50;
  double x70 = x0*x57;
  double x71 = x13*(-0.088220000000000007*x18 + 0.02554*x58 + 0.02554*x70);
  double x72 = x27*x34;
  double x73 = x21*x3;
  double x74 = x22*x32;
  double x75 = x39*x5;
  double x76 = 0.088220000000000007*x29;
  double x77 = x21*x9;
  double x78 = x22*x44;
  double x79 = 0.54191999999999996*x18;
  double x80 = x58 + x70;
  double x81 = -x18*x52 + x53*x80;
  double x82 = x60*(-x0*x21 + x23) + x61*(x18*x53 + x52*x80);
  double x83 = x51*x81 + x56*x82 + x79;
  double x84 = -x22*x38*x53 + x44*x52;
  double x85 = x38*x52;
  double x86 = -x38*x66 + x61*(x22*x85 + x44*x53);
  double x87 = -0.54191999999999996*x41 + 0.54191999999999996*x43;
  double x88 = x47*x53;
  double x89 = -x73 + x74;
  double x90 = -x60*(x20*x32 + x3*x57) + x61*(x52*x89 + x88);
  double x91 = x47*x52;
  double x92 = x53*x89 - x91;
  double x93 = -0.54191999999999996*x42 + 0.54191999999999996*x46;
  double x94 = x68*x81 + x69*x82 + x79;
  double x95 = 4*x20*x47*x59 - x61*(x22*x91 - x32*x53);
  double x96 = x22*x88 + x32*x52;
  double x97 = 0.54191999999999996*x29 + 0.54191999999999996*x31;
  double x98 = x77 + x78;
  double x99 = x60*(x20*x44 - x57*x9) + x61*(x38*x53 - x52*x98);
  double x100 = x53*x98 + x85;
  double x101 = 0.54191999999999996*x30 + 0.54191999999999996*x37;
  *val = 0.052914523900000003*x1*x18*x2*(-x13 + x17) - 0.25728000000000001*x28*(-x25*(0.088220000000000007*x19 + 0.02554*x21 - 0.02554*x24) + x27*(0.088220000000000007*x0 + x26*x5)) + 0.01821*x28*(x25*(x48 + x51*x55 + x56*x62) - x27*(-x51*x65 - x56*x67 - x63)) + 0.060165000000000003*x28*(x25*(x48 + x55*x68 + x62*x69) - x27*(-x63 - x65*x68 - x67*x69)) + x32*x40*(x15*x33 + x32*x36 - x38*x39) + 0.25728000000000001*x32*(x30*x71 - x72*(x26*x47 + 0.088220000000000007*x31 + x76) + x75*(x2*x76 + 0.088220000000000007*x30 + 0.02554*x77 + 0.02554*x78)) - 0.01821*x32*(x33*x83 + x72*(-x51*x96 + x56*x95 + x97) - x75*(-x100*x51 + x101 + x56*x99)) - 0.060165000000000003*x32*(x33*x94 + x72*(-x68*x96 + x69*x95 + x97) - x75*(-x100*x68 + x101 + x69*x99)) - x40*x44*(x15*x45 - x36*x44 + x39*x47) - 0.25728000000000001*x44*(x42*x71 - x72*(x26*x38 - 0.088220000000000007*x41 + 0.088220000000000007*x43) + x75*(0.088220000000000007*x42 - 0.088220000000000007*x46 - 0.02554*x73 + 0.02554*x74)) + 0.01821*x44*(x45*x83 + x72*(x51*x84 - x56*x86 + x87) + x75*(x51*x92 + x56*x90 + x93)) + 0.060165000000000003*x44*(x45*x94 + x72*(x68*x84 - x69*x86 + x87) + x75*(x68*x92 + x69*x90 + x93));
}
