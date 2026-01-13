

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_7_5(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[0];
  double x1 = pow(x0, 2);
  double x2 = sbo[1];
  double x3 = pow(x2, 2);
  double x4 = cbo[1];
  double x5 = pow(x4, 2);
  double x6 = cbo[0];
  double x7 = pow(x6, 2);
  double x8 = cbo[2];
  double x9 = sbo[2];
  double x10 = x5*x9;
  double x11 = sq[0];
  double x12 = 0.02554*x11;
  double x13 = x6*x8;
  double x14 = x0*x9;
  double x15 = x14*x2;
  double x16 = -x13 + x15;
  double x17 = x0*x8;
  double x18 = x6*x9;
  double x19 = x18*x2;
  double x20 = x17 + x19;
  double x21 = x2*(x1 + x7 - 1);
  double x22 = x17*x2;
  double x23 = x18 + x22;
  double x24 = -x13*x2 + x14;
  double x25 = 0.088220000000000007*x14;
  double x26 = 0.088220000000000007*x13;
  double x27 = cq[0];
  double x28 = x0*x4;
  double x29 = x27*x28;
  double x30 = x11*x23;
  double x31 = x27*x4*x6;
  double x32 = x11*x24;
  double x33 = -0.54191999999999996*x8;
  double x34 = M_SQRT2;
  double x35 = sqrt(6);
  double x36 = 0.016767499999999998*x34 + 0.016512499999999999*x35;
  double x37 = x34 - x35;
  double x38 = x34 + x35;
  double x39 = x11*x9;
  double x40 = x37*x8 + x38*x39;
  double x41 = 0.016512499999999999*x34 - 0.016767499999999998*x35;
  double x42 = 4*sq[1];
  double x43 = x27*x42;
  double x44 = cq[1];
  double x45 = -x43*x9 + x44*(x37*x39 - x38*x8);
  double x46 = 0.013937500000000002*x34 + 0.032607499999999998*x35;
  double x47 = 0.032607499999999998*x34 - 0.013937500000000002*x35;
  double x48 = x20*x37;
  double x49 = -x20*x43 + x44*(x11*x48 + x24*x38);
  double x50 = -x11*x20*x38 + x24*x37;
  double x51 = x16*x38;
  double x52 = -x29 + x30;
  double x53 = -x42*(x11*x28 + x23*x27) + x44*(x37*x52 + x51);
  double x54 = x16*x37;
  double x55 = x38*x52 - x54;
  double x56 = -0.54191999999999996*x13 + 0.54191999999999996*x15;
  double x57 = 0.54191999999999996*x14 - 0.54191999999999996*x2*x6*x8;
  double x58 = x16*x43 + x44*(-x11*x54 + x23*x38);
  double x59 = x11*x51 + x23*x37;
  double x60 = x31 + x32;
  double x61 = -x42*(x11*x4*x6 - x24*x27) + x44*(x20*x38 - x37*x60);
  double x62 = x38*x60 + x48;
  double x63 = 0.54191999999999996*x17 + 0.54191999999999996*x19;
  double x64 = 0.54191999999999996*x18 + 0.54191999999999996*x22;
  *val = (-0.052914523900000003*x10*x8 + 0.25728000000000001*x10*(x12*x9 + 0.088220000000000007*x8) + 0.060165000000000003*x10*(-x33 - x36*x40 - x41*x45) + 0.01821*x10*(-x33 - x40*x46 - x45*x47) - 0.052914523900000003*x16*(x20*x21 + x23) + 0.25728000000000001*x16*(x12*x16 + 0.088220000000000007*x18 + x21*(0.088220000000000007*x17 + 0.088220000000000007*x19 + 0.02554*x31 + 0.02554*x32) + 0.088220000000000007*x22) + 0.060165000000000003*x16*(x21*(-x36*x62 + x41*x61 + x63) - x36*x59 + x41*x58 + x64) + 0.01821*x16*(x21*(-x46*x62 + x47*x61 + x63) - x46*x59 + x47*x58 + x64) + 0.052914523900000003*x20*(x16*x21 + x24) + 0.25728000000000001*x20*(x12*x20 + x2*x26 + x21*(-x2*x25 + x26 - 0.02554*x29 + 0.02554*x30) - x25) + 0.060165000000000003*x20*(-x21*(x36*x55 + x41*x53 + x56) + x36*x50 - x41*x49 - x57) + 0.01821*x20*(-x21*(x46*x55 + x47*x53 + x56) + x46*x50 - x47*x49 - x57))/(x1*x3 + x1*x5 + x3*x7 + x5*x7);
}
