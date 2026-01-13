

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_7_1(const double dq[3], const double base_dori[3], const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
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
  double x20 = x10*x3;
  double x21 = x20*(x19*x9 + x6*x8);
  double x22 = 0.016512499999999999*x11 - 0.016767499999999998*x12;
  double x23 = 0.060165000000000003*x22;
  double x24 = 0.032607499999999998*x11 - 0.013937500000000002*x12;
  double x25 = 0.01821*x24;
  double x26 = sbo[0];
  double x27 = cbo[0];
  double x28 = x10*x27;
  double x29 = x26*x4;
  double x30 = x0*x29 + x28;
  double x31 = x17*x26 + x30*x5;
  double x32 = x27*x4;
  double x33 = x10*x26;
  double x34 = x0*x33 - x32;
  double x35 = x3*x5;
  double x36 = x1*x30 - x26*x35;
  double x37 = x15*x36;
  double x38 = x13*x34 + x37;
  double x39 = -x31*x8 + x38*x9;
  double x40 = 0.060165000000000003*x34;
  double x41 = 0.01821*x34;
  double x42 = x0*x28 + x29;
  double x43 = x17*x27;
  double x44 = -x0*x32 + x33;
  double x45 = -x43 + x44*x5;
  double x46 = x13*x42;
  double x47 = x27*x35;
  double x48 = x1*x44 + x47;
  double x49 = x15*x48 - x46;
  double x50 = -x45*x8 + x49*x9;
  double x51 = 4*x9;
  double x52 = x18*x51;
  double x53 = x15*x7;
  double x54 = -x52 - x53*x6;
  double x55 = 0.030082500000000002*x22;
  double x56 = x20*x55;
  double x57 = 0.0091050000000000002*x24;
  double x58 = x20*x57;
  double x59 = -x52 - x53*x6;
  double x60 = x31*x53;
  double x61 = -x36*x51 + x60;
  double x62 = 0.030082500000000002*x34;
  double x63 = x22*x62;
  double x64 = 0.0091050000000000002*x34;
  double x65 = x24*x64;
  double x66 = x36*x51 - x60;
  double x67 = x45*x53;
  double x68 = x48*x51 - x67;
  double x69 = 0.030082500000000002*x42;
  double x70 = x22*x69;
  double x71 = 0.0091050000000000002*x42;
  double x72 = x24*x71;
  double x73 = -x48*x51 + x67;
  double x74 = -x10*x35*x51 + x7*(-x10*x15*x17 + x13*x3*x4);
  double x75 = x19*x7 - 4*x6*x9;
  double x76 = x55*x75;
  double x77 = x3*x4;
  double x78 = x57*x75;
  double x79 = x5*x51;
  double x80 = x42*x79;
  double x81 = -x44;
  double x82 = x7*(x1*x15*x42 - x13*x81) + x80;
  double x83 = -x34;
  double x84 = x13*x30;
  double x85 = x1*x15;
  double x86 = x7*(x83*x85 + x84) + x79*x83;
  double x87 = x31*x51;
  double x88 = x38*x7 + x87;
  double x89 = x30*x88;
  double x90 = x45*x51 + x49*x7;
  double x91 = pow(x0, 2);
  double x92 = pow(x27, 2);
  double x93 = pow(x26, 2);
  double x94 = pow(x3, 2);
  double x95 = x92*x94 + x93*x94;
  double x96 = x10*x79 + x7*(x10*x85 - x13*x4);
  double x97 = -x10*x96;
  double x98 = x94*x97;
  double x99 = -x7*(x13*x44 + x42*x85) - x80;
  double x100 = x22*x99;
  double x101 = -x88;
  double x102 = x0*(x92 + x93 - 1);
  double x103 = x101*x102;
  double x104 = x24*x99;
  double x105 = x34*x85 - x84;
  double x106 = x105*x7 + 4*x34*x5*x9;
  double x107 = x106*x22;
  double x108 = -x49*x7;
  double x109 = -x108 + x45*x51;
  double x110 = x109*x22;
  double x111 = x106*x24;
  double x112 = x109*x24;
  double x113 = x7*(-x13*x83 + x37) + x87;
  double x114 = x51*(x43 + x5*x81) + x7*(x15*(x1*x81 - x47) + x46);
  double x115 = x51*(x16*x4 + x17);
  double x116 = x0*x14;
  double x117 = x2*x4 - x35;
  double x118 = x115 + x7*(x116 + x117*x15);
  double x119 = x10*x118;
  double x120 = pow(x10, 2);
  double x121 = x120*x93;
  double x122 = pow(x4, 2);
  double x123 = x122*x93;
  double x124 = x120*x92;
  double x125 = x122*x92;
  double x126 = 1.0/(x121 + x123 + x124 + x125);
  double x127 = x126*x22;
  double x128 = 1.0/(x121*x91 + x121*x94 + x123*x91 + x123*x94 + x124*x91 + x124*x94 + x125*x91 + x125*x94);
  double x129 = 0.030082500000000002*x20;
  double x130 = x126*x24;
  double x131 = 0.0091050000000000002*x20;
  double x132 = -x75;
  double x133 = x132*x28;
  double x134 = x0*x128;
  double x135 = 1.0/x3;
  double x136 = x135*x4;
  double x137 = x134*x136;
  double x138 = x91 + x95;
  double x139 = x132*x33;
  double x140 = x134*x22;
  double x141 = x136*(x105*x7 + x34*x79);
  double x142 = x128*x138;
  double x143 = x136*x142*(-x108 + 4*x45*x9);
  double x144 = x134*x24;
  double x145 = x0*x10;
  double x146 = -x115 + x7*(-x116 - x117*x15);
  double x147 = x13*x3;
  double x148 = x51*(-x2*x26 + x26*x3*x4*x5) + x7*(x147*x33 + x15*(x16*x26 + x17*x29));
  double x149 = x51*(x2*x27 - x32*x35) + x7*(-x147*x28 + x15*(-x16*x27 - x17*x32));
  double x150 = x3*x55;
  double x151 = x33*x88;
  double x152 = x3*x57;
  double x153 = x28*x90;
  double x154 = -x118*x4;
  double x155 = x127*x132;
  double x156 = x10*x135;
  double x157 = x134*x156;
  double x158 = x142*x156;
  double x159 = x101*x158;
  double x160 = x130*x132;
  *val = dq[0]*(0.030082500000000002*x22*x34*x66 + 0.030082500000000002*x22*x42*x73 + 0.0091050000000000002*x24*x34*x66 + 0.0091050000000000002*x24*x42*x73 - x54*x56 - x54*x58 - x56*x59 - x58*x59 - x61*x63 - x61*x65 - x68*x70 - x68*x72) + dq[1]*(-x21*x23 - x21*x25 - x22*x39*x40 + 0.060165000000000003*x22*x42*x50 - x24*x39*x41 + 0.01821*x24*x42*x50) + base_dori[0]*(0.030082500000000002*x113*x22*x42 + 0.0091050000000000002*x113*x24*x42 - x114*x63 - x114*x65 - x129*(x0*x128*x22*x4*x96 - x119*x127) - x131*(x0*x128*x24*x4*x96 - x119*x130) + 0.030082500000000002*x22*x83*x90 + 0.0091050000000000002*x24*x83*x90 + 0.030082500000000002*x34*(x127*x139 - x140*x141 + x143*x22) + 0.0091050000000000002*x34*(x130*x139 - x141*x144 + x143*x24) - x69*(-x100*x137 + x101*x128*x135*x138*x22*x4 - x127*x133) - x70*x88 - x71*(x101*x128*x135*x138*x24*x4 - x104*x137 - x130*x133) - x72*x88) + base_dori[1]*(-x129*(x127*x154 + x140*x97) - x131*(x130*x154 + x144*x97) + x145*x76 + x145*x78 - x146*x56 - x146*x58 - x148*x63 - x148*x65 + x149*x70 + x149*x72 - x150*x151 + x150*x153 - x151*x152 + x152*x153 + x62*(x107*x157 - x110*x158 + x155*x29) + x64*(x111*x157 - x112*x158 + x160*x29) + x69*(-x100*x157 + x155*x32 + x159*x22) + x71*(-x104*x157 + x159*x24 + x160*x32)) + base_dori[2]*(0.030082500000000002*x22*x42*x82 + 0.030082500000000002*x22*x81*x90 + 0.0091050000000000002*x24*x42*x82 + 0.0091050000000000002*x24*x81*x90 - x55*x89 - x56*x74 - x57*x89 - x58*x74 - x63*x86 - x65*x86 - x76*x77 - x77*x78 + (1.0/2.0)*(-x23*x98 - x25*x98 + x40*(x102*x110 + x107) + x41*(x102*x112 + x111) + 0.060165000000000003*x42*(-x100 - x103*x22) + 0.01821*x42*(-x103*x24 - x104))/(x91*x92 + x91*x93 + x95));
}
