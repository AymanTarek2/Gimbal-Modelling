

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_8_1(const double dq[3], const double base_dori[3], const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1];
  double x1 = sq[0];
  double x2 = x0*x1;
  double x3 = cbo[1];
  double x4 = cbo[2];
  double x5 = cq[0];
  double x6 = x2 - x3*x4*x5;
  double x7 = sq[1];
  double x8 = 4*x7;
  double x9 = cq[1];
  double x10 = sbo[2];
  double x11 = M_SQRT2;
  double x12 = sqrt(6);
  double x13 = x11 + x12;
  double x14 = x10*x13;
  double x15 = x11 - x12;
  double x16 = x0*x5;
  double x17 = x1*x3;
  double x18 = x16 + x17*x4;
  double x19 = x14*x3 + x15*x18;
  double x20 = x0*(x19*x9 + x6*x8);
  double x21 = 0.016512499999999999*x11 - 0.016767499999999998*x12;
  double x22 = 0.060165000000000003*x21;
  double x23 = 0.032607499999999998*x11 - 0.013937500000000002*x12;
  double x24 = 0.01821*x23;
  double x25 = sbo[0];
  double x26 = 0.060165000000000003*x25;
  double x27 = cbo[0];
  double x28 = x10*x27;
  double x29 = x25*x4;
  double x30 = x0*x29 + x28;
  double x31 = x17*x25 + x30*x5;
  double x32 = x27*x4;
  double x33 = x10*x25;
  double x34 = x0*x33 - x32;
  double x35 = x3*x5;
  double x36 = x1*x30 - x25*x35;
  double x37 = x15*x36;
  double x38 = x13*x34 + x37;
  double x39 = x3*(-x31*x8 + x38*x9);
  double x40 = 0.01821*x25;
  double x41 = 0.060165000000000003*x27;
  double x42 = x17*x27;
  double x43 = -x0*x32 + x33;
  double x44 = -x42 + x43*x5;
  double x45 = x0*x28 + x29;
  double x46 = x13*x45;
  double x47 = x27*x35;
  double x48 = x1*x43 + x47;
  double x49 = x15*x48 - x46;
  double x50 = x3*(-x44*x8 + x49*x9);
  double x51 = 0.01821*x27;
  double x52 = 4*x9;
  double x53 = x18*x52;
  double x54 = x15*x7;
  double x55 = -x53 - x54*x6;
  double x56 = 0.030082500000000002*x0;
  double x57 = x21*x56;
  double x58 = 0.0091050000000000002*x0;
  double x59 = x23*x58;
  double x60 = -x53 - x54*x6;
  double x61 = x31*x54;
  double x62 = -x36*x52 + x61;
  double x63 = 0.030082500000000002*x3;
  double x64 = x25*x63;
  double x65 = x21*x64;
  double x66 = 0.0091050000000000002*x3;
  double x67 = x25*x66;
  double x68 = x23*x67;
  double x69 = x36*x52 - x61;
  double x70 = x44*x54;
  double x71 = x48*x52 - x70;
  double x72 = x27*x63;
  double x73 = x21*x72;
  double x74 = x27*x66;
  double x75 = x23*x74;
  double x76 = -x48*x52 + x70;
  double x77 = -x10*x35*x52 + x7*(-x10*x15*x17 + x13*x3*x4);
  double x78 = x5*x52;
  double x79 = x45*x78;
  double x80 = -x43;
  double x81 = x7*(x1*x15*x45 - x13*x80) + x79;
  double x82 = -x34;
  double x83 = x1*x15;
  double x84 = x7*(x13*x30 + x82*x83) + x78*x82;
  double x85 = pow(x0, 2);
  double x86 = pow(x27, 2);
  double x87 = pow(x25, 2);
  double x88 = pow(x3, 2);
  double x89 = x86*x88 + x87*x88;
  double x90 = x10*x78 + x7*(x10*x83 - x13*x4);
  double x91 = -x0*x90;
  double x92 = -x7*(x13*x43 + x45*x83) - x79;
  double x93 = x21*x92;
  double x94 = x31*x52;
  double x95 = x38*x7 + x94;
  double x96 = -x95;
  double x97 = x0*(x86 + x87 - 1);
  double x98 = x21*x97;
  double x99 = x23*x92;
  double x100 = x23*x96;
  double x101 = -x13*x30 + x34*x83;
  double x102 = x101*x7 + x34*x78;
  double x103 = x102*x21;
  double x104 = -x49*x7;
  double x105 = -x104 + 4*x44*x9;
  double x106 = x102*x23;
  double x107 = x105*x23;
  double x108 = x52*(x42 + x5*x80) + x7*(x15*(x1*x80 - x47) + x46);
  double x109 = x7*(-x13*x82 + x37) + x94;
  double x110 = x44*x52 + x49*x7;
  double x111 = x52*(x16*x4 + x17);
  double x112 = x0*x14;
  double x113 = x2*x4 - x35;
  double x114 = x111 + x7*(x112 + x113*x15);
  double x115 = x10*x114;
  double x116 = pow(x10, 2);
  double x117 = x116*x87;
  double x118 = pow(x4, 2);
  double x119 = x118*x87;
  double x120 = x116*x86;
  double x121 = x118*x86;
  double x122 = 1.0/(x117 + x119 + x120 + x121);
  double x123 = x122*x21;
  double x124 = 1.0/(x117*x85 + x117*x88 + x119*x85 + x119*x88 + x120*x85 + x120*x88 + x121*x85 + x121*x88);
  double x125 = x122*x23;
  double x126 = x19*x7 - 4*x6*x9;
  double x127 = -x126;
  double x128 = x123*x127;
  double x129 = x0*x4;
  double x130 = 1.0/x3;
  double x131 = x124*x130;
  double x132 = x129*x131;
  double x133 = x85 + x89;
  double x134 = x133*x4;
  double x135 = x124*x21;
  double x136 = x130*x135;
  double x137 = x136*x96;
  double x138 = x125*x127;
  double x139 = x100*x131;
  double x140 = x129*(x101*x7 + 4*x34*x5*x9);
  double x141 = x134*(-x104 + x44*x52);
  double x142 = x124*x23;
  double x143 = x130*x142;
  double x144 = -x111 + x7*(-x112 - x113*x15);
  double x145 = x13*x3;
  double x146 = x52*(-x2*x25 + x25*x3*x4*x5) + x7*(x145*x33 + x15*(x16*x25 + x17*x29));
  double x147 = x52*(x2*x27 - x32*x35) + x7*(-x145*x28 + x15*(-x16*x27 - x17*x32));
  double x148 = x25*x95;
  double x149 = x110*x27;
  double x150 = -x114*x4;
  double x151 = x10*x91;
  double x152 = x0*x10*x131;
  double x153 = x10*x133;
  *val = dq[0]*(x55*x57 + x55*x59 + x57*x60 + x59*x60 - x62*x65 - x62*x68 + x65*x69 + x68*x69 - x71*x73 - x71*x75 + x73*x76 + x75*x76) + dq[1]*(x20*x22 + x20*x24 - x21*x26*x39 + x21*x41*x50 - x23*x39*x40 + x23*x50*x51) + base_dori[0]*(-x108*x65 - x108*x68 + x109*x73 + x109*x75 - x110*x65 - x110*x68 + x56*(x0*x124*x21*x4*x90 - x115*x123) + x58*(x0*x124*x23*x4*x90 - x115*x125) + x64*(x128*x33 - x136*x140 + x136*x141) + x67*(x138*x33 - x140*x143 + x141*x143) + x72*(x128*x28 + x132*x93 - x134*x137) - x73*x95 + x74*(x132*x99 - x134*x139 + x138*x28) - x75*x95) + base_dori[1]*(x126*x21*x63 + x126*x23*x66 + x144*x57 + x144*x59 - x146*x65 - x146*x68 + x147*x73 + x147*x75 + x148*x57 + x148*x59 - x149*x57 - x149*x59 + x56*(x123*x150 + x135*x151) + x58*(x125*x150 + x142*x151) + x64*(x103*x152 - x105*x136*x153 + x128*x29) + x67*(x106*x152 - x107*x131*x153 + x138*x29) + x72*(x128*x32 + x137*x153 - x152*x93) + x74*(x138*x32 + x139*x153 - x152*x99)) + base_dori[2]*((1.0/2.0)*x3*(x22*x91 + x24*x91 + x26*(x103 + x105*x98) + x40*(x106 + x107*x97) - x41*(x93 + x96*x98) - x51*(x100*x97 + x99))/(x85*x86 + x85*x87 + x89) + x57*x77 + x59*x77 - x65*x84 - x68*x84 + x73*x81 + x75*x81);
}
