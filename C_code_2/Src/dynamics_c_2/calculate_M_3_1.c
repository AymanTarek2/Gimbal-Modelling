

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_3_1(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = M_SQRT2;
  double x1 = sqrt(6);
  double x2 = 0.016512499999999999*x0 - 0.016767499999999998*x1;
  double x3 = sbo[1];
  double x4 = sq[0];
  double x5 = x3*x4;
  double x6 = cbo[2];
  double x7 = cbo[1];
  double x8 = cq[0];
  double x9 = x7*x8;
  double x10 = x5 - x6*x9;
  double x11 = cq[1];
  double x12 = 4*x11;
  double x13 = sq[1];
  double x14 = x0 + x1;
  double x15 = sbo[2];
  double x16 = x15*x7;
  double x17 = x0 - x1;
  double x18 = x3*x8;
  double x19 = x4*x7;
  double x20 = x18 + x19*x6;
  double x21 = x14*x16 + x17*x20;
  double x22 = -x10*x12 + x13*x21;
  double x23 = x15*x3;
  double x24 = 0.54191999999999996*x23;
  double x25 = 0.016767499999999998*x0 + 0.016512499999999999*x1;
  double x26 = x5*x6 - x9;
  double x27 = x14*x26 - x17*x23;
  double x28 = -x11*(x14*x23 + x17*x26) + 4*x13*(x18*x6 + x19);
  double x29 = sbo[0];
  double x30 = pow(x29, 2);
  double x31 = pow(x15, 2);
  double x32 = x30*x31;
  double x33 = pow(x6, 2);
  double x34 = x30*x33;
  double x35 = cbo[0];
  double x36 = pow(x35, 2);
  double x37 = x31*x36;
  double x38 = x33*x36;
  double x39 = 1.0/(x32 + x34 + x37 + x38);
  double x40 = x15*x39;
  double x41 = 0.54191999999999996*x6;
  double x42 = x15*x4;
  double x43 = -x14*x42 - x17*x6;
  double x44 = -x11*(-x14*x6 + x17*x42) + 4*x13*x15*x8;
  double x45 = pow(x3, 2);
  double x46 = pow(x7, 2);
  double x47 = 1.0/(x32*x45 + x32*x46 + x34*x45 + x34*x46 + x37*x45 + x37*x46 + x38*x45 + x38*x46);
  double x48 = x47*x6;
  double x49 = x3*x48;
  double x50 = 0.032607499999999998*x0 - 0.013937500000000002*x1;
  double x51 = 0.013937500000000002*x0 + 0.032607499999999998*x1;
  double x52 = x15*x29;
  double x53 = x35*x6;
  double x54 = x3*x53;
  double x55 = x52 - x54;
  double x56 = -x19*x35 + x55*x8;
  double x57 = x29*x6;
  double x58 = x15*x35;
  double x59 = x3*x58;
  double x60 = x57 + x59;
  double x61 = x14*x60;
  double x62 = x35*x9 + x4*x55;
  double x63 = x17*x62 - x61;
  double x64 = x12*x56 + x13*x63;
  double x65 = 0.54191999999999996*x16;
  double x66 = x14*x20 - x16*x17;
  double x67 = 4*x13;
  double x68 = x10*x67 + x11*x21;
  double x69 = x2*x68 + x25*x66 + x65;
  double x70 = x39*x58;
  double x71 = x17*x55 - x4*x61;
  double x72 = x17*x60;
  double x73 = x11*(x14*x55 + x4*x72) - x60*x67*x8;
  double x74 = -0.54191999999999996*x52 + 0.54191999999999996*x54;
  double x75 = 1.0/x7;
  double x76 = x49*x75;
  double x77 = x3*x57;
  double x78 = x58 + x77;
  double x79 = x19*x29 + x78*x8;
  double x80 = x3*x52;
  double x81 = -x53 + x80;
  double x82 = x14*x81;
  double x83 = -x29*x9 + x4*x78;
  double x84 = x17*x83 + x82;
  double x85 = x11*x84 - x67*x79;
  double x86 = x17*x81;
  double x87 = x14*x83 - x86;
  double x88 = -0.54191999999999996*x53 + 0.54191999999999996*x80;
  double x89 = x30*x46 + x36*x46;
  double x90 = x48*x75;
  double x91 = x90*(x45 + x89);
  double x92 = 1.9252800000000001*x2;
  double x93 = x50*x68 + x51*x66 + x65;
  double x94 = 0.58272000000000002*x50;
  double x95 = x12*x79 + x13*x84;
  double x96 = x39*x52;
  double x97 = -x11*(-x14*x78 + x4*x86) + 4*x13*x8*x81;
  double x98 = x17*x78 + x4*x82;
  double x99 = 0.54191999999999996*x58 + 0.54191999999999996*x77;
  double x100 = x56*x67;
  double x101 = x100 - x11*x63;
  double x102 = x14*x62 + x72;
  double x103 = 0.54191999999999996*x57 + 0.54191999999999996*x59;
  double x104 = -x14*x68 + x17*x66;
  double x105 = -x100 + x11*x63;
  double x106 = x102*x17 - x105*x14;
  double x107 = -x14*x85 + x17*x87;
  double x108 = x89*x90;
  double x109 = x47*x77 + x70;
  double x110 = x47*x54 - x96;
  double x111 = x108*x66;
  double x112 = x102*x110;
  double x113 = x109*x87;
  double x114 = pow(x66, 2);
  double x115 = pow(x102, 2);
  double x116 = pow(x87, 2);
  double x117 = x22*x66;
  double x118 = x66*x68;
  double x119 = x102*x64;
  double x120 = x102*x105;
  double x121 = x87*x95;
  double x122 = x85*x87;
  double x123 = x108*x22;
  double x124 = x109*x95;
  double x125 = x110*x64;
  double x126 = x108*x68;
  double x127 = x109*x85;
  double x128 = x105*x110;
  double x129 = cq[2];
  double x130 = x129*x14;
  double x131 = sq[2];
  double x132 = 4*x131;
  double x133 = x129*x17;
  double x134 = x130*x66 + x132*x22 + x133*x68;
  double x135 = x102*x130 + x105*x133 + x132*x64;
  double x136 = x130*x87 + x132*x95 + x133*x85;
  double x137 = x131*x14;
  double x138 = 4*x129;
  double x139 = -x131*x17*x68 - x137*x66 + x138*x22;
  double x140 = x102*x137 + x105*x131*x17 - x138*x64;
  double x141 = -x131*x17*x85 - x137*x87 + x138*x95;
  *val = 0.015041250000000001*x2*x22*(x40*(-x2*x28 + x24 + x25*x27) + x49*(x2*x44 + x25*x43 + x41)) + 0.0045525000000000001*x22*x50*(x40*(x24 + x27*x51 - x28*x50) + x49*(x41 + x43*x51 + x44*x50)) - 1.0/128.0*x64*x92*(-x69*x70 + x76*(-x2*x73 + x25*x71 + x74) + x91*(x2*x85 + x25*x87 + x88)) - 1.0/128.0*x64*x94*(-x70*x93 + x76*(-x50*x73 + x51*x71 + x74) + x91*(x50*x85 + x51*x87 + x88)) - 1.0/128.0*x92*x95*(x69*x96 - x76*(x2*x97 - x25*x98 + x99) + x91*(x101*x2 - x102*x25 + x103)) - 1.0/128.0*x94*x95*(-x76*(x50*x97 - x51*x98 + x99) + x91*(x101*x50 - x102*x51 + x103) + x93*x96) - 1.0/32.0*(x111 - x112 + x113)*(3.9389987500000003e-5*x114 + 3.9389987500000003e-5*x115 + 3.9389987500000003e-5*x116 + 1.7000000000000003e-10*x117 - 1.22701775e-5*x118 + 1.7000000000000003e-10*x119 - 1.22701775e-5*x120 + 1.7000000000000003e-10*x121 - 1.22701775e-5*x122) - 1.0/128.0*(x114 + x115 + x116)*(0.00015755995000000001*x111 - 0.00015755995000000001*x112 + 0.00015755995000000001*x113 + 6.8000000000000013e-10*x123 + 6.8000000000000013e-10*x124 - 6.8000000000000013e-10*x125 - 4.908071e-5*x126 - 4.908071e-5*x127 + 4.908071e-5*x128) - 1.0/128.0*(x117 + x119 + x121)*(6.8000000000000013e-10*x111 - 6.8000000000000013e-10*x112 + 6.8000000000000013e-10*x113 + 0.00054005738000000004*x123 + 0.00054005738000000004*x124 - 0.00054005738000000004*x125 + 2.3100000000000001e-9*x126 + 2.3100000000000001e-9*x127 - 2.3100000000000001e-9*x128) - 1.0/128.0*(x118 + x120 + x122)*(-4.908071e-5*x111 + 4.908071e-5*x112 - 4.908071e-5*x113 + 2.3100000000000001e-9*x123 + 2.3100000000000001e-9*x124 - 2.3100000000000001e-9*x125 + 0.00050018127000000005*x126 + 0.00050018127000000005*x127 - 0.00050018127000000005*x128) - 1.0/32.0*(x123 + x124 - x125)*(1.7000000000000003e-10*x114 + 1.7000000000000003e-10*x115 + 1.7000000000000003e-10*x116 + 0.00013501434500000001*x117 + 5.7750000000000002e-10*x118 + 0.00013501434500000001*x119 + 5.7750000000000002e-10*x120 + 0.00013501434500000001*x121 + 5.7750000000000002e-10*x122) - 1.0/32.0*(x126 + x127 - x128)*(-1.22701775e-5*x114 - 1.22701775e-5*x115 - 1.22701775e-5*x116 + 5.7750000000000002e-10*x117 + 0.00012504531750000001*x118 + 5.7750000000000002e-10*x119 + 0.00012504531750000001*x120 + 5.7750000000000002e-10*x121 + 0.00012504531750000001*x122) + 5.1988466796875003e-8*(x102*x106 + x104*x66 + x107*x87)*(-x104*x108 + x106*x110 - x107*x109) - 2.8224560546875002e-8*(x102*x135 + x134*x66 + x136*x87)*(x108*x134 + x109*x136 - x110*x135) - 2.8224560546875002e-8*(x102*x140 - x139*x66 - x141*x87)*(-x108*x139 - x109*x141 - x110*x140);
}
