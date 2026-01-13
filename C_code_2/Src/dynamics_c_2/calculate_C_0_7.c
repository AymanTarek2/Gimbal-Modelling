

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_0_7(const double dq[3], const double base_dori[3], const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1];
  double x1 = cq[0];
  double x2 = x0*x1;
  double x3 = cbo[2];
  double x4 = sq[0];
  double x5 = cbo[1];
  double x6 = x4*x5;
  double x7 = x2 + x3*x6;
  double x8 = cq[1];
  double x9 = 4*x8;
  double x10 = x7*x9;
  double x11 = x0*x4;
  double x12 = -x1*x3*x5 + x11;
  double x13 = -x12;
  double x14 = M_SQRT2;
  double x15 = sqrt(6);
  double x16 = x14 - x15;
  double x17 = sq[1];
  double x18 = x16*x17;
  double x19 = -x10 + x13*x18;
  double x20 = 0.016512499999999999*x14 - 0.016767499999999998*x15;
  double x21 = sbo[2];
  double x22 = x21*x5;
  double x23 = 0.030082500000000002*x22;
  double x24 = x20*x23;
  double x25 = 0.032607499999999998*x14 - 0.013937500000000002*x15;
  double x26 = 0.0091050000000000002*x22;
  double x27 = x25*x26;
  double x28 = -x10 - x12*x18;
  double x29 = sbo[0];
  double x30 = x1*x5;
  double x31 = cbo[0];
  double x32 = x21*x31;
  double x33 = x29*x3;
  double x34 = x0*x33 + x32;
  double x35 = -x29*x30 + x34*x4;
  double x36 = -x35;
  double x37 = x29*x6;
  double x38 = x1*x34;
  double x39 = x37 + x38;
  double x40 = x18*x39;
  double x41 = x36*x9 + x40;
  double x42 = x3*x31;
  double x43 = x21*x29;
  double x44 = x0*x43 - x42;
  double x45 = 0.030082500000000002*x44;
  double x46 = x20*x45;
  double x47 = 0.0091050000000000002*x44;
  double x48 = x25*x47;
  double x49 = x35*x9 - x40;
  double x50 = x30*x31;
  double x51 = -x0*x42 + x43;
  double x52 = x4*x51 + x50;
  double x53 = x31*x6;
  double x54 = x1*x51;
  double x55 = -x53 + x54;
  double x56 = x18*x55;
  double x57 = x52*x9 - x56;
  double x58 = x0*x32 + x33;
  double x59 = 0.030082500000000002*x58;
  double x60 = x20*x59;
  double x61 = 0.0091050000000000002*x58;
  double x62 = x25*x61;
  double x63 = -x52;
  double x64 = x56 + x63*x9;
  double x65 = pow(x21, 2);
  double x66 = pow(x5, 2);
  double x67 = 0.0032854656000000002*x44;
  double x68 = -x44;
  double x69 = x1*x68;
  double x70 = 0.0032854656000000002*x39;
  double x71 = -x51;
  double x72 = x14 + x15;
  double x73 = 0.016767499999999998*x14 + 0.016512499999999999*x15;
  double x74 = x72*x73;
  double x75 = x21*x30;
  double x76 = 4*x17;
  double x77 = x16*x8;
  double x78 = x21*x6*x76 + x75*x77;
  double x79 = 0.013937500000000002*x14 + 0.032607499999999998*x15;
  double x80 = x72*x79;
  double x81 = x7*x76;
  double x82 = x12*x77 - x81;
  double x83 = x12*x80 + x25*x82;
  double x84 = x3*x5;
  double x85 = x12*x74 + x20*x82;
  double x86 = x1*x58;
  double x87 = x4*x76;
  double x88 = x58*x87 + x77*x86;
  double x89 = x25*x88 + x80*x86;
  double x90 = x20*x88 + x74*x86;
  double x91 = x68*x87 + x69*x77;
  double x92 = x39*x74;
  double x93 = x35*x76 + x39*x77;
  double x94 = x20*x93 + x92;
  double x95 = x39*x80;
  double x96 = x25*x93 + x95;
  double x97 = x55*x74;
  double x98 = x55*x77;
  double x99 = x52*x76 + x98;
  double x100 = 0.030082500000000002*x20*x99 + 0.030082500000000002*x97;
  double x101 = x55*x80;
  double x102 = 0.0091050000000000002*x101 + 0.0091050000000000002*x25*x99;
  double x103 = pow(x0, 2);
  double x104 = pow(x31, 2);
  double x105 = pow(x29, 2);
  double x106 = x104*x66 + x105*x66;
  double x107 = x1*x21;
  double x108 = x107*x74;
  double x109 = x107*x77 + x21*x87;
  double x110 = -x108 - x109*x20;
  double x111 = x21*x66;
  double x112 = x107*x80;
  double x113 = -x109*x25 - x112;
  double x114 = 0.02554*x1;
  double x115 = 0.02554*x37 + 0.02554*x38;
  double x116 = x0*(x104 + x105 - 1);
  double x117 = -0.02554*x53 + 0.02554*x54;
  double x118 = x16*x39*x8 - x36*x76;
  double x119 = x118*x20 + x92;
  double x120 = x118*x25 + x95;
  double x121 = -x97;
  double x122 = -x99;
  double x123 = x121 + x122*x20;
  double x124 = x1*x44;
  double x125 = -x124*x77 - x44*x87;
  double x126 = -x124*x74 + x125*x20;
  double x127 = -x101;
  double x128 = x122*x25 + x127;
  double x129 = -x124*x80 + x125*x25;
  double x130 = x1*x71 + x53;
  double x131 = x130*x77 + x76*(x4*x71 - x50);
  double x132 = x2*x3;
  double x133 = 0.02554*x132;
  double x134 = -x133 - 0.02554*x6;
  double x135 = x105*x65;
  double x136 = pow(x3, 2);
  double x137 = x105*x136;
  double x138 = x104*x65;
  double x139 = x104*x136;
  double x140 = 1.0/(x135 + x137 + x138 + x139);
  double x141 = x140*x21;
  double x142 = 1.0/(x103*x135 + x103*x137 + x103*x138 + x103*x139 + x135*x66 + x137*x66 + x138*x66 + x139*x66);
  double x143 = 0.12864*x22;
  double x144 = x132 + x6;
  double x145 = -x144*x77 + x76*(x1*x5 - x11*x3);
  double x146 = -x109;
  double x147 = x0*x142;
  double x148 = x147*x3;
  double x149 = x140*(0.02554*x1*x3*x5 - 0.02554*x11);
  double x150 = 1.0/x5;
  double x151 = x142*x150;
  double x152 = x133*x151;
  double x153 = x151*(x103 + x106);
  double x154 = x153*x3;
  double x155 = x13*x77 + x81;
  double x156 = x13*x74 + x155*x20;
  double x157 = x140*x32;
  double x158 = -x90;
  double x159 = x148*x150;
  double x160 = x13*x80 + x155*x25;
  double x161 = -x89;
  double x162 = x140*x43;
  double x163 = x63*x76 - x98;
  double x164 = x11*x31 - x30*x42;
  double x165 = x1*x29*x3*x5 - x11*x29;
  double x166 = -x145;
  double x167 = x144*x74 + x166*x20;
  double x168 = x144*x80 + x166*x25;
  double x169 = x165*x77 + x76*(x2*x29 + x33*x6);
  double x170 = x164*x77 + x76*(-x2*x31 - x42*x6);
  double x171 = x32*x5;
  double x172 = x140*x3;
  double x173 = x147*x21;
  double x174 = 0.02554*x151*x2*x21;
  double x175 = x153*x21;
  double x176 = x140*x156;
  double x177 = x150*x173;
  double x178 = x140*x160;
  *val = dq[1]*(x19*x24 + x19*x27 - x24*x28 - x27*x28 + x41*x46 + x41*x48 + x46*x49 + x48*x49 - x57*x60 - x57*x62 - x60*x64 - x62*x64) + base_dori[0]*(-x100*x68 - x102*x68 - x130*x67 + x143*(x133*x142*x21 + x134*x141) + x23*(x141*(x144*x72*x73 - x145*x20) + x148*(-x108 + x146*x20)) + x26*(x141*(x144*x72*x79 - x145*x25) + x148*(-x112 + x146*x25)) + 0.12864*x44*(-x117*x154 + x149*x43 + x152*x44) + x45*(x130*x74 + x131*x20) - x45*(-x126*x159 + x154*(x121 + x163*x20) + x156*x162) + x47*(x130*x80 + x131*x25) - x47*(-x129*x159 + x154*(x127 + x163*x25) + x160*x162) + 0.0032854656000000002*x55*x68 + 0.12864*x58*(-x115*x154 + x149*x32 + x152*x58) + x59*(x119*x154 - x156*x157 + x158*x159) + x61*(x120*x154 - x157*x160 + x159*x161)) + base_dori[1]*(-0.0032854656000000002*x0*x12*x21 + 0.0091050000000000002*x0*x21*x83 + 0.030082500000000002*x0*x21*x85 - x100*x171 - x102*x171 - x143*(0.02554*x0*x1*x142*x65 - x134*x172) + 0.0032854656000000002*x144*x21*x5 + 0.0032854656000000002*x164*x58 - x165*x67 - x167*x23 - x168*x26 + 0.030082500000000002*x21*x29*x5*x94 + 0.0091050000000000002*x21*x29*x5*x96 + 0.0032854656000000002*x21*x31*x5*x55 + 0.030082500000000002*x21*x5*(-x110*x173 + x167*x172) + 0.0091050000000000002*x21*x5*(-x113*x173 + x168*x172) - x43*x5*x70 + 0.030082500000000002*x44*(x165*x74 + x169*x20) + 0.0091050000000000002*x44*(x165*x80 + x169*x25) + 0.12864*x44*(x117*x175 + x149*x33 - x174*x44) - x45*(-x123*x175 + x126*x177 + x176*x33) - x47*(-x128*x175 + x129*x177 + x178*x33) + 0.12864*x58*(x115*x175 + x149*x42 - x174*x58) - x59*(x164*x74 + x170*x20) - x59*(x119*x175 + x158*x177 + x176*x42) - x61*(x164*x80 + x170*x25) - x61*(x120*x175 + x161*x177 + x178*x42)) + base_dori[2]*(0.0032854656000000002*x1*pow(x58, 2) + 0.0032854656000000002*x1*x65*x66 - x100*x71 - x102*x71 + 0.0032854656000000002*x12*x3*x5 - x23*(x20*x78 + x74*x75) - x26*(x25*x78 + x75*x80) - x34*x70 + 0.030082500000000002*x34*x94 + 0.0091050000000000002*x34*x96 + 0.030082500000000002*x44*(x20*x91 + x69*x74) + 0.0091050000000000002*x44*(x25*x91 + x69*x80) + 0.0032854656000000002*x55*x71 - x59*x90 - x61*x89 - x67*x69 - 0.0091050000000000002*x83*x84 - 0.030082500000000002*x84*x85 - 1.0/2.0*(0.0065709312000000004*x1*x65*x66 + 0.060165000000000003*x110*x111 + 0.01821*x111*x113 + 0.25728000000000001*x44*(x114*x44 + x116*x117) + 0.060165000000000003*x44*(x116*x123 + x126) + 0.01821*x44*(x116*x128 + x129) + 0.25728000000000001*x58*(x114*x58 + x115*x116) + 0.060165000000000003*x58*(-x116*x119 - x90) + 0.01821*x58*(-x116*x120 - x89))/(x103*x104 + x103*x105 + x106));
}
