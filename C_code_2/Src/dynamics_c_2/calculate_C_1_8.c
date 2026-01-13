

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_1_8(const double dq[3], const double base_dori[3], const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1];
  double x1 = M_SQRT2;
  double x2 = sqrt(6);
  double x3 = 0.016512499999999999*x1 - 0.016767499999999998*x2;
  double x4 = cq[0];
  double x5 = x0*x4;
  double x6 = cbo[2];
  double x7 = sq[0];
  double x8 = cbo[1];
  double x9 = x7*x8;
  double x10 = x5 + x6*x9;
  double x11 = cq[1];
  double x12 = 4*x11;
  double x13 = x10*x12;
  double x14 = x0*x7;
  double x15 = x14 - x4*x6*x8;
  double x16 = x1 - x2;
  double x17 = sq[1];
  double x18 = x16*x17;
  double x19 = -x13 - x15*x18;
  double x20 = 0.032607499999999998*x1 - 0.013937500000000002*x2;
  double x21 = -x13 - x15*x18;
  double x22 = 0.030082500000000002*x0;
  double x23 = x22*x3;
  double x24 = 0.0091050000000000002*x0;
  double x25 = x20*x24;
  double x26 = sbo[0];
  double x27 = x4*x8;
  double x28 = sbo[2];
  double x29 = cbo[0];
  double x30 = x28*x29;
  double x31 = x26*x6;
  double x32 = x0*x31 + x30;
  double x33 = -x26*x27 + x32*x7;
  double x34 = x26*x9 + x32*x4;
  double x35 = x18*x34;
  double x36 = -x12*x33 + x35;
  double x37 = 0.030082500000000002*x8;
  double x38 = x26*x37;
  double x39 = x3*x38;
  double x40 = 0.0091050000000000002*x8;
  double x41 = x26*x40;
  double x42 = x20*x41;
  double x43 = x12*x33 - x35;
  double x44 = x27*x29;
  double x45 = x26*x28;
  double x46 = x29*x6;
  double x47 = -x0*x46 + x45;
  double x48 = x44 + x47*x7;
  double x49 = x29*x9;
  double x50 = x4*x47 - x49;
  double x51 = x18*x50;
  double x52 = x12*x48 - x51;
  double x53 = -x12*x48 + x51;
  double x54 = x1 + x2;
  double x55 = -x12*x27*x28 + x17*(-x16*x28*x9 + x54*x6*x8);
  double x56 = x0*x30 + x31;
  double x57 = x12*x4;
  double x58 = x56*x57;
  double x59 = -x47;
  double x60 = x17*(x16*x56*x7 - x54*x59) + x58;
  double x61 = x29*x37;
  double x62 = x3*x61;
  double x63 = x0*x45 - x46;
  double x64 = -x63;
  double x65 = x16*x7;
  double x66 = x17*(x32*x54 + x64*x65) + x57*x64;
  double x67 = x29*x40;
  double x68 = x20*x67;
  double x69 = pow(x0, 2);
  double x70 = pow(x29, 2);
  double x71 = pow(x26, 2);
  double x72 = pow(x8, 2);
  double x73 = x70*x72 + x71*x72;
  double x74 = x17*(x28*x65 - x54*x6) + x28*x57;
  double x75 = -x0*x74;
  double x76 = x3*x75;
  double x77 = x20*x75;
  double x78 = -x17*(x47*x54 + x56*x65) - x58;
  double x79 = x3*x78;
  double x80 = x12*x34;
  double x81 = x16*x33;
  double x82 = x17*(x54*x63 + x81) + x80;
  double x83 = -x82;
  double x84 = x0*(x70 + x71 - 1);
  double x85 = x3*x84;
  double x86 = x20*x78;
  double x87 = x20*x83;
  double x88 = -x32*x54 + x63*x65;
  double x89 = x17*x88 + x57*x63;
  double x90 = x3*x89;
  double x91 = x16*x48 - x54*x56;
  double x92 = -x17*x91;
  double x93 = 4*x11*x50 - x92;
  double x94 = x20*x89;
  double x95 = x20*x93;
  double x96 = x12*(x4*x59 + x49) + x17*(x16*(-x44 + x59*x7) + x54*x56);
  double x97 = x17*(-x54*x64 + x81) + x80;
  double x98 = x12*x50 + x17*x91;
  double x99 = x12*(x5*x6 + x9);
  double x100 = x28*x54;
  double x101 = x0*x100;
  double x102 = x14*x6 - x27;
  double x103 = x17*(x101 + x102*x16) + x99;
  double x104 = x103*x28;
  double x105 = pow(x28, 2);
  double x106 = x105*x71;
  double x107 = pow(x6, 2);
  double x108 = x107*x71;
  double x109 = x105*x70;
  double x110 = x107*x70;
  double x111 = 1.0/(x106 + x108 + x109 + x110);
  double x112 = x111*x3;
  double x113 = 1.0/(x106*x69 + x106*x72 + x108*x69 + x108*x72 + x109*x69 + x109*x72 + x110*x69 + x110*x72);
  double x114 = x111*x20;
  double x115 = -4*x11*x15 + x17*(x10*x16 + x100*x8);
  double x116 = -x115;
  double x117 = x112*x116;
  double x118 = 1.0/x8;
  double x119 = x113*x6;
  double x120 = x0*x118*x119;
  double x121 = x118*(x69 + x73);
  double x122 = x119*x121;
  double x123 = x3*x83;
  double x124 = x114*x116;
  double x125 = x120*(4*x11*x4*x63 + x17*x88);
  double x126 = x122*(x12*x50 - x92);
  double x127 = x17*(-x101 - x102*x16) - x99;
  double x128 = x54*x8;
  double x129 = x12*(-x14*x26 + x26*x4*x6*x8) + x17*(x128*x45 + x16*(x26*x5 + x31*x9));
  double x130 = x12*(x14*x29 - x27*x46) + x17*(-x128*x30 + x16*(-x29*x5 - x46*x9));
  double x131 = x29*x98;
  double x132 = -x103*x6;
  double x133 = x113*x28;
  double x134 = x0*x118*x133;
  double x135 = x121*x133;
  *val = dq[0]*(0.0091050000000000002*x0*x19*x20 + 0.030082500000000002*x0*x19*x3 + 0.0091050000000000002*x20*x29*x52*x8 + 0.0091050000000000002*x20*x29*x53*x8 - x21*x23 - x21*x25 + 0.030082500000000002*x29*x3*x52*x8 + 0.030082500000000002*x29*x3*x53*x8 - x36*x39 - x36*x42 - x39*x43 - x42*x43) + base_dori[0]*(0.0091050000000000002*x20*x29*x8*x97 - x22*(x0*x113*x3*x6*x74 - x104*x112) - x24*(x0*x113*x20*x6*x74 - x104*x114) + 0.030082500000000002*x29*x3*x8*x97 - x38*(x117*x45 - x125*x3 + x126*x3) - x39*x96 - x39*x98 - x41*(x124*x45 - x125*x20 + x126*x20) - x42*x96 - x42*x98 - x61*(x117*x30 + x120*x79 - x122*x123) - x62*x82 - x67*(x120*x86 - x122*x87 + x124*x30) - x68*x82) + base_dori[1]*(0.0091050000000000002*x0*x127*x20 + 0.030082500000000002*x0*x127*x3 + 0.0091050000000000002*x0*x20*x26*x82 + 0.030082500000000002*x0*x26*x3*x82 + 0.0091050000000000002*x115*x20*x8 + 0.030082500000000002*x115*x3*x8 - x129*x39 - x129*x42 + 0.0091050000000000002*x130*x20*x29*x8 + 0.030082500000000002*x130*x29*x3*x8 - x131*x23 - x131*x25 - x22*(x112*x132 + x133*x76) - x24*(x114*x132 + x133*x77) - x38*(x117*x31 + x134*x90 - x135*x3*x93) - x41*(x124*x31 + x134*x94 - x135*x95) - x61*(x117*x46 + x123*x135 - x134*x79) - x67*(x124*x46 - x134*x86 + x135*x87)) + base_dori[2]*(x23*x55 + x25*x55 - x39*x66 - x42*x66 + x60*x62 + x60*x68 - 1.0/2.0*x8*(0.01821*x26*(x84*x95 + x94) + 0.060165000000000003*x26*(x85*x93 + x90) - 0.060165000000000003*x29*(x79 + x83*x85) - 0.01821*x29*(x84*x87 + x86) + 0.060165000000000003*x76 + 0.01821*x77)/(x69*x70 + x69*x71 + x73));
}
