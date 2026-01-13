

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_6_0(const double dq[3], const double base_dori[3], const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1];
  double x1 = cq[0];
  double x2 = x0*x1;
  double x3 = cbo[2];
  double x4 = sq[0];
  double x5 = cbo[1];
  double x6 = x4*x5;
  double x7 = x2 + x3*x6;
  double x8 = x3*x5;
  double x9 = sbo[2];
  double x10 = cbo[0];
  double x11 = x10*x9;
  double x12 = sbo[0];
  double x13 = x12*x3;
  double x14 = x0*x13 + x11;
  double x15 = -x1*x12*x5 + x14*x4;
  double x16 = -x15;
  double x17 = x12*x9;
  double x18 = x10*x3;
  double x19 = -x0*x18 + x17;
  double x20 = x1*x5;
  double x21 = x10*x20;
  double x22 = x19*x4 + x21;
  double x23 = -x22;
  double x24 = M_SQRT2;
  double x25 = sqrt(6);
  double x26 = x24 + x25;
  double x27 = 0.016767499999999998*x24 + 0.016512499999999999*x25;
  double x28 = x26*x27;
  double x29 = 0.016512499999999999*x24 - 0.016767499999999998*x25;
  double x30 = x0*x4;
  double x31 = -x1*x3*x5 + x30;
  double x32 = -x31;
  double x33 = sq[1];
  double x34 = 4*x33;
  double x35 = cq[1];
  double x36 = x24 - x25;
  double x37 = -x32*x34 + x35*x36*x7;
  double x38 = 0.013937500000000002*x24 + 0.032607499999999998*x25;
  double x39 = x26*x38;
  double x40 = 0.032607499999999998*x24 - 0.013937500000000002*x25;
  double x41 = x12*x6;
  double x42 = x1*x14;
  double x43 = x41 + x42;
  double x44 = x35*x36;
  double x45 = x16*x44 + x34*x43;
  double x46 = 0.01821*x14;
  double x47 = 0.060165000000000003*x14;
  double x48 = x10*x6;
  double x49 = x1*x19;
  double x50 = -x48 + x49;
  double x51 = x23*x44 + x34*x50;
  double x52 = 0.01821*x19;
  double x53 = 0.060165000000000003*x19;
  double x54 = 4*x35;
  double x55 = x54*x7;
  double x56 = x33*x36;
  double x57 = x32*x56 - x55;
  double x58 = 0.030082500000000002*x29*x8;
  double x59 = 0.0091050000000000002*x40*x8;
  double x60 = -x31*x56 - x55;
  double x61 = x43*x56;
  double x62 = x16*x54 + x61;
  double x63 = 0.030082500000000002*x14;
  double x64 = x29*x63;
  double x65 = 0.0091050000000000002*x14;
  double x66 = x40*x65;
  double x67 = x15*x54 - x61;
  double x68 = x50*x56;
  double x69 = x22*x54 - x68;
  double x70 = 0.030082500000000002*x19;
  double x71 = x29*x70;
  double x72 = 0.0091050000000000002*x19;
  double x73 = x40*x72;
  double x74 = x23*x54 + x68;
  double x75 = x1*x9;
  double x76 = pow(x5, 2);
  double x77 = x3*x76;
  double x78 = x75*x77;
  double x79 = x0*x11 + x13;
  double x80 = x0*x17 - x18;
  double x81 = -x80;
  double x82 = x20*x9;
  double x83 = x34*x6*x9 + x44*x82;
  double x84 = x34*x7;
  double x85 = x31*x44 - x84;
  double x86 = 0.0091050000000000002*x31*x39 + 0.0091050000000000002*x40*x85;
  double x87 = x5*x9;
  double x88 = 0.030082500000000002*x28*x31 + 0.030082500000000002*x29*x85;
  double x89 = x1*x79;
  double x90 = x34*x4;
  double x91 = x44*x89 + x79*x90;
  double x92 = x39*x89 + x40*x91;
  double x93 = x28*x89 + x29*x91;
  double x94 = x1*x81;
  double x95 = x44*x94 + x81*x90;
  double x96 = x28*x43;
  double x97 = x15*x34 + x43*x44;
  double x98 = 0.030082500000000002*x29*x97 + 0.030082500000000002*x96;
  double x99 = x39*x43;
  double x100 = 0.0091050000000000002*x40*x97 + 0.0091050000000000002*x99;
  double x101 = x28*x50;
  double x102 = x44*x50;
  double x103 = x102 + x22*x34;
  double x104 = x101 + x103*x29;
  double x105 = x39*x50;
  double x106 = x103*x40 + x105;
  double x107 = pow(x0, 2);
  double x108 = pow(x10, 2);
  double x109 = pow(x12, 2);
  double x110 = x108*x76 + x109*x76;
  double x111 = x28*x75;
  double x112 = x44*x75 + x9*x90;
  double x113 = -x111 - x112*x29;
  double x114 = x39*x75;
  double x115 = -x112*x40 - x114;
  double x116 = 0.02554*x1;
  double x117 = 0.02554*x41 + 0.02554*x42;
  double x118 = x0*(x108 + x109 - 1);
  double x119 = -0.02554*x48 + 0.02554*x49;
  double x120 = -x16*x34 + x35*x36*x43;
  double x121 = x120*x29 + x96;
  double x122 = x120*x40 + x99;
  double x123 = -x102 + x23*x34;
  double x124 = -x101 + x123*x29;
  double x125 = x1*x80;
  double x126 = -x125*x44 - x80*x90;
  double x127 = -x125*x28 + x126*x29;
  double x128 = -x105 + x123*x40;
  double x129 = -x125*x39 + x126*x40;
  double x130 = -x19;
  double x131 = x1*x130 + x48;
  double x132 = x131*x44 + x34*(x130*x4 - x21);
  double x133 = x2*x3;
  double x134 = 0.02554*x133;
  double x135 = -x134 - 0.02554*x6;
  double x136 = pow(x9, 2);
  double x137 = x109*x136;
  double x138 = pow(x3, 2);
  double x139 = x109*x138;
  double x140 = x108*x136;
  double x141 = x108*x138;
  double x142 = 1.0/(x137 + x139 + x140 + x141);
  double x143 = x142*x9;
  double x144 = 1.0/(x107*x137 + x107*x139 + x107*x140 + x107*x141 + x137*x76 + x139*x76 + x140*x76 + x141*x76);
  double x145 = x133 + x6;
  double x146 = -x145*x44 + x34*(x1*x5 - x3*x30);
  double x147 = -x112;
  double x148 = x0*x144;
  double x149 = x148*x3;
  double x150 = x142*(0.02554*x1*x3*x5 - 0.02554*x30);
  double x151 = 1.0/x5;
  double x152 = x144*x151;
  double x153 = x134*x152;
  double x154 = x152*(x107 + x110);
  double x155 = x154*x3;
  double x156 = 0.12864*x19;
  double x157 = x32*x44 + x84;
  double x158 = x142*(x157*x29 + x28*x32);
  double x159 = -x93;
  double x160 = x149*x151;
  double x161 = x142*(x157*x40 + x32*x39);
  double x162 = -x92;
  double x163 = x1*x12*x3*x5 - x12*x30;
  double x164 = x10*x30 - x18*x20;
  double x165 = -x146;
  double x166 = x145*x28 + x165*x29;
  double x167 = x145*x39 + x165*x40;
  double x168 = x0*x3;
  double x169 = x163*x44 + x34*(x12*x2 + x13*x6);
  double x170 = x164*x44 + x34*(-x10*x2 - x18*x6);
  double x171 = x13*x5;
  double x172 = x142*x3;
  double x173 = x148*x9;
  double x174 = 0.02554*x152*x2*x9;
  double x175 = x154*x9;
  double x176 = x151*x173;
  *val = dq[0]*(0.0065709312000000004*x14*x16 + 0.0065709312000000004*x19*x23 + 0.060165000000000003*x3*x5*(x28*x7 + x29*x37) + 0.01821*x3*x5*(x37*x40 + x39*x7) - x46*(x16*x39 + x40*x45) - x47*(x16*x28 + x29*x45) - x52*(x23*x39 + x40*x51) - x53*(x23*x28 + x29*x51) - 0.0065709312000000004*x7*x8) + dq[1]*(x57*x58 + x57*x59 + x58*x60 + x59*x60 + x62*x64 + x62*x66 - x64*x67 - x66*x67 - x69*x71 - x69*x73 + x71*x74 + x73*x74) + base_dori[0]*(-x100*x130 - x100*x19 - x104*x63 - x106*x65 + 0.0032854656000000002*x130*x43 - x130*x98 + 0.0032854656000000002*x131*x14 + 0.0032854656000000002*x14*x50 + 0.12864*x14*(-x119*x155 + x150*x17 + x153*x80) - x156*(x11*x150 - x117*x155 + x153*x79) + 0.0032854656000000002*x19*x43 - x19*x98 + 0.030082500000000002*x3*x5*(x143*(x145*x26*x27 - x146*x29) + x149*(-x111 + x147*x29)) + 0.0091050000000000002*x3*x5*(x143*(x145*x26*x38 - x146*x40) + x149*(-x114 + x147*x40)) + 0.12864*x3*x5*(x134*x144*x9 + x135*x143) - x63*(x131*x28 + x132*x29) - x63*(x124*x155 - x127*x160 + x158*x17) - x65*(x131*x39 + x132*x40) - x65*(x128*x155 - x129*x160 + x161*x17) - x70*(-x11*x158 + x121*x155 + x159*x160) - x72*(-x11*x161 + x122*x155 + x160*x162)) + base_dori[1]*(0.0032854656000000002*x0*x3*x31 + 0.030082500000000002*x10*x104*x3*x5 + 0.0091050000000000002*x10*x106*x3*x5 - x100*x171 + 0.0032854656000000002*x12*x3*x43*x5 + 0.0032854656000000002*x14*x163 + 0.12864*x14*(x119*x175 + x13*x150 - x174*x80) - 0.0032854656000000002*x145*x8 - x156*(x117*x175 + x150*x18 - x174*x79) + 0.0032854656000000002*x164*x19 + 0.030082500000000002*x166*x3*x5 + 0.0091050000000000002*x167*x3*x5 - x168*x86 - x168*x88 - x171*x98 - 0.0032854656000000002*x18*x5*x50 + 0.030082500000000002*x19*(x121*x175 + x158*x18 + x159*x176) + 0.0091050000000000002*x19*(x122*x175 + x161*x18 + x162*x176) + 0.030082500000000002*x3*x5*(-x113*x173 + x166*x172) + 0.0091050000000000002*x3*x5*(-x115*x173 + x167*x172) - x63*(x163*x28 + x169*x29) - x63*(-x124*x175 + x127*x176 + x13*x158) - x65*(x163*x39 + x169*x40) - x65*(-x128*x175 + x129*x176 + x13*x161) - x70*(x164*x28 + x170*x29) - x72*(x164*x39 + x170*x40) - 0.12864*x8*(0.02554*x0*x1*x136*x144 - x135*x172)) + base_dori[2]*(0.0032854656000000002*x1*x14*x81 + 0.0032854656000000002*x1*x19*x79 - x100*x81 - 0.030082500000000002*x104*x79 - 0.0091050000000000002*x106*x79 + 0.030082500000000002*x3*x5*(x28*x82 + x29*x83) + 0.0091050000000000002*x3*x5*(x39*x82 + x40*x83) + 0.0032854656000000002*x31*x5*x9 + 0.0032854656000000002*x43*x81 + 0.0032854656000000002*x50*x79 - x63*(x28*x94 + x29*x95) - x65*(x39*x94 + x40*x95) - x70*x93 - x72*x92 - 0.0032854656000000002*x78 - x81*x98 - x86*x87 - x87*x88 + (1.0/2.0)*(-0.060165000000000003*x113*x77 - 0.01821*x115*x77 - 0.25728000000000001*x14*(x116*x80 + x118*x119) + 0.25728000000000001*x19*(x116*x79 + x117*x118) - x46*(x118*x128 + x129) - x47*(x118*x124 + x127) - x52*(x118*x122 + x92) - x53*(x118*x121 + x93) - 0.0065709312000000004*x78)/(x107*x108 + x107*x109 + x110));
}
