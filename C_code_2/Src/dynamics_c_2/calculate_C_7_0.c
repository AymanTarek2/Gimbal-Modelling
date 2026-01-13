

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_C_7_0(const double dq[3], const double base_dori[3], const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[2];
  double x1 = cbo[1];
  double x2 = sbo[1];
  double x3 = cq[0];
  double x4 = x2*x3;
  double x5 = cbo[2];
  double x6 = sq[0];
  double x7 = x1*x6;
  double x8 = x4 + x5*x7;
  double x9 = cbo[0];
  double x10 = x5*x9;
  double x11 = sbo[0];
  double x12 = x0*x11;
  double x13 = -x10 + x12*x2;
  double x14 = x0*x9;
  double x15 = x11*x5;
  double x16 = x14 + x15*x2;
  double x17 = -x1*x11*x3 + x16*x6;
  double x18 = -x17;
  double x19 = x14*x2 + x15;
  double x20 = x1*x3;
  double x21 = x20*x9;
  double x22 = -x10*x2 + x12;
  double x23 = x21 + x22*x6;
  double x24 = -x23;
  double x25 = M_SQRT2;
  double x26 = sqrt(6);
  double x27 = 0.016767499999999998*x25 + 0.016512499999999999*x26;
  double x28 = x25 + x26;
  double x29 = x28*x8;
  double x30 = 0.016512499999999999*x25 - 0.016767499999999998*x26;
  double x31 = x2*x6;
  double x32 = -x1*x3*x5 + x31;
  double x33 = -x32;
  double x34 = sq[1];
  double x35 = 4*x34;
  double x36 = cq[1];
  double x37 = x25 - x26;
  double x38 = -x33*x35 + x36*x37*x8;
  double x39 = x0*x1;
  double x40 = 0.013937500000000002*x25 + 0.032607499999999998*x26;
  double x41 = 0.032607499999999998*x25 - 0.013937500000000002*x26;
  double x42 = x18*x28;
  double x43 = x11*x7;
  double x44 = x16*x3;
  double x45 = x43 + x44;
  double x46 = x36*x37;
  double x47 = x18*x46 + x35*x45;
  double x48 = x24*x28;
  double x49 = x7*x9;
  double x50 = x22*x3;
  double x51 = -x49 + x50;
  double x52 = x24*x46 + x35*x51;
  double x53 = 0.01821*x19;
  double x54 = 0.060165000000000003*x19;
  double x55 = 4*x36;
  double x56 = x55*x8;
  double x57 = x34*x37;
  double x58 = x33*x57 - x56;
  double x59 = 0.030082500000000002*x39;
  double x60 = x30*x59;
  double x61 = 0.0091050000000000002*x39;
  double x62 = x41*x61;
  double x63 = -x32*x57 - x56;
  double x64 = x45*x57;
  double x65 = x18*x55 + x64;
  double x66 = 0.030082500000000002*x13;
  double x67 = 0.0091050000000000002*x13;
  double x68 = x17*x55 - x64;
  double x69 = x51*x57;
  double x70 = x23*x55 - x69;
  double x71 = 0.030082500000000002*x19;
  double x72 = 0.0091050000000000002*x19;
  double x73 = x24*x55 + x69;
  double x74 = pow(x0, 2);
  double x75 = pow(x1, 2);
  double x76 = 0.0032854656000000002*x13;
  double x77 = -x13;
  double x78 = x3*x77;
  double x79 = 0.0032854656000000002*x45;
  double x80 = -x22;
  double x81 = x27*x28;
  double x82 = x0*x20;
  double x83 = x0*x35*x7 + x46*x82;
  double x84 = x28*x40;
  double x85 = x35*x8;
  double x86 = x32*x46 - x85;
  double x87 = 0.0091050000000000002*x32*x84 + 0.0091050000000000002*x41*x86;
  double x88 = x1*x5;
  double x89 = 0.030082500000000002*x30*x86 + 0.030082500000000002*x32*x81;
  double x90 = x19*x3;
  double x91 = x35*x6;
  double x92 = x19*x91 + x46*x90;
  double x93 = x41*x92 + x84*x90;
  double x94 = x30*x92 + x81*x90;
  double x95 = x46*x78 + x77*x91;
  double x96 = x45*x81;
  double x97 = x17*x35 + x45*x46;
  double x98 = x30*x97 + x96;
  double x99 = x45*x84;
  double x100 = x41*x97 + x99;
  double x101 = x51*x81;
  double x102 = x46*x51;
  double x103 = x102 + x23*x35;
  double x104 = 0.030082500000000002*x101 + 0.030082500000000002*x103*x30;
  double x105 = x51*x84;
  double x106 = 0.0091050000000000002*x103*x41 + 0.0091050000000000002*x105;
  double x107 = pow(x2, 2);
  double x108 = pow(x9, 2);
  double x109 = pow(x11, 2);
  double x110 = x108*x75 + x109*x75;
  double x111 = x0*x3;
  double x112 = x111*x81;
  double x113 = x0*x91 + x111*x46;
  double x114 = -x112 - x113*x30;
  double x115 = x0*x75;
  double x116 = x111*x84;
  double x117 = -x113*x41 - x116;
  double x118 = 0.02554*x3;
  double x119 = 0.02554*x43 + 0.02554*x44;
  double x120 = x2*(x108 + x109 - 1);
  double x121 = -0.02554*x49 + 0.02554*x50;
  double x122 = -x18*x35 + x36*x37*x45;
  double x123 = x122*x30 + x96;
  double x124 = x122*x41 + x99;
  double x125 = -x101;
  double x126 = -x103;
  double x127 = x125 + x126*x30;
  double x128 = x13*x3;
  double x129 = -x128*x46 - x13*x91;
  double x130 = -x128*x81 + x129*x30;
  double x131 = -x105;
  double x132 = x126*x41 + x131;
  double x133 = -x128*x84 + x129*x41;
  double x134 = x3*x80 + x49;
  double x135 = x134*x46 + x35*(-x21 + x6*x80);
  double x136 = x4*x5;
  double x137 = 0.02554*x136;
  double x138 = -x137 - 0.02554*x7;
  double x139 = x109*x74;
  double x140 = pow(x5, 2);
  double x141 = x109*x140;
  double x142 = x108*x74;
  double x143 = x108*x140;
  double x144 = 1.0/(x139 + x141 + x142 + x143);
  double x145 = x0*x144;
  double x146 = 1.0/(x107*x139 + x107*x141 + x107*x142 + x107*x143 + x139*x75 + x141*x75 + x142*x75 + x143*x75);
  double x147 = 0.12864*x39;
  double x148 = x136 + x7;
  double x149 = -x148*x46 + x35*(x1*x3 - x31*x5);
  double x150 = -x113;
  double x151 = x146*x2;
  double x152 = x151*x5;
  double x153 = 0.02554*x1*x3*x5 - 0.02554*x31;
  double x154 = x14*x144;
  double x155 = 1.0/x1;
  double x156 = x146*x155;
  double x157 = x137*x156;
  double x158 = x156*(x107 + x110);
  double x159 = x158*x5;
  double x160 = 0.12864*x19;
  double x161 = x12*x144;
  double x162 = 0.12864*x13;
  double x163 = x33*x46 + x85;
  double x164 = x163*x30 + x33*x81;
  double x165 = -x94;
  double x166 = x152*x155;
  double x167 = x163*x41 + x33*x84;
  double x168 = -x93;
  double x169 = -x102 + x24*x35;
  double x170 = x0*x2;
  double x171 = x1*x12;
  double x172 = -x10*x20 + x31*x9;
  double x173 = x1*x11*x3*x5 - x11*x31;
  double x174 = x1*x14;
  double x175 = -x149;
  double x176 = x148*x81 + x175*x30;
  double x177 = x148*x84 + x175*x41;
  double x178 = x173*x46 + x35*(x11*x4 + x15*x7);
  double x179 = x172*x46 + x35*(-x10*x7 - x4*x9);
  double x180 = x144*x5;
  double x181 = x0*x151;
  double x182 = x144*x153;
  double x183 = 0.02554*x0*x156*x4;
  double x184 = x0*x158;
  double x185 = x144*x164;
  double x186 = x155*x181;
  double x187 = x144*x167;
  *val = dq[0]*(0.0065709312000000004*x0*x1*x8 - 0.0065709312000000004*x13*x18 + 0.060165000000000003*x13*(x27*x42 + x30*x47) + 0.01821*x13*(x40*x42 + x41*x47) + 0.0065709312000000004*x19*x24 - 0.060165000000000003*x39*(x27*x29 + x30*x38) - 0.01821*x39*(x29*x40 + x38*x41) - x53*(x40*x48 + x41*x52) - x54*(x27*x48 + x30*x52)) + dq[1]*(0.030082500000000002*x13*x30*x68 + 0.0091050000000000002*x13*x41*x68 + 0.030082500000000002*x19*x30*x73 + 0.0091050000000000002*x19*x41*x73 - x30*x65*x66 - x30*x70*x71 - x41*x65*x67 - x41*x70*x72 - x58*x60 - x58*x62 - x60*x63 - x62*x63) + base_dori[0]*(-x104*x77 - x106*x77 + 0.030082500000000002*x13*(x134*x81 + x135*x30) + 0.0091050000000000002*x13*(x134*x84 + x135*x41) + 0.030082500000000002*x13*(-x130*x166 + x159*(x125 + x169*x30) + x161*x164) + 0.0091050000000000002*x13*(-x133*x166 + x159*(x131 + x169*x41) + x161*x167) - x134*x76 - x147*(x0*x137*x146 + x138*x145) - x160*(-x119*x159 + x153*x154 + x157*x19) - x162*(-x121*x159 + x13*x157 + x153*x161) + 0.0032854656000000002*x51*x77 - x59*(x145*(x148*x27*x28 - x149*x30) + x152*(-x112 + x150*x30)) - x61*(x145*(x148*x28*x40 - x149*x41) + x152*(-x116 + x150*x41)) - x71*(x123*x159 - x154*x164 + x165*x166) - x72*(x124*x159 - x154*x167 + x166*x168)) + base_dori[1]*(0.0091050000000000002*x100*x171 - x104*x174 - x106*x174 + x147*(-x138*x180 + 0.02554*x146*x2*x3*x74) + 0.0032854656000000002*x148*x39 - x160*(x10*x182 + x119*x184 - x183*x19) - x162*(x121*x184 - x13*x183 + x15*x182) - 0.0032854656000000002*x170*x32 + x170*x87 + x170*x89 - x171*x79 + 0.030082500000000002*x171*x98 + 0.0032854656000000002*x172*x19 - x173*x76 + 0.0032854656000000002*x174*x51 - x176*x59 - x177*x61 - x59*(-x114*x181 + x176*x180) - x61*(-x117*x181 + x177*x180) + x66*(x173*x81 + x178*x30) + x66*(-x127*x184 + x130*x186 + x15*x185) + x67*(x173*x84 + x178*x41) + x67*(-x132*x184 + x133*x186 + x15*x187) - x71*(x172*x81 + x179*x30) + x71*(x10*x185 + x123*x184 + x165*x186) - x72*(x172*x84 + x179*x41) + x72*(x10*x187 + x124*x184 + x168*x186)) + base_dori[2]*(0.0032854656000000002*x1*x32*x5 + 0.0091050000000000002*x100*x16 - x104*x80 - x106*x80 + 0.030082500000000002*x13*(x30*x95 + x78*x81) + 0.0091050000000000002*x13*(x41*x95 + x78*x84) - x16*x79 + 0.030082500000000002*x16*x98 + 0.0032854656000000002*pow(x19, 2)*x3 + 0.0032854656000000002*x3*x74*x75 + 0.0032854656000000002*x51*x80 - x59*(x30*x83 + x81*x82) - x61*(x41*x83 + x82*x84) - x71*x94 - x72*x93 - x76*x78 - x87*x88 - x88*x89 + (1.0/2.0)*(0.060165000000000003*x114*x115 + 0.01821*x115*x117 + 0.25728000000000001*x13*(x118*x13 + x120*x121) + 0.060165000000000003*x13*(x120*x127 + x130) + 0.01821*x13*(x120*x132 + x133) + 0.25728000000000001*x19*(x118*x19 + x119*x120) + 0.0065709312000000004*x3*x74*x75 + x53*(-x120*x124 - x93) + x54*(-x120*x123 - x94))/(x107*x108 + x107*x109 + x110));
}
