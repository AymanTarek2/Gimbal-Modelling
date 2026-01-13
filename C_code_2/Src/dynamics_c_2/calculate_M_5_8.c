

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_5_8(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = cbo[1];
  double x1 = sbo[0];
  double x2 = pow(x1, 2);
  double x3 = sbo[1];
  double x4 = pow(x3, 2);
  double x5 = pow(x0, 2);
  double x6 = cbo[0];
  double x7 = pow(x6, 2);
  double x8 = cbo[2];
  double x9 = sbo[2];
  double x10 = sq[0];
  double x11 = 0.02554*x10;
  double x12 = x1*x8;
  double x13 = x6*x9;
  double x14 = x13*x3;
  double x15 = x12 + x14;
  double x16 = x3*(x2 + x7 - 1);
  double x17 = x12*x3;
  double x18 = x13 + x17;
  double x19 = x6*x8;
  double x20 = x1*x9;
  double x21 = x20*x3;
  double x22 = -x19 + x21;
  double x23 = x19*x3;
  double x24 = x20 - x23;
  double x25 = 0.088220000000000007*x20;
  double x26 = 0.088220000000000007*x19;
  double x27 = cq[0];
  double x28 = x0*x1;
  double x29 = x27*x28;
  double x30 = x10*x18;
  double x31 = x0*x6;
  double x32 = x27*x31;
  double x33 = x10*x24;
  double x34 = -0.54191999999999996*x8;
  double x35 = M_SQRT2;
  double x36 = sqrt(6);
  double x37 = 0.016767499999999998*x35 + 0.016512499999999999*x36;
  double x38 = x35 - x36;
  double x39 = x35 + x36;
  double x40 = x10*x9;
  double x41 = x38*x8 + x39*x40;
  double x42 = 0.016512499999999999*x35 - 0.016767499999999998*x36;
  double x43 = sq[1];
  double x44 = 4*x43;
  double x45 = x27*x44;
  double x46 = cq[1];
  double x47 = -x45*x9 + x46*(x38*x40 - x39*x8);
  double x48 = 0.013937500000000002*x35 + 0.032607499999999998*x36;
  double x49 = 0.032607499999999998*x35 - 0.013937500000000002*x36;
  double x50 = x15*x38;
  double x51 = -x15*x45 + x46*(x10*x50 + x24*x39);
  double x52 = -x10*x15*x39 + x24*x38;
  double x53 = x22*x39;
  double x54 = -x29 + x30;
  double x55 = -x44*(x10*x28 + x18*x27) + x46*(x38*x54 + x53);
  double x56 = x22*x38;
  double x57 = x39*x54 - x56;
  double x58 = -0.54191999999999996*x19 + 0.54191999999999996*x21;
  double x59 = 0.54191999999999996*x20 - 0.54191999999999996*x23;
  double x60 = 4*x22*x27*x43 - x46*(x10*x56 - x18*x39);
  double x61 = x10*x53 + x18*x38;
  double x62 = x32 + x33;
  double x63 = x44*(-x10*x31 + x24*x27) + x46*(x15*x39 - x38*x62);
  double x64 = x39*x62 + x50;
  double x65 = 0.54191999999999996*x12 + 0.54191999999999996*x14;
  double x66 = 0.54191999999999996*x13 + 0.54191999999999996*x17;
  *val = x0*(-0.052914523900000003*x1*(x15*x16 + x18) + 0.25728000000000001*x1*(x11*x22 + 0.088220000000000007*x13 + x16*(0.088220000000000007*x12 + 0.088220000000000007*x14 + 0.02554*x32 + 0.02554*x33) + 0.088220000000000007*x17) + 0.060165000000000003*x1*(x16*(-x37*x64 + x42*x63 + x65) - x37*x61 + x42*x60 + x66) + 0.01821*x1*(x16*(-x48*x64 + x49*x63 + x65) - x48*x61 + x49*x60 + x66) + 0.052914523900000003*x3*x8 - 0.25728000000000001*x3*(x11*x9 + 0.088220000000000007*x8) - 0.060165000000000003*x3*(-x34 - x37*x41 - x42*x47) - 0.01821*x3*(-x34 - x41*x48 - x47*x49) + 0.052914523900000003*x6*(x16*x22 + x24) + 0.25728000000000001*x6*(x11*x15 + x16*(-x25*x3 + x26 - 0.02554*x29 + 0.02554*x30) - x25 + x26*x3) - 0.060165000000000003*x6*(x16*(x37*x57 + x42*x55 + x58) - x37*x52 + x42*x51 + x59) - 0.01821*x6*(x16*(x48*x57 + x49*x55 + x58) - x48*x52 + x49*x51 + x59))/(x2*x4 + x2*x5 + x4*x7 + x5*x7);
}
