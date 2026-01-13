

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_6_3(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1];
  double x1 = sbo[2];
  double x2 = pow(x1, 2);
  double x3 = sbo[0];
  double x4 = pow(x3, 2);
  double x5 = x2*x4;
  double x6 = cbo[2];
  double x7 = pow(x6, 2);
  double x8 = x4*x7;
  double x9 = cbo[0];
  double x10 = pow(x9, 2);
  double x11 = x10*x2;
  double x12 = x10*x7;
  double x13 = 1.0/(x11 + x12 + x5 + x8);
  double x14 = x13*x2;
  double x15 = pow(x0, 2);
  double x16 = cbo[1];
  double x17 = pow(x16, 2);
  double x18 = 1.0/(x11*x15 + x11*x17 + x12*x15 + x12*x17 + x15*x5 + x15*x8 + x17*x5 + x17*x8);
  double x19 = x0*x1;
  double x20 = cq[0];
  double x21 = x16*x20;
  double x22 = sq[0];
  double x23 = x0*x22;
  double x24 = x23*x6;
  double x25 = x1*x13;
  double x26 = 0.02554*x22;
  double x27 = x18*x6;
  double x28 = x0*x27;
  double x29 = x1*x9;
  double x30 = x3*x6;
  double x31 = x0*x30;
  double x32 = x29 + x31;
  double x33 = x14*x16;
  double x34 = 1.0/x16;
  double x35 = x28*x34;
  double x36 = x0*x29;
  double x37 = x30 + x36;
  double x38 = x27*x34*(x10*x17 + x15 + x17*x4);
  double x39 = x1*x3;
  double x40 = x6*x9;
  double x41 = x0*x40;
  double x42 = x39 - x41;
  double x43 = x0*x39;
  double x44 = -x40 + x43;
  double x45 = 0.54191999999999996*x19;
  double x46 = M_SQRT2;
  double x47 = sqrt(6);
  double x48 = 0.013937500000000002*x46 + 0.032607499999999998*x47;
  double x49 = x46 - x47;
  double x50 = x46 + x47;
  double x51 = -x21 + x24;
  double x52 = -x19*x49 + x50*x51;
  double x53 = 0.032607499999999998*x46 - 0.013937500000000002*x47;
  double x54 = sq[1];
  double x55 = x16*x22;
  double x56 = x0*x20;
  double x57 = cq[1];
  double x58 = 4*x54*(x55 + x56*x6) - x57*(x19*x50 + x49*x51);
  double x59 = 0.54191999999999996*x6;
  double x60 = x1*x22;
  double x61 = -x49*x6 - x50*x60;
  double x62 = 4*x1*x20*x54 - x57*(x49*x60 - x50*x6);
  double x63 = 0.016767499999999998*x46 + 0.016512499999999999*x47;
  double x64 = 0.016512499999999999*x46 - 0.016767499999999998*x47;
  double x65 = x1*x16;
  double x66 = x55*x6;
  double x67 = x13*(0.02554*x56 - 0.088220000000000007*x65 + 0.02554*x66);
  double x68 = x21*x3;
  double x69 = x22*x32;
  double x70 = 0.088220000000000007*x29;
  double x71 = x21*x9;
  double x72 = x22*x42;
  double x73 = 0.54191999999999996*x65;
  double x74 = x56 + x66;
  double x75 = -x49*x65 + x50*x74;
  double x76 = 4*x54;
  double x77 = x57*(x49*x74 + x50*x65) + x76*(-x21*x6 + x23);
  double x78 = x13*(x48*x75 + x53*x77 + x73);
  double x79 = -x22*x37*x50 + x42*x49;
  double x80 = x37*x49;
  double x81 = -x20*x37*x76 + x57*(x22*x80 + x42*x50);
  double x82 = -0.54191999999999996*x39 + 0.54191999999999996*x41;
  double x83 = x44*x50;
  double x84 = -x68 + x69;
  double x85 = x57*(x49*x84 + x83) - x76*(x20*x32 + x3*x55);
  double x86 = x44*x49;
  double x87 = x50*x84 - x86;
  double x88 = -0.54191999999999996*x40 + 0.54191999999999996*x43;
  double x89 = x13*(x63*x75 + x64*x77 + x73);
  double x90 = 4*x20*x44*x54 - x57*(x22*x86 - x32*x50);
  double x91 = x22*x83 + x32*x49;
  double x92 = 0.54191999999999996*x29 + 0.54191999999999996*x31;
  double x93 = x71 + x72;
  double x94 = x57*(x37*x50 - x49*x93) + x76*(x20*x42 - x55*x9);
  double x95 = x50*x93 + x80;
  double x96 = 0.54191999999999996*x30 + 0.54191999999999996*x36;
  *val = -0.052914523900000003*x0*x16*x6*(x14 + x18*x7) + 0.25728000000000001*x16*x6*(x25*(0.088220000000000007*x19 + 0.02554*x21 - 0.02554*x24) + x28*(x1*x26 + 0.088220000000000007*x6)) + 0.01821*x16*x6*(x25*(x45 + x48*x52 - x53*x58) + x28*(x48*x61 + x53*x62 + x59)) + 0.060165000000000003*x16*x6*(x25*(x45 + x52*x63 - x58*x64) + x28*(x59 + x61*x63 + x62*x64)) + 0.052914523900000003*x32*(x3*x33 - x32*x35 + x37*x38) + 0.25728000000000001*x32*(x35*(x26*x44 + 0.088220000000000007*x31 + x70) - x38*(x0*x70 + 0.088220000000000007*x30 + 0.02554*x71 + 0.02554*x72) + x39*x67) - 0.01821*x32*(-x35*(-x48*x91 + x53*x90 + x92) + x38*(-x48*x95 + x53*x94 + x96) + x39*x78) - 0.060165000000000003*x32*(-x35*(-x63*x91 + x64*x90 + x92) + x38*(-x63*x95 + x64*x94 + x96) + x39*x89) - 0.25728000000000001*x42*(x29*x67 + x35*(x26*x37 - 0.088220000000000007*x39 + 0.088220000000000007*x41) - x38*(0.088220000000000007*x40 - 0.088220000000000007*x43 - 0.02554*x68 + 0.02554*x69)) - 0.01821*x42*(-x29*x78 + x35*(x48*x79 - x53*x81 + x82) + x38*(x48*x87 + x53*x85 + x88)) - 0.060165000000000003*x42*(-x29*x89 + x35*(x63*x79 - x64*x81 + x82) + x38*(x63*x87 + x64*x85 + x88)) - 0.052914523900000003*x42*(x33*x9 + x35*x42 - x38*x44);
}
