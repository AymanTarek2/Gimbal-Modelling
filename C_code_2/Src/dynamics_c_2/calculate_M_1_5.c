

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_1_5(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[0];
  double x1 = pow(x0, 2);
  double x2 = sbo[1];
  double x3 = pow(x2, 2);
  double x4 = cbo[1];
  double x5 = pow(x4, 2);
  double x6 = cbo[0];
  double x7 = pow(x6, 2);
  double x8 = cbo[2];
  double x9 = -0.54191999999999996*x8;
  double x10 = M_SQRT2;
  double x11 = sqrt(6);
  double x12 = 0.016767499999999998*x10 + 0.016512499999999999*x11;
  double x13 = x10 - x11;
  double x14 = x10 + x11;
  double x15 = sbo[2];
  double x16 = sq[0];
  double x17 = x15*x16;
  double x18 = x13*x8 + x14*x17;
  double x19 = 0.016512499999999999*x10 - 0.016767499999999998*x11;
  double x20 = cq[0];
  double x21 = sq[1];
  double x22 = 4*x21;
  double x23 = x20*x22;
  double x24 = cq[1];
  double x25 = -x15*x23 + x24*(x13*x17 - x14*x8);
  double x26 = 1.9252800000000001*x19;
  double x27 = x20*x4;
  double x28 = x16*x2 - x27*x8;
  double x29 = 4*x24;
  double x30 = x15*x4;
  double x31 = x16*x4;
  double x32 = x2*x20 + x31*x8;
  double x33 = x13*x32 + x14*x30;
  double x34 = x21*x33 - x28*x29;
  double x35 = x34*x4;
  double x36 = 0.013937500000000002*x10 + 0.032607499999999998*x11;
  double x37 = 0.032607499999999998*x10 - 0.013937500000000002*x11;
  double x38 = 0.58272000000000002*x37;
  double x39 = x0*x15;
  double x40 = x6*x8;
  double x41 = x2*x40;
  double x42 = x39 - x41;
  double x43 = x20*x42 - x31*x6;
  double x44 = x0*x8;
  double x45 = x15*x6;
  double x46 = x2*x45;
  double x47 = x44 + x46;
  double x48 = x14*x47;
  double x49 = x16*x42 + x27*x6;
  double x50 = x13*x49 - x48;
  double x51 = x21*x50 + x29*x43;
  double x52 = x13*x47;
  double x53 = -x23*x47 + x24*(x14*x42 + x16*x52);
  double x54 = x13*x42 - x16*x48;
  double x55 = x2*x44;
  double x56 = x45 + x55;
  double x57 = x0*x31 + x20*x56;
  double x58 = x2*x39;
  double x59 = -x40 + x58;
  double x60 = x14*x59;
  double x61 = -x0*x27 + x16*x56;
  double x62 = x13*x61 + x60;
  double x63 = -x22*x57 + x24*x62;
  double x64 = x13*x59;
  double x65 = x14*x61 - x64;
  double x66 = -0.54191999999999996*x40 + 0.54191999999999996*x58;
  double x67 = x1 + x7;
  double x68 = x2*(x67 - 1);
  double x69 = 0.54191999999999996*x39 - 0.54191999999999996*x41;
  double x70 = x21*x62 + x29*x57;
  double x71 = 4*x20*x21*x59 - x24*(-x14*x56 + x16*x64);
  double x72 = x13*x56 + x16*x60;
  double x73 = x22*x43;
  double x74 = -x24*x50 + x73;
  double x75 = x14*x49 + x52;
  double x76 = 0.54191999999999996*x44 + 0.54191999999999996*x46;
  double x77 = 0.54191999999999996*x45 + 0.54191999999999996*x55;
  double x78 = -x13*x30 + x14*x32;
  double x79 = pow(x78, 2);
  double x80 = pow(x75, 2);
  double x81 = pow(x65, 2);
  double x82 = x2*x67;
  double x83 = x78*x82;
  double x84 = x4*x6;
  double x85 = x75*x84;
  double x86 = x0*x4;
  double x87 = x65*x86;
  double x88 = x34*x82;
  double x89 = x22*x28 + x24*x33;
  double x90 = x82*x89;
  double x91 = x70*x86;
  double x92 = x63*x86;
  double x93 = x51*x84;
  double x94 = x24*x50 - x73;
  double x95 = x84*x94;
  double x96 = x13*x78 - x14*x89;
  double x97 = x13*x75 - x14*x94;
  double x98 = x13*x65 - x14*x63;
  double x99 = x34*x78;
  double x100 = x51*x75;
  double x101 = x65*x70;
  double x102 = x78*x89;
  double x103 = x75*x94;
  double x104 = x63*x65;
  double x105 = cq[2];
  double x106 = x105*x14;
  double x107 = sq[2];
  double x108 = 4*x107;
  double x109 = x105*x13;
  double x110 = x106*x78 + x108*x34 + x109*x89;
  double x111 = x106*x65 + x108*x70 + x109*x63;
  double x112 = x106*x75 + x108*x51 + x109*x94;
  double x113 = x107*x14;
  double x114 = 4*x105;
  double x115 = -x107*x13*x89 - x113*x78 + x114*x34;
  double x116 = -x107*x13*x63 - x113*x65 + x114*x70;
  double x117 = x107*x13*x94 + x113*x75 - x114*x51;
  *val = (1.0/128.0)*(-x26*x35*(-x12*x18 - x19*x25 - x9) - x26*x51*(-x12*x54 + x19*x53 + x68*(x12*x65 + x19*x63 + x66) + x69) - x26*x70*(-x12*x72 + x19*x71 + x68*(-x12*x75 + x19*x74 + x76) + x77) - x35*x38*(-x18*x36 - x25*x37 - x9) - x38*x51*(-x36*x54 + x37*x53 + x68*(x36*x65 + x37*x63 + x66) + x69) - x38*x70*(-x36*x72 + x37*x71 + x68*(-x36*x75 + x37*x74 + x76) + x77) - (x100 + x101 + x99)*(6.8000000000000013e-10*x83 + 6.8000000000000013e-10*x85 - 6.8000000000000013e-10*x87 + 0.00054005738000000004*x88 + 2.3100000000000001e-9*x90 - 0.00054005738000000004*x91 - 2.3100000000000001e-9*x92 + 0.00054005738000000004*x93 + 2.3100000000000001e-9*x95) - (x102 + x103 + x104)*(-4.908071e-5*x83 - 4.908071e-5*x85 + 4.908071e-5*x87 + 2.3100000000000001e-9*x88 + 0.00050018127000000005*x90 - 2.3100000000000001e-9*x91 - 0.00050018127000000005*x92 + 2.3100000000000001e-9*x93 + 0.00050018127000000005*x95) - (x79 + x80 + x81)*(0.00015755995000000001*x83 + 0.00015755995000000001*x85 - 0.00015755995000000001*x87 + 6.8000000000000013e-10*x88 - 4.908071e-5*x90 - 6.8000000000000013e-10*x91 + 4.908071e-5*x92 + 6.8000000000000013e-10*x93 - 4.908071e-5*x95) - 4*(x83 + x85 - x87)*(1.7000000000000003e-10*x100 + 1.7000000000000003e-10*x101 - 1.22701775e-5*x102 - 1.22701775e-5*x103 - 1.22701775e-5*x104 + 3.9389987500000003e-5*x79 + 3.9389987500000003e-5*x80 + 3.9389987500000003e-5*x81 + 1.7000000000000003e-10*x99) - 4*(x88 - x91 + x93)*(0.00013501434500000001*x100 + 0.00013501434500000001*x101 + 5.7750000000000002e-10*x102 + 5.7750000000000002e-10*x103 + 5.7750000000000002e-10*x104 + 1.7000000000000003e-10*x79 + 1.7000000000000003e-10*x80 + 1.7000000000000003e-10*x81 + 0.00013501434500000001*x99) - 4*(x90 - x92 + x95)*(5.7750000000000002e-10*x100 + 5.7750000000000002e-10*x101 + 0.00012504531750000001*x102 + 0.00012504531750000001*x103 + 0.00012504531750000001*x104 - 1.22701775e-5*x79 - 1.22701775e-5*x80 - 1.22701775e-5*x81 + 5.7750000000000002e-10*x99) - 3.6127437500000003e-6*(x110*x78 + x111*x65 + x112*x75)*(x110*x82 - x111*x86 + x112*x84) - 3.6127437500000003e-6*(-x115*x78 - x116*x65 + x117*x75)*(x0*x116*x4 - x115*x82 + x117*x84) + 6.6545237500000004e-6*(x65*x98 + x75*x97 + x78*x96)*(-x82*x96 - x84*x97 + x86*x98))/(x1*x3 + x1*x5 + x3*x7 + x5*x7);
}
