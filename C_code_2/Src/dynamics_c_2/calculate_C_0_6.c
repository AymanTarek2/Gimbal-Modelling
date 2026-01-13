

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_0_6(const double dq[3], const double base_dori[3], const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
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
  double x12 = x1*x5;
  double x13 = x11 - x12*x3;
  double x14 = -x13;
  double x15 = M_SQRT2;
  double x16 = sqrt(6);
  double x17 = x15 - x16;
  double x18 = sq[1];
  double x19 = x17*x18;
  double x20 = -x10 + x14*x19;
  double x21 = 0.016512499999999999*x15 - 0.016767499999999998*x16;
  double x22 = x3*x5;
  double x23 = 0.030082500000000002*x22;
  double x24 = 0.032607499999999998*x15 - 0.013937500000000002*x16;
  double x25 = 0.0091050000000000002*x22;
  double x26 = -x10 - x13*x19;
  double x27 = sbo[0];
  double x28 = sbo[2];
  double x29 = cbo[0];
  double x30 = x28*x29;
  double x31 = x27*x3;
  double x32 = x0*x31 + x30;
  double x33 = -x12*x27 + x32*x4;
  double x34 = -x33;
  double x35 = x27*x6;
  double x36 = x1*x32;
  double x37 = x35 + x36;
  double x38 = x19*x37;
  double x39 = x34*x9 + x38;
  double x40 = 0.030082500000000002*x32;
  double x41 = x21*x40;
  double x42 = 0.0091050000000000002*x32;
  double x43 = x24*x42;
  double x44 = x33*x9 - x38;
  double x45 = x12*x29;
  double x46 = x27*x28;
  double x47 = x29*x3;
  double x48 = -x0*x47 + x46;
  double x49 = x4*x48 + x45;
  double x50 = x29*x6;
  double x51 = x1*x48;
  double x52 = -x50 + x51;
  double x53 = x19*x52;
  double x54 = x49*x9 - x53;
  double x55 = 0.030082500000000002*x48;
  double x56 = x21*x55;
  double x57 = 0.0091050000000000002*x48;
  double x58 = x24*x57;
  double x59 = -x49;
  double x60 = x53 + x59*x9;
  double x61 = x1*x28;
  double x62 = pow(x5, 2);
  double x63 = x3*x62;
  double x64 = x61*x63;
  double x65 = x0*x30 + x31;
  double x66 = x0*x46 - x47;
  double x67 = -x66;
  double x68 = x15 + x16;
  double x69 = 0.016767499999999998*x15 + 0.016512499999999999*x16;
  double x70 = x68*x69;
  double x71 = x12*x28;
  double x72 = 4*x18;
  double x73 = x17*x8;
  double x74 = x28*x6*x72 + x71*x73;
  double x75 = 0.013937500000000002*x15 + 0.032607499999999998*x16;
  double x76 = x68*x75;
  double x77 = x7*x72;
  double x78 = x13*x73 - x77;
  double x79 = 0.0091050000000000002*x13*x76 + 0.0091050000000000002*x24*x78;
  double x80 = x28*x5;
  double x81 = 0.030082500000000002*x13*x70 + 0.030082500000000002*x21*x78;
  double x82 = x1*x65;
  double x83 = x4*x72;
  double x84 = x65*x83 + x73*x82;
  double x85 = x24*x84 + x76*x82;
  double x86 = x21*x84 + x70*x82;
  double x87 = x1*x67;
  double x88 = x67*x83 + x73*x87;
  double x89 = x37*x70;
  double x90 = x33*x72 + x37*x73;
  double x91 = x21*x90 + x89;
  double x92 = 0.030082500000000002*x91;
  double x93 = x37*x76;
  double x94 = x24*x90 + x93;
  double x95 = 0.0091050000000000002*x94;
  double x96 = x52*x70;
  double x97 = x52*x73;
  double x98 = x49*x72 + x97;
  double x99 = x21*x98 + x96;
  double x100 = x52*x76;
  double x101 = x100 + x24*x98;
  double x102 = pow(x0, 2);
  double x103 = pow(x29, 2);
  double x104 = pow(x27, 2);
  double x105 = x103*x62 + x104*x62;
  double x106 = x61*x70;
  double x107 = x28*x83 + x61*x73;
  double x108 = -x106 - x107*x21;
  double x109 = x61*x76;
  double x110 = -x107*x24 - x109;
  double x111 = 0.02554*x1;
  double x112 = 0.02554*x35 + 0.02554*x36;
  double x113 = x0*(x103 + x104 - 1);
  double x114 = -0.02554*x50 + 0.02554*x51;
  double x115 = x17*x37*x8 - x34*x72;
  double x116 = x115*x21 + x89;
  double x117 = x115*x24 + x93;
  double x118 = x59*x72 - x97;
  double x119 = x118*x21 - x96;
  double x120 = x1*x66;
  double x121 = -x120*x73 - x66*x83;
  double x122 = -x120*x70 + x121*x21;
  double x123 = -x100 + x118*x24;
  double x124 = -x120*x76 + x121*x24;
  double x125 = -x48;
  double x126 = x1*x125 + x50;
  double x127 = x126*x73 + x72*(x125*x4 - x45);
  double x128 = x2*x3;
  double x129 = 0.02554*x128;
  double x130 = -x129 - 0.02554*x6;
  double x131 = pow(x28, 2);
  double x132 = x104*x131;
  double x133 = pow(x3, 2);
  double x134 = x104*x133;
  double x135 = x103*x131;
  double x136 = x103*x133;
  double x137 = 1.0/(x132 + x134 + x135 + x136);
  double x138 = x137*x28;
  double x139 = 1.0/(x102*x132 + x102*x134 + x102*x135 + x102*x136 + x132*x62 + x134*x62 + x135*x62 + x136*x62);
  double x140 = x139*x28;
  double x141 = x128 + x6;
  double x142 = -x141*x73 + x72*(x1*x5 - x11*x3);
  double x143 = -x107;
  double x144 = x0*x3;
  double x145 = x139*x144;
  double x146 = 0.02554*x1*x3*x5 - 0.02554*x11;
  double x147 = x137*x30;
  double x148 = 1.0/x5;
  double x149 = x148*x65;
  double x150 = x129*x139;
  double x151 = x148*(x102 + x105);
  double x152 = x112*x151;
  double x153 = x139*x3;
  double x154 = x137*x46;
  double x155 = x148*x66;
  double x156 = x151*x153;
  double x157 = 0.12864*x32;
  double x158 = x14*x73 + x77;
  double x159 = x14*x70 + x158*x21;
  double x160 = -x86;
  double x161 = x145*x148;
  double x162 = x14*x76 + x158*x24;
  double x163 = -x85;
  double x164 = x1*x27*x3*x5 - x11*x27;
  double x165 = x11*x29 - x12*x47;
  double x166 = -x142;
  double x167 = x141*x70 + x166*x21;
  double x168 = x141*x76 + x166*x24;
  double x169 = x164*x73 + x72*(x2*x27 + x31*x6);
  double x170 = x165*x73 + x72*(-x2*x29 - x47*x6);
  double x171 = x31*x5;
  double x172 = x137*x3;
  double x173 = x0*x140;
  double x174 = x137*x146;
  double x175 = 0.02554*x140*x2;
  double x176 = x140*x151;
  double x177 = x137*x47;
  double x178 = x148*x173;
  double x179 = x137*x31;
  *val = dq[1]*(-x20*x21*x23 - x20*x24*x25 + 0.030082500000000002*x21*x26*x3*x5 + 0.0091050000000000002*x24*x26*x3*x5 - x39*x41 - x39*x43 - x41*x44 - x43*x44 - x54*x56 - x54*x58 - x56*x60 - x58*x60) + base_dori[0]*(-x101*x42 + 0.0032854656000000002*x125*x37 - x125*x92 - x125*x95 + 0.0032854656000000002*x126*x32 - x157*(-x114*x156 + x146*x154 + x150*x155) - 0.12864*x22*(x129*x140 + x130*x138) - x23*(x138*(x141*x68*x69 - x142*x21) + x145*(-x106 + x143*x21)) - x25*(x138*(x141*x68*x75 - x142*x24) + x145*(-x109 + x143*x24)) + 0.0032854656000000002*x32*x52 + 0.030082500000000002*x32*(x119*x156 - x122*x161 + x154*x159) + 0.0091050000000000002*x32*(x123*x156 - x124*x161 + x154*x162) + 0.0032854656000000002*x37*x48 - x40*x99 - x40*(x126*x70 + x127*x21) - x42*(x126*x76 + x127*x24) + 0.030082500000000002*x48*(x116*x156 - x147*x159 + x160*x161) + 0.0091050000000000002*x48*(x117*x156 - x147*x162 + x161*x163) + 0.12864*x48*(x146*x147 + x149*x150 - x152*x153) - x55*x91 - x57*x94) + base_dori[1]*(0.0032854656000000002*x0*x13*x3 + 0.0091050000000000002*x101*x29*x3*x5 - 0.0032854656000000002*x141*x22 - x144*x79 - x144*x81 - x157*(x114*x176 - x155*x175 + x174*x31) + 0.0032854656000000002*x164*x32 + 0.0032854656000000002*x165*x48 + 0.030082500000000002*x167*x3*x5 + 0.0091050000000000002*x168*x3*x5 - x171*x92 - x171*x95 - x23*(-x108*x173 + x167*x172) - x25*(-x110*x173 + x168*x172) + 0.0032854656000000002*x27*x3*x37*x5 + 0.030082500000000002*x29*x3*x5*x99 + 0.12864*x3*x5*(0.02554*x0*x1*x131*x139 - x130*x172) + 0.030082500000000002*x32*(-x119*x176 + x122*x178 + x159*x179) + 0.0091050000000000002*x32*(-x123*x176 + x124*x178 + x162*x179) - x40*(x164*x70 + x169*x21) - x42*(x164*x76 + x169*x24) - 0.0032854656000000002*x47*x5*x52 + 0.12864*x48*(x140*x152 - x149*x175 + x174*x47) - x55*(x165*x70 + x170*x21) - x55*(x116*x176 + x159*x177 + x160*x178) - x57*(x165*x76 + x170*x24) - x57*(x117*x176 + x162*x177 + x163*x178)) + base_dori[2]*(0.0032854656000000002*x1*x32*x67 + 0.0032854656000000002*x1*x48*x65 - 0.0091050000000000002*x101*x65 + 0.0032854656000000002*x13*x28*x5 + 0.030082500000000002*x3*x5*(x21*x74 + x70*x71) + 0.0091050000000000002*x3*x5*(x24*x74 + x71*x76) + 0.0032854656000000002*x37*x67 - x40*(x21*x88 + x70*x87) - x42*(x24*x88 + x76*x87) + 0.0032854656000000002*x52*x65 - x55*x86 - x57*x85 - 0.0032854656000000002*x64 - 0.030082500000000002*x65*x99 - x67*x92 - x67*x95 - x79*x80 - x80*x81 - 1.0/2.0*(-0.060165000000000003*x108*x63 - 0.01821*x110*x63 - 0.25728000000000001*x32*(x111*x66 + x113*x114) - 0.060165000000000003*x32*(x113*x119 + x122) - 0.01821*x32*(x113*x123 + x124) + 0.25728000000000001*x48*(x111*x65 + x112*x113) - 0.060165000000000003*x48*(x113*x116 + x86) - 0.01821*x48*(x113*x117 + x85) - 0.0065709312000000004*x64)/(x102*x103 + x102*x104 + x105));
}
