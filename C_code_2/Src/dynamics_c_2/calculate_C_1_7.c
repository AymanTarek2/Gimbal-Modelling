

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_1_7(const double dq[3], const double base_dori[3], const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = M_SQRT2;
  double x1 = sqrt(6);
  double x2 = 0.016512499999999999*x0 - 0.016767499999999998*x1;
  double x3 = 0.030082500000000002*x2;
  double x4 = sbo[1];
  double x5 = cq[0];
  double x6 = x4*x5;
  double x7 = cbo[2];
  double x8 = sq[0];
  double x9 = cbo[1];
  double x10 = x8*x9;
  double x11 = x10*x7 + x6;
  double x12 = cq[1];
  double x13 = 4*x12;
  double x14 = x11*x13;
  double x15 = x4*x8;
  double x16 = x5*x9;
  double x17 = x15 - x16*x7;
  double x18 = x0 - x1;
  double x19 = sq[1];
  double x20 = x18*x19;
  double x21 = sbo[2];
  double x22 = x21*x9;
  double x23 = x22*(-x14 - x17*x20);
  double x24 = 0.032607499999999998*x0 - 0.013937500000000002*x1;
  double x25 = 0.0091050000000000002*x24;
  double x26 = -x14 - x17*x20;
  double x27 = sbo[0];
  double x28 = cbo[0];
  double x29 = x21*x28;
  double x30 = x27*x7;
  double x31 = x29 + x30*x4;
  double x32 = -x16*x27 + x31*x8;
  double x33 = x10*x27 + x31*x5;
  double x34 = x20*x33;
  double x35 = -x13*x32 + x34;
  double x36 = x28*x7;
  double x37 = x21*x27;
  double x38 = -x36 + x37*x4;
  double x39 = 0.030082500000000002*x38;
  double x40 = x2*x39;
  double x41 = 0.0091050000000000002*x38;
  double x42 = x24*x41;
  double x43 = x13*x32 - x34;
  double x44 = x29*x4 + x30;
  double x45 = x16*x28;
  double x46 = -x36*x4 + x37;
  double x47 = x45 + x46*x8;
  double x48 = x10*x28;
  double x49 = x46*x5 - x48;
  double x50 = x20*x49;
  double x51 = x13*x47 - x50;
  double x52 = -x13*x47 + x50;
  double x53 = x0 + x1;
  double x54 = x22*(-x13*x16*x21 + x19*(-x10*x18*x21 + x53*x7*x9));
  double x55 = x21*x53;
  double x56 = -4*x12*x17 + x19*(x11*x18 + x55*x9);
  double x57 = x7*x9;
  double x58 = x13*x5;
  double x59 = x44*x58;
  double x60 = -x46;
  double x61 = x19*(x18*x44*x8 - x53*x60) + x59;
  double x62 = -x38;
  double x63 = x31*x53;
  double x64 = x18*x8;
  double x65 = x19*(x62*x64 + x63) + x58*x62;
  double x66 = x13*x33;
  double x67 = x18*x32;
  double x68 = x19*(x38*x53 + x67) + x66;
  double x69 = x31*x68;
  double x70 = x18*x47 - x44*x53;
  double x71 = x13*x49 + x19*x70;
  double x72 = pow(x4, 2);
  double x73 = pow(x28, 2);
  double x74 = pow(x27, 2);
  double x75 = pow(x9, 2);
  double x76 = x73*x75 + x74*x75;
  double x77 = x19*(x21*x64 - x53*x7) + x21*x58;
  double x78 = -x21*x77;
  double x79 = x75*x78;
  double x80 = -x19*(x44*x64 + x46*x53) - x59;
  double x81 = x2*x80;
  double x82 = -x68;
  double x83 = x4*(x73 + x74 - 1);
  double x84 = x82*x83;
  double x85 = x24*x80;
  double x86 = x38*x64 - x63;
  double x87 = 4*x12*x38*x5 + x19*x86;
  double x88 = x2*x87;
  double x89 = -x19*x70;
  double x90 = x13*x49 - x89;
  double x91 = x2*x90;
  double x92 = x24*x87;
  double x93 = x24*x90;
  double x94 = 0.030082500000000002*x44;
  double x95 = x2*x94;
  double x96 = 0.0091050000000000002*x44;
  double x97 = x24*x96;
  double x98 = x19*(-x53*x62 + x67) + x66;
  double x99 = x13*(x48 + x5*x60) + x19*(x18*(-x45 + x60*x8) + x44*x53);
  double x100 = x62*x71;
  double x101 = x13*(x10 + x6*x7);
  double x102 = x4*x55;
  double x103 = x15*x7 - x16;
  double x104 = x101 + x19*(x102 + x103*x18);
  double x105 = x104*x21;
  double x106 = pow(x21, 2);
  double x107 = x106*x74;
  double x108 = pow(x7, 2);
  double x109 = x108*x74;
  double x110 = x106*x73;
  double x111 = x108*x73;
  double x112 = 1.0/(x107 + x109 + x110 + x111);
  double x113 = x112*x2;
  double x114 = 1.0/(x107*x72 + x107*x75 + x109*x72 + x109*x75 + x110*x72 + x110*x75 + x111*x72 + x111*x75);
  double x115 = x112*x24;
  double x116 = -x56;
  double x117 = x116*x29;
  double x118 = x114*x4;
  double x119 = 1.0/x9;
  double x120 = x119*x7;
  double x121 = x118*x120;
  double x122 = x72 + x76;
  double x123 = x116*x37;
  double x124 = x118*x2;
  double x125 = x120*(x19*x86 + x38*x58);
  double x126 = x114*x122;
  double x127 = x120*x126*(4*x12*x49 - x89);
  double x128 = x118*x24;
  double x129 = x22*(-x101 + x19*(-x102 - x103*x18));
  double x130 = x53*x9;
  double x131 = x13*(-x15*x27 + x27*x5*x7*x9) + x19*(x130*x37 + x18*(x10*x30 + x27*x6));
  double x132 = x13*(x15*x28 - x16*x36) + x19*(-x130*x29 + x18*(-x10*x36 - x28*x6));
  double x133 = x37*x68;
  double x134 = -x104*x7;
  double x135 = x113*x116;
  double x136 = x119*x21;
  double x137 = x118*x136;
  double x138 = x126*x136;
  double x139 = x138*x82;
  double x140 = x115*x116;
  *val = dq[0]*(0.030082500000000002*x2*x21*x26*x9 + 0.030082500000000002*x2*x44*x51 + 0.030082500000000002*x2*x44*x52 + 0.0091050000000000002*x21*x24*x26*x9 - x23*x25 - x23*x3 + 0.0091050000000000002*x24*x44*x51 + 0.0091050000000000002*x24*x44*x52 - x35*x40 - x35*x42 - x40*x43 - x42*x43) + base_dori[0]*(x100*x25 + x100*x3 + 0.030082500000000002*x22*(-x105*x113 + x114*x2*x4*x7*x77) + 0.0091050000000000002*x22*(-x105*x115 + x114*x24*x4*x7*x77) - x39*(x113*x123 - x124*x125 + x127*x2) - x40*x99 - x41*(x115*x123 - x125*x128 + x127*x24) - x42*x99 - x68*x95 - x68*x97 + x94*(-x113*x117 + x114*x119*x122*x2*x7*x82 - x121*x81) + x95*x98 + x96*(x114*x119*x122*x24*x7*x82 - x115*x117 - x121*x85) + x97*x98) + base_dori[1]*(-x129*x25 - x129*x3 - x131*x40 - x131*x42 + 0.030082500000000002*x132*x2*x44 + 0.0091050000000000002*x132*x24*x44 - x133*x25*x9 - x133*x3*x9 + 0.030082500000000002*x2*x21*x28*x71*x9 + 0.030082500000000002*x2*x21*x4*x56 + 0.0091050000000000002*x21*x24*x28*x71*x9 + 0.0091050000000000002*x21*x24*x4*x56 + 0.030082500000000002*x21*x9*(x113*x134 + x124*x78) + 0.0091050000000000002*x21*x9*(x115*x134 + x128*x78) - x39*(x135*x30 + x137*x88 - x138*x91) - x41*(x137*x92 - x138*x93 + x140*x30) - x94*(x135*x36 - x137*x81 + x139*x2) - x96*(-x137*x85 + x139*x24 + x140*x36)) + base_dori[2]*(0.030082500000000002*x2*x44*x61 + 0.030082500000000002*x2*x60*x71 + 0.0091050000000000002*x24*x44*x61 + 0.0091050000000000002*x24*x60*x71 - x25*x54 - x25*x56*x57 - x25*x69 - x3*x54 - x3*x56*x57 - x3*x69 - x40*x65 - x42*x65 - 1.0/2.0*(-0.060165000000000003*x2*x79 - 0.01821*x24*x79 + 0.060165000000000003*x38*(x83*x91 + x88) + 0.01821*x38*(x83*x93 + x92) + 0.060165000000000003*x44*(-x2*x84 - x81) + 0.01821*x44*(-x24*x84 - x85))/(x72*x73 + x72*x74 + x76));
}
