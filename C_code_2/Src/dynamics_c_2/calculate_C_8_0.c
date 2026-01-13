

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_8_0(const double dq[3], const double base_dori[3], const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1];
  double x1 = cq[0];
  double x2 = x0*x1;
  double x3 = cbo[2];
  double x4 = sq[0];
  double x5 = cbo[1];
  double x6 = x4*x5;
  double x7 = x2 + x3*x6;
  double x8 = sbo[0];
  double x9 = sbo[2];
  double x10 = cbo[0];
  double x11 = x10*x9;
  double x12 = x3*x8;
  double x13 = x0*x12 + x11;
  double x14 = -x1*x5*x8 + x13*x4;
  double x15 = -x14;
  double x16 = 0.0065709312000000004*x5;
  double x17 = x1*x5;
  double x18 = x10*x17;
  double x19 = x8*x9;
  double x20 = x10*x3;
  double x21 = -x0*x20 + x19;
  double x22 = x18 + x21*x4;
  double x23 = -x22;
  double x24 = M_SQRT2;
  double x25 = sqrt(6);
  double x26 = 0.016767499999999998*x24 + 0.016512499999999999*x25;
  double x27 = x24 + x25;
  double x28 = x27*x7;
  double x29 = 0.016512499999999999*x24 - 0.016767499999999998*x25;
  double x30 = x0*x4;
  double x31 = -x1*x3*x5 + x30;
  double x32 = -x31;
  double x33 = sq[1];
  double x34 = 4*x33;
  double x35 = cq[1];
  double x36 = x24 - x25;
  double x37 = -x32*x34 + x35*x36*x7;
  double x38 = 0.060165000000000003*x0;
  double x39 = 0.013937500000000002*x24 + 0.032607499999999998*x25;
  double x40 = 0.032607499999999998*x24 - 0.013937500000000002*x25;
  double x41 = 0.01821*x0;
  double x42 = x15*x27;
  double x43 = x6*x8;
  double x44 = x1*x13;
  double x45 = x43 + x44;
  double x46 = x35*x36;
  double x47 = x15*x46 + x34*x45;
  double x48 = x23*x27;
  double x49 = x10*x6;
  double x50 = x1*x21;
  double x51 = -x49 + x50;
  double x52 = x23*x46 + x34*x51;
  double x53 = 0.01821*x10;
  double x54 = 0.060165000000000003*x10;
  double x55 = 4*x35;
  double x56 = x55*x7;
  double x57 = x33*x36;
  double x58 = x32*x57 - x56;
  double x59 = 0.030082500000000002*x0;
  double x60 = x29*x59;
  double x61 = 0.0091050000000000002*x0;
  double x62 = x40*x61;
  double x63 = -x31*x57 - x56;
  double x64 = x45*x57;
  double x65 = x15*x55 + x64;
  double x66 = 0.030082500000000002*x5;
  double x67 = x66*x8;
  double x68 = x29*x67;
  double x69 = 0.0091050000000000002*x5;
  double x70 = x69*x8;
  double x71 = x40*x70;
  double x72 = x14*x55 - x64;
  double x73 = x51*x57;
  double x74 = x22*x55 - x73;
  double x75 = x10*x66;
  double x76 = x29*x75;
  double x77 = x10*x69;
  double x78 = x40*x77;
  double x79 = x23*x55 + x73;
  double x80 = 0.0032854656000000002*x5;
  double x81 = x2*x9;
  double x82 = x0*x11 + x12;
  double x83 = x0*x19 - x20;
  double x84 = -x83;
  double x85 = x26*x27;
  double x86 = x17*x9;
  double x87 = x34*x6*x9 + x46*x86;
  double x88 = x27*x39;
  double x89 = x1*x82;
  double x90 = x34*x4;
  double x91 = x46*x89 + x82*x90;
  double x92 = x40*x91 + x88*x89;
  double x93 = x29*x91 + x85*x89;
  double x94 = x1*x84;
  double x95 = x46*x94 + x84*x90;
  double x96 = pow(x0, 2);
  double x97 = pow(x10, 2);
  double x98 = pow(x8, 2);
  double x99 = pow(x5, 2);
  double x100 = x97*x99 + x98*x99;
  double x101 = 0.02554*x1;
  double x102 = 0.02554*x43 + 0.02554*x44;
  double x103 = x0*(x97 + x98 - 1);
  double x104 = -0.02554*x49 + 0.02554*x50;
  double x105 = x1*x9;
  double x106 = x105*x85;
  double x107 = x105*x46 + x9*x90;
  double x108 = -x106 - x107*x29;
  double x109 = x105*x88;
  double x110 = -x107*x40 - x109;
  double x111 = x45*x85;
  double x112 = -x15*x34 + x35*x36*x45;
  double x113 = x111 + x112*x29;
  double x114 = x45*x88;
  double x115 = x112*x40 + x114;
  double x116 = x51*x85;
  double x117 = -x116;
  double x118 = x46*x51;
  double x119 = -x118 + x23*x34;
  double x120 = x117 + x119*x29;
  double x121 = x1*x83;
  double x122 = -x121*x46 - x83*x90;
  double x123 = -x121*x85 + x122*x29;
  double x124 = x51*x88;
  double x125 = -x124;
  double x126 = x119*x40 + x125;
  double x127 = -x121*x88 + x122*x40;
  double x128 = -x21;
  double x129 = x1*x128 + x49;
  double x130 = x8*x80;
  double x131 = x129*x46 + x34*(x128*x4 - x18);
  double x132 = x118 + x22*x34;
  double x133 = x116 + x132*x29;
  double x134 = x124 + x132*x40;
  double x135 = x2*x3;
  double x136 = 0.02554*x135;
  double x137 = -x136 - 0.02554*x6;
  double x138 = pow(x9, 2);
  double x139 = x138*x98;
  double x140 = pow(x3, 2);
  double x141 = x140*x98;
  double x142 = x138*x97;
  double x143 = x140*x97;
  double x144 = 1.0/(x139 + x141 + x142 + x143);
  double x145 = x144*x9;
  double x146 = 1.0/(x139*x96 + x139*x99 + x141*x96 + x141*x99 + x142*x96 + x142*x99 + x143*x96 + x143*x99);
  double x147 = 0.12864*x0;
  double x148 = x135 + x6;
  double x149 = -x148*x46 + x34*(x1*x5 - x3*x30);
  double x150 = -x107;
  double x151 = x0*x146;
  double x152 = x151*x3;
  double x153 = x144*(0.02554*x1*x3*x5 - 0.02554*x30);
  double x154 = 1.0/x5;
  double x155 = x146*x154;
  double x156 = x136*x155;
  double x157 = x155*(x100 + x96);
  double x158 = x157*x3;
  double x159 = 0.12864*x5;
  double x160 = x10*x159;
  double x161 = x159*x8;
  double x162 = x34*x7;
  double x163 = x162 + x32*x46;
  double x164 = x163*x29 + x32*x85;
  double x165 = -x93;
  double x166 = x152*x154;
  double x167 = x163*x40 + x32*x88;
  double x168 = -x92;
  double x169 = x144*x164;
  double x170 = -x132;
  double x171 = x144*x167;
  double x172 = 0.0032854656000000002*x0;
  double x173 = x1*x3*x5*x8 - x30*x8;
  double x174 = x10*x30 - x17*x20;
  double x175 = x148*x27;
  double x176 = -x149;
  double x177 = x175*x26 + x176*x29;
  double x178 = x175*x39 + x176*x40;
  double x179 = -x162 + x31*x46;
  double x180 = x173*x46 + x34*(x12*x6 + x2*x8);
  double x181 = x174*x46 + x34*(-x10*x2 - x20*x6);
  double x182 = x14*x34 + x45*x46;
  double x183 = x144*x3;
  double x184 = x151*x9;
  double x185 = 0.02554*x155*x81;
  double x186 = x157*x9;
  double x187 = x154*x184;
  *val = dq[0]*(-0.0065709312000000004*x0*x7 + x10*x16*x23 - x15*x16*x8 + x38*(x26*x28 + x29*x37) + x41*(x28*x39 + x37*x40) - x5*x53*(x39*x48 + x40*x52) - x5*x54*(x26*x48 + x29*x52) + 0.060165000000000003*x5*x8*(x26*x42 + x29*x47) + 0.01821*x5*x8*(x39*x42 + x40*x47)) + dq[1]*(x58*x60 + x58*x62 + x60*x63 + x62*x63 - x65*x68 - x65*x71 + x68*x72 + x71*x72 - x74*x76 - x74*x78 + x76*x79 + x78*x79) + base_dori[0]*(-x129*x130 - x130*x51 + x133*x67 + x134*x70 + x147*(x136*x146*x9 + x137*x145) - x160*(-x102*x158 + x11*x153 + x156*x82) - x161*(-x104*x158 + x153*x19 + x156*x83) + x59*(x145*(x148*x26*x27 - x149*x29) + x152*(-x106 + x150*x29)) + x61*(x145*(x148*x27*x39 - x149*x40) + x152*(-x109 + x150*x40)) + x67*(x129*x85 + x131*x29) + x67*(-x123*x166 + x158*(x117 + x170*x29) + x169*x19) + x70*(x129*x88 + x131*x40) + x70*(-x127*x166 + x158*(x125 + x170*x40) + x171*x19) + x75*(x10*x144*x164*x9 - x113*x158 - x165*x166) + x77*(x10*x144*x167*x9 - x115*x158 - x166*x168)) + base_dori[1]*(x10*x133*x59 + x10*x134*x61 - x10*x172*x51 + x10*x174*x80 - x130*x173 - x147*(0.02554*x0*x1*x138*x146 - x137*x183) - x148*x172 - x160*(x102*x186 + x153*x20 - x185*x82) - x161*(x104*x186 + x12*x153 - x185*x83) + x172*x45*x8 + x177*x59 + x178*x61 - x31*x80 - x59*x8*(x111 + x182*x29) + x59*(-x108*x184 + x177*x183) - x61*x8*(x114 + x182*x40) + x61*(-x110*x184 + x178*x183) + x66*(x179*x29 + x31*x85) + x67*(x173*x85 + x180*x29) + x67*(x12*x169 - x120*x186 + x123*x187) + x69*(x179*x40 + x31*x88) + x70*(x173*x88 + x180*x40) + x70*(x12*x171 - x126*x186 + x127*x187) - x75*(x174*x85 + x181*x29) + x75*(x113*x186 + x165*x187 + x169*x20) - x77*(x174*x88 + x181*x40) + x77*(x115*x186 + x168*x187 + x171*x20)) + base_dori[2]*(-0.0032854656000000002*x17*x8*x84 + 0.0032854656000000002*x18*x82 + (1.0/2.0)*x5*(0.25728000000000001*x10*(x101*x82 + x102*x103) - x108*x38 - x110*x41 - x53*(x103*x115 + x92) - x54*(x103*x113 + x93) + 0.25728000000000001*x8*(x101*x83 + x103*x104) + 0.060165000000000003*x8*(x103*x120 + x123) + 0.01821*x8*(x103*x126 + x127) - 0.0065709312000000004*x81)/(x100 + x96*x97 + x96*x98) + x59*(x29*x87 + x85*x86) + x61*(x40*x87 + x86*x88) + x67*(x29*x95 + x85*x94) + x70*(x40*x95 + x88*x94) - x75*x93 - x77*x92 - x80*x81);
}
