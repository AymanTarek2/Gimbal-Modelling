

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_2_2(const double dq[3], const double base_dori[3], const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = M_SQRT2;
  double x1 = sqrt(6);
  double x2 = x0 - x1;
  double x3 = sbo[2];
  double x4 = cbo[1];
  double x5 = x3*x4;
  double x6 = x0 + x1;
  double x7 = sbo[1];
  double x8 = cq[0];
  double x9 = x7*x8;
  double x10 = cbo[2];
  double x11 = sq[0];
  double x12 = x11*x4;
  double x13 = x10*x12 + x9;
  double x14 = x13*x6 - x2*x5;
  double x15 = -x14;
  double x16 = cq[2];
  double x17 = x16*x6;
  double x18 = x11*x7;
  double x19 = x4*x8;
  double x20 = -x10*x19 + x18;
  double x21 = cq[1];
  double x22 = 4*x21;
  double x23 = sq[1];
  double x24 = x13*x2 + x5*x6;
  double x25 = -x20*x22 + x23*x24;
  double x26 = sq[2];
  double x27 = 4*x26;
  double x28 = 4*x23;
  double x29 = x20*x28 + x21*x24;
  double x30 = x16*x2;
  double x31 = x25*x27 + x29*x30;
  double x32 = x29*x6;
  double x33 = x15*x2 + x32;
  double x34 = 2*x33;
  double x35 = cbo[0];
  double x36 = x10*x35;
  double x37 = sbo[0];
  double x38 = x3*x37;
  double x39 = -x36 + x38*x7;
  double x40 = x3*x35;
  double x41 = x10*x37;
  double x42 = x40 + x41*x7;
  double x43 = x11*x42 - x19*x37;
  double x44 = x43*x6;
  double x45 = -x2*x39 + x44;
  double x46 = -x45;
  double x47 = x12*x37 + x42*x8;
  double x48 = x22*x47;
  double x49 = x2*x43;
  double x50 = x39*x6 + x49;
  double x51 = x23*x50 + x48;
  double x52 = -x28*x47;
  double x53 = x21*x50 + x52;
  double x54 = x27*x51 + x30*x53;
  double x55 = x53*x6;
  double x56 = x2*x46 + x55;
  double x57 = 2*x56;
  double x58 = x40*x7 + x41;
  double x59 = x2*x58;
  double x60 = x19*x35;
  double x61 = -x36*x7 + x38;
  double x62 = x11*x61 + x60;
  double x63 = x59 + x6*x62;
  double x64 = x12*x35;
  double x65 = x61*x8 - x64;
  double x66 = x58*x6;
  double x67 = x2*x62 - x66;
  double x68 = x21*x67 - x28*x65;
  double x69 = x2*x63 - x6*x68;
  double x70 = -x69;
  double x71 = x22*x65 + x23*x67;
  double x72 = x17*x63 + x27*x71 + x30*x68;
  double x73 = x70*x72;
  double x74 = x26*x6;
  double x75 = 4*x16;
  double x76 = x25*x75;
  double x77 = x2*x26;
  double x78 = x29*x77;
  double x79 = -x15*x74 - x76 + x78;
  double x80 = x51*x75;
  double x81 = x53*x77;
  double x82 = -x46*x74 - x80 + x81;
  double x83 = x63*x74 + x68*x77 - x71*x75;
  double x84 = 2.2050437927246095e-10*x33*x79 + 2.2050437927246095e-10*x56*x82 + 2.2050437927246095e-10*x70*x83;
  double x85 = x14*x2 - x32;
  double x86 = -x85;
  double x87 = 2*x86;
  double x88 = x2*x45 - x55;
  double x89 = -x88;
  double x90 = 2*x89;
  double x91 = 2*x70;
  double x92 = x14*x17 + x31;
  double x93 = x17*x45 + x54;
  double x94 = 2.2050437927246095e-10*x73 + 2.2050437927246095e-10*x86*x92 + 2.2050437927246095e-10*x89*x93;
  double x95 = -x39;
  double x96 = x2*x95;
  double x97 = x44 + x96;
  double x98 = x2*x97;
  double x99 = x6*x95;
  double x100 = x49 - x99;
  double x101 = x100*x21 + x52;
  double x102 = 2*x69;
  double x103 = -x61;
  double x104 = x103*x11 - x60;
  double x105 = x104*x6 - x59;
  double x106 = x105*x2;
  double x107 = x103*x8 + x64;
  double x108 = x104*x2 + x66;
  double x109 = -x107*x28 + x108*x21;
  double x110 = x109*x6;
  double x111 = 2*x88;
  double x112 = 4.0615989685058596e-10*pow(x69, 2) + 4.0615989685058596e-10*pow(x85, 2) + 4.0615989685058596e-10*pow(x88, 2);
  double x113 = -x105;
  double x114 = 2*x82;
  double x115 = x100*x23 + x48;
  double x116 = x107*x22 + x108*x23;
  double x117 = 2*x101*x6 - 2*x98;
  double x118 = 2*x93;
  double x119 = -x25;
  double x120 = 4*x6;
  double x121 = -x51;
  double x122 = -x71;
  double x123 = 2*x79;
  double x124 = x119*x6;
  double x125 = x121*x6;
  double x126 = 2*x122*x6;
  double x127 = 2*x92;
  double x128 = -x20;
  double x129 = x2*x6;
  double x130 = x128*x129;
  double x131 = x128*x2*x21 + x13*x28;
  double x132 = 2*x85;
  double x133 = -x43;
  double x134 = -x133*x28 + x2*x21*x47;
  double x135 = x134*x6;
  double x136 = -x62;
  double x137 = -x136*x28 + x2*x21*x65;
  double x138 = x137*x6;
  double x139 = pow(x6, 2);
  double x140 = x139*x26;
  double x141 = x2*x23;
  double x142 = x128*x141 - x13*x22;
  double x143 = -2*x130 + 2*x131*x6;
  double x144 = x133*x22 + x141*x47;
  double x145 = x136*x22 + x141*x65;
  double x146 = -2*x129*x47 + 2*x135;
  double x147 = -2*x129*x65 + 2*x138;
  double x148 = x139*x16;
  double x149 = x12*x3;
  double x150 = x10*x2*x4 + x149*x6;
  double x151 = -x150;
  double x152 = x19*x3;
  double x153 = x10*x4*x6 - x149*x2;
  double x154 = x152*x28 + x153*x21;
  double x155 = x154*x6;
  double x156 = x103*x2 + x11*x66;
  double x157 = x156*x2;
  double x158 = x28*x8;
  double x159 = -x103*x6 + x11*x2*x58;
  double x160 = -x158*x58 + x159*x21;
  double x161 = x11*x99 - x2*x42;
  double x162 = x11*x96 + x42*x6;
  double x163 = -x158*x95 + x162*x21;
  double x164 = x163*x6;
  double x165 = -x152*x22 + x153*x23;
  double x166 = x22*x8;
  double x167 = x159*x23 + x166*x58;
  double x168 = -x161;
  double x169 = x162*x23 + x166*x95;
  double x170 = -2*x157 + 2*x160*x6;
  double x171 = x3*x7;
  double x172 = -x10*x18 + x4*x8;
  double x173 = x171*x2 + x172*x6;
  double x174 = x173*x2;
  double x175 = x10*x9 + x12;
  double x176 = -x171*x6 + x172*x2;
  double x177 = x175*x28 + x176*x21;
  double x178 = x177*x6;
  double x179 = x38*x4;
  double x180 = x12*x41 + x37*x9;
  double x181 = -x179*x2 + x180*x6;
  double x182 = x181*x2;
  double x183 = x10*x37*x4*x8 - x18*x37;
  double x184 = x179*x6 + x180*x2;
  double x185 = -x183*x28 + x184*x21;
  double x186 = x185*x6;
  double x187 = x4*x40;
  double x188 = -x12*x36 - x35*x9;
  double x189 = x187*x2 + x188*x6;
  double x190 = x189*x2;
  double x191 = x18*x35 - x19*x36;
  double x192 = -x187*x6 + x188*x2;
  double x193 = -x191*x28 + x192*x21;
  double x194 = -x175*x22 + x176*x23;
  double x195 = x183*x22 + x184*x23;
  double x196 = x191*x22 + x192*x23;
  double x197 = -2*x190 + 2*x193*x6;
  double x198 = -x173;
  double x199 = -x181;
  *val = dq[0]*(x112*(x102*(-2*x138 + 2*x2*x6*x65) + x111*(-2*x135 + 2*x2*x47*x6) + x132*(2*x130 - 2*x131*x6)) + x84*(x143*x79 + x146*x82 + x147*x83 + x34*(x128*x140 + x131*x77 - x142*x75) + x57*(x134*x77 + x140*x47 - x144*x75) + x91*(x137*x77 + x140*x65 - x145*x75)) + x94*(x143*x92 + x146*x93 + x147*x72 + x87*(x128*x148 + x131*x30 + x142*x27) + x90*(x134*x30 + x144*x27 + x148*x47) + x91*(x137*x30 + x145*x27 + x148*x65))) + dq[1]*(x112*(-x119*x120*x85 - x120*x121*x88 - x120*x122*x69) + x84*(x114*x125 + x123*x124 + x126*x83 + x34*(x119*x77 - x29*x75) + x57*(x121*x77 - x53*x75) + x91*(x122*x77 - x68*x75)) + x94*(x118*x125 + x124*x127 + x126*x72 + x87*(x119*x30 + x27*x29) + x90*(x121*x30 + x27*x53) + x91*(x122*x30 + x27*x68))) + dq[2]*(x84*(x34*(-x15*x17 + x31) + x57*(-x17*x46 + x54) + 2*x73) + x94*(-x83*x91 + x87*(-x14*x74 + x76 - x78) + x90*(-x45*x74 + x80 - x81))) + base_dori[0]*(x112*(x102*(-2*x101*x6 + 2*x98) + x111*(2*x106 - 2*x110)) + x84*(x114*(x110 + x113*x2) + x117*x83 + x57*(x109*x2*x26 - x113*x74 - x116*x75) + x91*(x101*x77 - x115*x75 + x74*x97)) + x94*(x117*x72 + x118*(-x106 + x109*x6) + x90*(x105*x17 + x109*x30 + x116*x27) + x91*(x101*x30 + x115*x27 + x17*x97))) + base_dori[1]*(x112*(x102*(2*x190 - 2*x193*x6) + x111*(2*x182 - 2*x186) + x132*(2*x174 - 2*x178)) + x84*(x114*(x186 + x199*x2) + x123*(x178 + x198*x2) + x197*x83 + x34*(x177*x2*x26 - x194*x75 - x198*x74) + x57*(x185*x2*x26 - x195*x75 - x199*x74) + x91*(x189*x74 + x193*x77 - x196*x75)) + x94*(x118*(-x182 + x185*x6) + x127*(-x174 + x177*x6) + x197*x72 + x87*(x17*x173 + x177*x30 + x194*x27) + x90*(x17*x181 + x185*x30 + x195*x27) + x91*(x17*x189 + x193*x30 + x196*x27))) + base_dori[2]*(x112*(x102*(2*x157 - 2*x160*x6) + x111*(2*x161*x2 - 2*x164) + x132*(2*x151*x2 - 2*x155)) + x84*(x114*(x164 + x168*x2) + x123*(x150*x2 + x155) + x170*x83 + x34*(-x150*x74 + x154*x2*x26 - x165*x75) + x57*(x163*x2*x26 - x168*x74 - x169*x75) + x91*(x156*x74 + x160*x77 - x167*x75)) + x94*(x118*(-x161*x2 + x164) + x127*(-x151*x2 + x155) + x170*x72 + x87*(x151*x17 + x154*x30 + x165*x27) + x90*(x161*x17 + x163*x30 + x169*x27) + x91*(x156*x17 + x160*x30 + x167*x27)));
}
