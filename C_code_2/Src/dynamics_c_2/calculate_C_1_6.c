

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_1_6(const double dq[3], const double base_dori[3], const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
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
  double x16 = x15 - x5*x7*x9;
  double x17 = x0 - x1;
  double x18 = sq[1];
  double x19 = x17*x18;
  double x20 = x7*x9;
  double x21 = x20*(-x14 - x16*x19);
  double x22 = 0.032607499999999998*x0 - 0.013937500000000002*x1;
  double x23 = 0.0091050000000000002*x22;
  double x24 = x20*(-x14 - x16*x19);
  double x25 = sbo[0];
  double x26 = x5*x9;
  double x27 = sbo[2];
  double x28 = cbo[0];
  double x29 = x27*x28;
  double x30 = x25*x7;
  double x31 = x29 + x30*x4;
  double x32 = -x25*x26 + x31*x8;
  double x33 = x10*x25 + x31*x5;
  double x34 = x19*x33;
  double x35 = -x13*x32 + x34;
  double x36 = 0.030082500000000002*x31;
  double x37 = x2*x36;
  double x38 = 0.0091050000000000002*x31;
  double x39 = x22*x38;
  double x40 = x13*x32 - x34;
  double x41 = x26*x28;
  double x42 = x25*x27;
  double x43 = x28*x7;
  double x44 = -x4*x43 + x42;
  double x45 = x41 + x44*x8;
  double x46 = x10*x28;
  double x47 = x44*x5 - x46;
  double x48 = x19*x47;
  double x49 = x13*x45 - x48;
  double x50 = 0.030082500000000002*x44;
  double x51 = x2*x50;
  double x52 = 0.0091050000000000002*x44;
  double x53 = x22*x52;
  double x54 = -x13*x45 + x48;
  double x55 = x0 + x1;
  double x56 = x20*(-x13*x26*x27 + x18*(-x10*x17*x27 + x55*x7*x9));
  double x57 = x27*x55;
  double x58 = -4*x12*x16 + x18*(x11*x17 + x57*x9);
  double x59 = x3*x58;
  double x60 = x27*x9;
  double x61 = x23*x58;
  double x62 = x4*x42 - x43;
  double x63 = -x62;
  double x64 = x13*x5;
  double x65 = x31*x55;
  double x66 = x17*x8;
  double x67 = x18*(x63*x66 + x65) + x63*x64;
  double x68 = x29*x4 + x30;
  double x69 = x64*x68;
  double x70 = -x44;
  double x71 = x18*(x17*x68*x8 - x55*x70) + x69;
  double x72 = x13*x33;
  double x73 = x17*x32;
  double x74 = x18*(x55*x62 + x73) + x72;
  double x75 = x63*x74;
  double x76 = x17*x45 - x55*x68;
  double x77 = x13*x47 + x18*x76;
  double x78 = x68*x77;
  double x79 = pow(x4, 2);
  double x80 = pow(x28, 2);
  double x81 = pow(x25, 2);
  double x82 = pow(x9, 2);
  double x83 = x80*x82 + x81*x82;
  double x84 = x18*(x27*x66 - x55*x7) + x27*x64;
  double x85 = -x84;
  double x86 = -x18*(x44*x55 + x66*x68) - x69;
  double x87 = x2*x86;
  double x88 = -x74;
  double x89 = x4*(x80 + x81 - 1);
  double x90 = x88*x89;
  double x91 = x22*x86;
  double x92 = x18*(x62*x66 - x65) + x62*x64;
  double x93 = x2*x92;
  double x94 = 4*x12*x47 + x18*x76;
  double x95 = x2*x94;
  double x96 = x22*x92;
  double x97 = x22*x94;
  double x98 = x13*(x46 + x5*x70) + x18*(x17*(-x41 + x70*x8) + x55*x68);
  double x99 = x70*x74;
  double x100 = x18*(-x55*x63 + x73) + x72;
  double x101 = x13*(x10 + x6*x7);
  double x102 = x4*x57;
  double x103 = x15*x7 - x26;
  double x104 = x101 + x18*(x102 + x103*x17);
  double x105 = x104*x27;
  double x106 = pow(x27, 2);
  double x107 = x106*x81;
  double x108 = pow(x7, 2);
  double x109 = x108*x81;
  double x110 = x106*x80;
  double x111 = x108*x80;
  double x112 = 1.0/(x107 + x109 + x110 + x111);
  double x113 = x112*x2;
  double x114 = 1.0/(x107*x79 + x107*x82 + x109*x79 + x109*x82 + x110*x79 + x110*x82 + x111*x79 + x111*x82);
  double x115 = 0.030082500000000002*x20;
  double x116 = x112*x22;
  double x117 = 0.0091050000000000002*x20;
  double x118 = -x58;
  double x119 = x113*x118;
  double x120 = x114*x4;
  double x121 = 1.0/x9;
  double x122 = x121*x7;
  double x123 = x120*x122;
  double x124 = x79 + x83;
  double x125 = x116*x118;
  double x126 = x114*x124;
  double x127 = x122*x126;
  double x128 = x4*x7;
  double x129 = x20*(-x101 + x18*(-x102 - x103*x17));
  double x130 = x55*x9;
  double x131 = x13*(-x15*x25 + x25*x5*x7*x9) + x18*(x130*x42 + x17*(x10*x30 + x25*x6));
  double x132 = x13*(x15*x28 - x26*x43) + x18*(-x130*x29 + x17*(-x10*x43 - x28*x6));
  double x133 = x30*x74;
  double x134 = x3*x9;
  double x135 = x23*x9;
  double x136 = x43*x77;
  double x137 = -x104*x7;
  double x138 = x120*x27;
  double x139 = x138*x85;
  double x140 = x121*x138;
  double x141 = x121*x126;
  double x142 = x141*x27*x88;
  double x143 = x141*x27;
  *val = dq[0]*(x21*x23 + x21*x3 - x23*x24 - x24*x3 + x35*x37 + x35*x39 + x37*x40 + x39*x40 + x49*x51 + x49*x53 + x51*x54 + x53*x54) + base_dori[0]*(x100*x51 + x100*x53 - x115*(-x105*x113 + x114*x2*x4*x7*x84) - x117*(-x105*x116 + x114*x22*x4*x7*x84) + x23*x99 + x3*x99 + x36*(x119*x42 - x123*x93 + x127*x95) + x37*x77 + x37*x98 + x38*(-x123*x96 + x125*x42 + x127*x97) + x39*x77 + x39*x98 + x50*(x114*x121*x124*x2*x7*x88 - x119*x29 - x123*x87) + x52*(x114*x121*x124*x22*x7*x88 - x123*x91 - x125*x29)) + base_dori[1]*(-x115*(x113*x137 + x139*x2) - x117*(x116*x137 + x139*x22) - x128*x59 - x128*x61 + x129*x23 + x129*x3 + x131*x37 + x131*x39 + x132*x51 + x132*x53 + x133*x134 + x133*x135 - x134*x136 - x135*x136 + x36*(x119*x30 + x140*x93 - x143*x95) + x38*(x125*x30 + x140*x96 - x143*x97) - x50*(x119*x43 - x140*x87 + x142*x2) - x52*(x125*x43 - x140*x91 + x142*x22)) + base_dori[2]*(x23*x56 + x23*x75 + x23*x78 + x3*x56 + x3*x75 + x3*x78 + x37*x67 + x39*x67 + x51*x71 + x53*x71 - x59*x60 - x60*x61 - 1.0/2.0*(0.060165000000000003*x2*x7*x82*x85 + 0.01821*x22*x7*x82*x85 - 0.060165000000000003*x31*(x89*x95 + x93) - 0.01821*x31*(x89*x97 + x96) - 0.060165000000000003*x44*(x2*x90 + x87) - 0.01821*x44*(x22*x90 + x91))/(x79*x80 + x79*x81 + x83));
}
