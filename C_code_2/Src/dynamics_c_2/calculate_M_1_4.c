

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_1_4(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1];
  double x1 = sq[0];
  double x2 = x0*x1;
  double x3 = cbo[2];
  double x4 = cbo[1];
  double x5 = cq[0];
  double x6 = x4*x5;
  double x7 = x2 - x3*x6;
  double x8 = cq[1];
  double x9 = 4*x8;
  double x10 = sq[1];
  double x11 = M_SQRT2;
  double x12 = sqrt(6);
  double x13 = x11 + x12;
  double x14 = sbo[2];
  double x15 = x14*x4;
  double x16 = x11 - x12;
  double x17 = x0*x5;
  double x18 = x1*x4;
  double x19 = x17 + x18*x3;
  double x20 = x13*x15 + x16*x19;
  double x21 = x10*x20 - x7*x9;
  double x22 = x0*x14;
  double x23 = 0.54191999999999996*x22;
  double x24 = 0.016767499999999998*x11 + 0.016512499999999999*x12;
  double x25 = x2*x3 - x6;
  double x26 = x13*x25 - x16*x22;
  double x27 = 0.016512499999999999*x11 - 0.016767499999999998*x12;
  double x28 = 4*x10;
  double x29 = -x28*(x17*x3 + x18) + x8*(x13*x22 + x16*x25);
  double x30 = sbo[0];
  double x31 = pow(x30, 2);
  double x32 = pow(x14, 2);
  double x33 = x31*x32;
  double x34 = pow(x3, 2);
  double x35 = x31*x34;
  double x36 = cbo[0];
  double x37 = pow(x36, 2);
  double x38 = x32*x37;
  double x39 = x34*x37;
  double x40 = 1.0/(x33 + x35 + x38 + x39);
  double x41 = x3*x40;
  double x42 = -0.54191999999999996*x3;
  double x43 = x1*x14;
  double x44 = x13*x43 + x16*x3;
  double x45 = x28*x5;
  double x46 = -x14*x45 + x8*(-x13*x3 + x16*x43);
  double x47 = pow(x0, 2);
  double x48 = pow(x4, 2);
  double x49 = 1.0/(x33*x47 + x33*x48 + x35*x47 + x35*x48 + x38*x47 + x38*x48 + x39*x47 + x39*x48);
  double x50 = x22*x49;
  double x51 = 1.9252800000000001*x27;
  double x52 = 0.013937500000000002*x11 + 0.032607499999999998*x12;
  double x53 = 0.032607499999999998*x11 - 0.013937500000000002*x12;
  double x54 = 0.58272000000000002*x53;
  double x55 = x14*x30;
  double x56 = x3*x36;
  double x57 = x0*x56;
  double x58 = x55 - x57;
  double x59 = -x18*x36 + x5*x58;
  double x60 = x3*x30;
  double x61 = x14*x36;
  double x62 = x0*x61;
  double x63 = x60 + x62;
  double x64 = x13*x63;
  double x65 = x1*x58 + x36*x6;
  double x66 = x16*x65 - x64;
  double x67 = x10*x66 + x59*x9;
  double x68 = 0.54191999999999996*x15;
  double x69 = x13*x19 - x15*x16;
  double x70 = x20*x8 + x28*x7;
  double x71 = x24*x69 + x27*x70 + x68;
  double x72 = x40*x56;
  double x73 = -x1*x64 + x16*x58;
  double x74 = x16*x63;
  double x75 = -x45*x63 + x8*(x1*x74 + x13*x58);
  double x76 = -0.54191999999999996*x55 + 0.54191999999999996*x57;
  double x77 = 1.0/x4;
  double x78 = x50*x77;
  double x79 = x0*x60;
  double x80 = x61 + x79;
  double x81 = x18*x30 + x5*x80;
  double x82 = x0*x55;
  double x83 = -x56 + x82;
  double x84 = x13*x83;
  double x85 = x1*x80 - x30*x6;
  double x86 = x16*x85 + x84;
  double x87 = -x28*x81 + x8*x86;
  double x88 = x16*x83;
  double x89 = x13*x85 - x88;
  double x90 = -0.54191999999999996*x56 + 0.54191999999999996*x82;
  double x91 = x31*x48 + x37*x48;
  double x92 = x14*x49*x77;
  double x93 = x92*(x47 + x91);
  double x94 = x52*x69 + x53*x70 + x68;
  double x95 = x10*x86 + x81*x9;
  double x96 = x40*x60;
  double x97 = 4*x10*x5*x83 - x8*(x1*x88 - x13*x80);
  double x98 = x1*x84 + x16*x80;
  double x99 = 0.54191999999999996*x61 + 0.54191999999999996*x79;
  double x100 = x28*x59;
  double x101 = x100 - x66*x8;
  double x102 = x13*x65 + x74;
  double x103 = 0.54191999999999996*x60 + 0.54191999999999996*x62;
  double x104 = -x13*x70 + x16*x69;
  double x105 = -x100 + x66*x8;
  double x106 = x102*x16 - x105*x13;
  double x107 = -x13*x87 + x16*x89;
  double x108 = x91*x92;
  double x109 = x49*x62 + x96;
  double x110 = x49*x82 - x72;
  double x111 = x108*x69;
  double x112 = x102*x109;
  double x113 = x110*x89;
  double x114 = pow(x69, 2);
  double x115 = pow(x102, 2);
  double x116 = pow(x89, 2);
  double x117 = x21*x69;
  double x118 = x69*x70;
  double x119 = x102*x67;
  double x120 = x102*x105;
  double x121 = x89*x95;
  double x122 = x87*x89;
  double x123 = x108*x21;
  double x124 = x110*x95;
  double x125 = x109*x67;
  double x126 = x108*x70;
  double x127 = x110*x87;
  double x128 = x105*x109;
  double x129 = cq[2];
  double x130 = x129*x13;
  double x131 = sq[2];
  double x132 = 4*x131;
  double x133 = x129*x16;
  double x134 = x130*x69 + x132*x21 + x133*x70;
  double x135 = x102*x130 + x105*x133 + x132*x67;
  double x136 = x130*x89 + x132*x95 + x133*x87;
  double x137 = x13*x131;
  double x138 = 4*x129;
  double x139 = x131*x16*x70 + x137*x69 - x138*x21;
  double x140 = x102*x137 + x105*x131*x16 - x138*x67;
  double x141 = x131*x16*x87 + x137*x89 - x138*x95;
  *val = (1.0/128.0)*x21*x51*(x41*(x23 + x24*x26 + x27*x29) - x50*(-x24*x44 - x27*x46 - x42)) + (1.0/128.0)*x21*x54*(x41*(x23 + x26*x52 + x29*x53) - x50*(-x42 - x44*x52 - x46*x53)) + (1.0/128.0)*x51*x67*(x71*x72 + x78*(x24*x73 - x27*x75 + x76) + x93*(x24*x89 + x27*x87 + x90)) - 1.0/128.0*x51*x95*(x71*x96 + x78*(-x24*x98 + x27*x97 + x99) - x93*(x101*x27 - x102*x24 + x103)) + (1.0/128.0)*x54*x67*(x72*x94 + x78*(x52*x73 - x53*x75 + x76) + x93*(x52*x89 + x53*x87 + x90)) - 1.0/128.0*x54*x95*(x78*(-x52*x98 + x53*x97 + x99) - x93*(x101*x53 - x102*x52 + x103) + x94*x96) + (1.0/32.0)*(x111 - x112 + x113)*(3.9389987500000003e-5*x114 + 3.9389987500000003e-5*x115 + 3.9389987500000003e-5*x116 + 1.7000000000000003e-10*x117 - 1.22701775e-5*x118 + 1.7000000000000003e-10*x119 - 1.22701775e-5*x120 + 1.7000000000000003e-10*x121 - 1.22701775e-5*x122) + (1.0/128.0)*(x114 + x115 + x116)*(0.00015755995000000001*x111 - 0.00015755995000000001*x112 + 0.00015755995000000001*x113 + 6.8000000000000013e-10*x123 + 6.8000000000000013e-10*x124 - 6.8000000000000013e-10*x125 - 4.908071e-5*x126 - 4.908071e-5*x127 + 4.908071e-5*x128) + (1.0/128.0)*(x117 + x119 + x121)*(6.8000000000000013e-10*x111 - 6.8000000000000013e-10*x112 + 6.8000000000000013e-10*x113 + 0.00054005738000000004*x123 + 0.00054005738000000004*x124 - 0.00054005738000000004*x125 + 2.3100000000000001e-9*x126 + 2.3100000000000001e-9*x127 - 2.3100000000000001e-9*x128) + (1.0/128.0)*(x118 + x120 + x122)*(-4.908071e-5*x111 + 4.908071e-5*x112 - 4.908071e-5*x113 + 2.3100000000000001e-9*x123 + 2.3100000000000001e-9*x124 - 2.3100000000000001e-9*x125 + 0.00050018127000000005*x126 + 0.00050018127000000005*x127 - 0.00050018127000000005*x128) + (1.0/32.0)*(x123 + x124 - x125)*(1.7000000000000003e-10*x114 + 1.7000000000000003e-10*x115 + 1.7000000000000003e-10*x116 + 0.00013501434500000001*x117 + 5.7750000000000002e-10*x118 + 0.00013501434500000001*x119 + 5.7750000000000002e-10*x120 + 0.00013501434500000001*x121 + 5.7750000000000002e-10*x122) + (1.0/32.0)*(x126 + x127 - x128)*(-1.22701775e-5*x114 - 1.22701775e-5*x115 - 1.22701775e-5*x116 + 5.7750000000000002e-10*x117 + 0.00012504531750000001*x118 + 5.7750000000000002e-10*x119 + 0.00012504531750000001*x120 + 5.7750000000000002e-10*x121 + 0.00012504531750000001*x122) - 5.1988466796875003e-8*(x102*x106 + x104*x69 + x107*x89)*(-x104*x108 + x106*x109 - x107*x110) + 2.8224560546875002e-8*(x102*x135 + x134*x69 + x136*x89)*(x108*x134 - x109*x135 + x110*x136) + 2.8224560546875002e-8*(x102*x140 + x139*x69 + x141*x89)*(x108*x139 - x109*x140 + x110*x141);
}
