

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_6_1(const double dq[3], const double base_dori[3], const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
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
  double x20 = x3*x4;
  double x21 = x20*(x19*x9 + x6*x8);
  double x22 = 0.016512499999999999*x11 - 0.016767499999999998*x12;
  double x23 = 0.032607499999999998*x11 - 0.013937500000000002*x12;
  double x24 = sbo[0];
  double x25 = cbo[0];
  double x26 = x10*x25;
  double x27 = x24*x4;
  double x28 = x0*x27 + x26;
  double x29 = x17*x24 + x28*x5;
  double x30 = x25*x4;
  double x31 = x10*x24;
  double x32 = x0*x31 - x30;
  double x33 = x1*x28 - x24*x3*x5;
  double x34 = x15*x33;
  double x35 = x13*x32 + x34;
  double x36 = -x29*x8 + x35*x9;
  double x37 = 0.060165000000000003*x28;
  double x38 = 0.01821*x28;
  double x39 = x17*x25;
  double x40 = -x0*x30 + x31;
  double x41 = -x39 + x40*x5;
  double x42 = x0*x26 + x27;
  double x43 = x13*x42;
  double x44 = x3*x5;
  double x45 = x25*x44;
  double x46 = x1*x40 + x45;
  double x47 = x15*x46 - x43;
  double x48 = -x41*x8 + x47*x9;
  double x49 = 0.060165000000000003*x40;
  double x50 = 0.01821*x40;
  double x51 = 4*x9;
  double x52 = x18*x51;
  double x53 = x15*x7;
  double x54 = -x52 - x53*x6;
  double x55 = 0.030082500000000002*x22;
  double x56 = x20*x55;
  double x57 = 0.0091050000000000002*x23;
  double x58 = x20*x57;
  double x59 = -x52 - x53*x6;
  double x60 = x29*x53;
  double x61 = -x33*x51 + x60;
  double x62 = 0.030082500000000002*x28;
  double x63 = x22*x62;
  double x64 = 0.0091050000000000002*x28;
  double x65 = x23*x64;
  double x66 = x33*x51 - x60;
  double x67 = x41*x53;
  double x68 = x46*x51 - x67;
  double x69 = 0.030082500000000002*x40;
  double x70 = x22*x69;
  double x71 = 0.0091050000000000002*x40;
  double x72 = x23*x71;
  double x73 = -x46*x51 + x67;
  double x74 = -x10*x44*x51 + x7*(-x10*x15*x17 + x13*x3*x4);
  double x75 = x19*x7 - 4*x6*x9;
  double x76 = x55*x75;
  double x77 = x10*x3;
  double x78 = x57*x75;
  double x79 = -x32;
  double x80 = x5*x51;
  double x81 = x13*x28;
  double x82 = x1*x15;
  double x83 = x7*(x79*x82 + x81) + x79*x80;
  double x84 = x42*x80;
  double x85 = -x40;
  double x86 = x7*(x1*x15*x42 - x13*x85) + x84;
  double x87 = x29*x51;
  double x88 = x35*x7 + x87;
  double x89 = x79*x88;
  double x90 = x41*x51 + x47*x7;
  double x91 = x42*x90;
  double x92 = pow(x0, 2);
  double x93 = pow(x25, 2);
  double x94 = pow(x24, 2);
  double x95 = pow(x3, 2);
  double x96 = x93*x95 + x94*x95;
  double x97 = x10*x80 + x7*(x10*x82 - x13*x4);
  double x98 = -x97;
  double x99 = -x7*(x13*x40 + x42*x82) - x84;
  double x100 = x22*x99;
  double x101 = -x88;
  double x102 = x0*(x93 + x94 - 1);
  double x103 = x101*x102;
  double x104 = x23*x99;
  double x105 = x32*x80 + x7*(x32*x82 - x81);
  double x106 = x105*x22;
  double x107 = 4*x41*x9 + x47*x7;
  double x108 = x107*x22;
  double x109 = x105*x23;
  double x110 = x107*x23;
  double x111 = x51*(x39 + x5*x85) + x7*(x15*(x1*x85 - x45) + x43);
  double x112 = x85*x88;
  double x113 = x7*(-x13*x79 + x34) + x87;
  double x114 = x51*(x16*x4 + x17);
  double x115 = x0*x14;
  double x116 = x2*x4 - x44;
  double x117 = x114 + x7*(x115 + x116*x15);
  double x118 = x10*x117;
  double x119 = pow(x10, 2);
  double x120 = x119*x94;
  double x121 = pow(x4, 2);
  double x122 = x121*x94;
  double x123 = x119*x93;
  double x124 = x121*x93;
  double x125 = 1.0/(x120 + x122 + x123 + x124);
  double x126 = x125*x22;
  double x127 = 1.0/(x120*x92 + x120*x95 + x122*x92 + x122*x95 + x123*x92 + x123*x95 + x124*x92 + x124*x95);
  double x128 = 0.030082500000000002*x20;
  double x129 = x125*x23;
  double x130 = 0.0091050000000000002*x20;
  double x131 = -x75;
  double x132 = x126*x131;
  double x133 = x0*x127;
  double x134 = 1.0/x3;
  double x135 = x134*x4;
  double x136 = x133*x135;
  double x137 = x92 + x96;
  double x138 = x129*x131;
  double x139 = x127*x137;
  double x140 = x135*x139;
  double x141 = x0*x4;
  double x142 = -x114 + x7*(-x115 - x116*x15);
  double x143 = x13*x3;
  double x144 = x51*(-x2*x24 + x24*x3*x4*x5) + x7*(x143*x31 + x15*(x16*x24 + x17*x27));
  double x145 = x51*(x2*x25 - x30*x44) + x7*(-x143*x26 + x15*(-x16*x25 - x17*x30));
  double x146 = x27*x88;
  double x147 = x3*x55;
  double x148 = x3*x57;
  double x149 = x30*x90;
  double x150 = -x117*x4;
  double x151 = x10*x98;
  double x152 = x10*x134;
  double x153 = x133*x152;
  double x154 = x139*x152;
  double x155 = x101*x154;
  *val = dq[0]*(x54*x56 + x54*x58 + x56*x59 + x58*x59 + x61*x63 + x61*x65 - x63*x66 - x65*x66 - x68*x70 - x68*x72 + x70*x73 + x72*x73) + dq[1]*(0.060165000000000003*x21*x22 + 0.01821*x21*x23 + x22*x36*x37 + x22*x48*x49 + x23*x36*x38 + x23*x48*x50) + base_dori[0]*(x111*x63 + x111*x65 + x112*x55 + x112*x57 + x113*x70 + x113*x72 + x128*(x0*x127*x22*x4*x97 - x118*x126) + x130*(x0*x127*x23*x4*x97 - x118*x129) - x62*(-x106*x136 + x108*x140 + x132*x31) + x63*x90 - x64*(-x109*x136 + x110*x140 + x138*x31) + x65*x90 - x69*(-x100*x136 + x101*x127*x134*x137*x22*x4 - x132*x26) - x71*(x101*x127*x134*x137*x23*x4 - x104*x136 - x138*x26)) + base_dori[1]*(x128*(x126*x150 + x133*x151*x22) + x130*(x129*x150 + x133*x151*x23) - x141*x76 - x141*x78 + x142*x56 + x142*x58 + x144*x63 + x144*x65 + x145*x70 + x145*x72 + x146*x147 + x146*x148 - x147*x149 - x148*x149 - x62*(x106*x153 - x108*x154 + x132*x27) - x64*(x109*x153 - x110*x154 + x138*x27) + x69*(-x100*x153 + x132*x30 + x155*x22) + x71*(-x104*x153 + x138*x30 + x155*x23)) + base_dori[2]*(x55*x89 + x55*x91 + x56*x74 + x57*x89 + x57*x91 + x58*x74 + x63*x83 + x65*x83 + x70*x86 + x72*x86 - x76*x77 - x77*x78 + (1.0/2.0)*(0.060165000000000003*x22*x4*x95*x98 + 0.01821*x23*x4*x95*x98 - x37*(x102*x108 + x106) - x38*(x102*x110 + x109) - x49*(x100 + x103*x22) - x50*(x103*x23 + x104))/(x92*x93 + x92*x94 + x96));
}
