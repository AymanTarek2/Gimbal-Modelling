

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_0_8(const double dq[3], const double base_dori[3], const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
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
  double x22 = 0.030082500000000002*x0;
  double x23 = x21*x22;
  double x24 = 0.032607499999999998*x15 - 0.013937500000000002*x16;
  double x25 = 0.0091050000000000002*x0;
  double x26 = x24*x25;
  double x27 = -x10 - x13*x19;
  double x28 = sbo[0];
  double x29 = x12*x28;
  double x30 = sbo[2];
  double x31 = cbo[0];
  double x32 = x30*x31;
  double x33 = x28*x3;
  double x34 = x0*x33 + x32;
  double x35 = -x29 + x34*x4;
  double x36 = -x35;
  double x37 = x28*x6;
  double x38 = x1*x34;
  double x39 = x37 + x38;
  double x40 = x19*x39;
  double x41 = x36*x9 + x40;
  double x42 = 0.030082500000000002*x5;
  double x43 = x28*x42;
  double x44 = x21*x43;
  double x45 = 0.0091050000000000002*x5;
  double x46 = x28*x45;
  double x47 = x24*x46;
  double x48 = x35*x9 - x40;
  double x49 = x12*x31;
  double x50 = x28*x30;
  double x51 = x3*x31;
  double x52 = -x0*x51 + x50;
  double x53 = x4*x52 + x49;
  double x54 = x31*x6;
  double x55 = x1*x52;
  double x56 = -x54 + x55;
  double x57 = x19*x56;
  double x58 = x53*x9 - x57;
  double x59 = x31*x42;
  double x60 = x21*x59;
  double x61 = x31*x45;
  double x62 = x24*x61;
  double x63 = -x53;
  double x64 = x57 + x63*x9;
  double x65 = 0.0032854656000000002*x5;
  double x66 = x2*x30;
  double x67 = x0*x32 + x33;
  double x68 = x0*x50 - x51;
  double x69 = -x68;
  double x70 = x15 + x16;
  double x71 = 0.016767499999999998*x15 + 0.016512499999999999*x16;
  double x72 = x70*x71;
  double x73 = x12*x30;
  double x74 = 4*x18;
  double x75 = x17*x8;
  double x76 = x30*x6*x74 + x73*x75;
  double x77 = 0.013937500000000002*x15 + 0.032607499999999998*x16;
  double x78 = x70*x77;
  double x79 = x1*x67;
  double x80 = x4*x74;
  double x81 = x67*x80 + x75*x79;
  double x82 = x24*x81 + x78*x79;
  double x83 = x21*x81 + x72*x79;
  double x84 = x1*x69;
  double x85 = x69*x80 + x75*x84;
  double x86 = pow(x0, 2);
  double x87 = pow(x31, 2);
  double x88 = pow(x28, 2);
  double x89 = pow(x5, 2);
  double x90 = x87*x89 + x88*x89;
  double x91 = 0.02554*x1;
  double x92 = 0.02554*x37 + 0.02554*x38;
  double x93 = x0*(x87 + x88 - 1);
  double x94 = -0.02554*x54 + 0.02554*x55;
  double x95 = x1*x30;
  double x96 = x72*x95;
  double x97 = x30*x80 + x75*x95;
  double x98 = x0*(-x21*x97 - x96);
  double x99 = x78*x95;
  double x100 = x0*(-x24*x97 - x99);
  double x101 = x39*x72;
  double x102 = x17*x39*x8 - x36*x74;
  double x103 = x101 + x102*x21;
  double x104 = x39*x78;
  double x105 = x102*x24 + x104;
  double x106 = x56*x72;
  double x107 = -x106;
  double x108 = x56*x75;
  double x109 = -x108 + x63*x74;
  double x110 = x107 + x109*x21;
  double x111 = x1*x68;
  double x112 = -x111*x75 - x68*x80;
  double x113 = -x111*x72 + x112*x21;
  double x114 = x56*x78;
  double x115 = -x114;
  double x116 = x109*x24 + x115;
  double x117 = -x111*x78 + x112*x24;
  double x118 = -x52;
  double x119 = x1*x118 + x54;
  double x120 = x28*x65;
  double x121 = x119*x75 + x74*(x118*x4 - x49);
  double x122 = x108 + x53*x74;
  double x123 = x106 + x122*x21;
  double x124 = x114 + x122*x24;
  double x125 = x2*x3;
  double x126 = 0.02554*x125;
  double x127 = -x126 - 0.02554*x6;
  double x128 = pow(x30, 2);
  double x129 = x128*x88;
  double x130 = pow(x3, 2);
  double x131 = x130*x88;
  double x132 = x128*x87;
  double x133 = x130*x87;
  double x134 = 1.0/(x129 + x131 + x132 + x133);
  double x135 = x134*x30;
  double x136 = 1.0/(x129*x86 + x129*x89 + x131*x86 + x131*x89 + x132*x86 + x132*x89 + x133*x86 + x133*x89);
  double x137 = x136*x30;
  double x138 = x125 + x6;
  double x139 = -x138*x75 + x74*(x1*x5 - x11*x3);
  double x140 = -x97;
  double x141 = x136*x3;
  double x142 = x0*x141;
  double x143 = x134*(0.02554*x1*x3*x5 - 0.02554*x11);
  double x144 = 1.0/x5;
  double x145 = x126*x136*x144;
  double x146 = x144*(x86 + x90);
  double x147 = x141*x146;
  double x148 = x7*x74;
  double x149 = x14*x75 + x148;
  double x150 = x14*x72 + x149*x21;
  double x151 = -x83;
  double x152 = x142*x144;
  double x153 = x14*x78 + x149*x24;
  double x154 = -x82;
  double x155 = x134*x150;
  double x156 = -x122;
  double x157 = x134*x153;
  double x158 = 0.0032854656000000002*x0;
  double x159 = x1*x28*x3*x5 - x11*x28;
  double x160 = x11*x31 - x12*x51;
  double x161 = x138*x70;
  double x162 = -x139;
  double x163 = x161*x71 + x162*x21;
  double x164 = x161*x77 + x162*x24;
  double x165 = x13*x75 - x148;
  double x166 = x159*x75 + x74*(x2*x28 + x33*x6);
  double x167 = x160*x75 + x74*(-x2*x31 - x51*x6);
  double x168 = x35*x74 + x39*x75;
  double x169 = x134*x3;
  double x170 = x137*x144;
  double x171 = 0.02554*x170*x2;
  double x172 = x137*x146;
  double x173 = x0*x170;
  *val = dq[1]*(-x20*x23 - x20*x26 + x23*x27 + x26*x27 + x41*x44 + x41*x47 + x44*x48 + x47*x48 - x58*x60 - x58*x62 - x60*x64 - x62*x64) + base_dori[0]*(-0.12864*x0*(x126*x137 + x127*x135) - x119*x120 - x120*x56 + 0.030082500000000002*x123*x28*x5 + 0.0091050000000000002*x124*x28*x5 - x22*(x135*(x138*x70*x71 - x139*x21) + x142*(x140*x21 - x96)) - x25*(x135*(x138*x70*x77 - x139*x24) + x142*(x140*x24 - x99)) + 0.030082500000000002*x28*x5*(x119*x72 + x121*x21) + 0.0091050000000000002*x28*x5*(x119*x78 + x121*x24) + 0.12864*x28*x5*(x143*x50 + x145*x68 - x147*x94) + 0.12864*x31*x5*(x143*x32 + x145*x67 - x147*x92) - x43*(-x113*x152 + x147*(x107 + x156*x21) + x155*x50) - x46*(-x117*x152 + x147*(x115 + x156*x24) + x157*x50) - x59*(-x103*x147 + x134*x150*x30*x31 - x151*x152) - x61*(-x105*x147 + x134*x153*x30*x31 - x152*x154)) + base_dori[1]*(0.030082500000000002*x0*x123*x31 + 0.0091050000000000002*x0*x124*x31 + 0.030082500000000002*x0*x163 + 0.0091050000000000002*x0*x164 + 0.0032854656000000002*x0*x28*x39 + 0.12864*x0*(0.02554*x0*x1*x128*x136 - x127*x169) - x120*x159 - x13*x65 - x138*x158 - x158*x31*x56 + 0.0032854656000000002*x160*x31*x5 - x22*x28*(x101 + x168*x21) - x22*(-x137*x98 + x163*x169) - x25*x28*(x104 + x168*x24) - x25*(-x100*x137 + x164*x169) + 0.030082500000000002*x28*x5*(x159*x72 + x166*x21) + 0.0091050000000000002*x28*x5*(x159*x78 + x166*x24) + 0.12864*x28*x5*(x143*x33 - x171*x68 + x172*x94) + 0.12864*x31*x5*(x143*x51 - x171*x67 + x172*x92) - x43*(-x110*x172 + x113*x173 + x155*x33) - x46*(-x116*x172 + x117*x173 + x157*x33) + 0.030082500000000002*x5*(x13*x72 + x165*x21) + 0.0091050000000000002*x5*(x13*x78 + x165*x24) - x59*(x160*x72 + x167*x21) - x59*(x103*x172 + x151*x173 + x155*x51) - x61*(x160*x78 + x167*x24) - x61*(x105*x172 + x154*x173 + x157*x51)) + base_dori[2]*(x22*(x21*x76 + x72*x73) + x25*(x24*x76 + x73*x78) - 0.0032854656000000002*x29*x69 + x43*(x21*x85 + x72*x84) + x46*(x24*x85 + x78*x84) + 0.0032854656000000002*x49*x67 - 1.0/2.0*x5*(-0.01821*x100 + 0.060165000000000003*x28*(x110*x93 + x113) + 0.01821*x28*(x116*x93 + x117) + 0.25728000000000001*x28*(x68*x91 + x93*x94) - 0.060165000000000003*x31*(x103*x93 + x83) - 0.01821*x31*(x105*x93 + x82) + 0.25728000000000001*x31*(x67*x91 + x92*x93) - 0.0065709312000000004*x66 - 0.060165000000000003*x98)/(x86*x87 + x86*x88 + x90) - x59*x83 - x61*x82 - x65*x66);
}
