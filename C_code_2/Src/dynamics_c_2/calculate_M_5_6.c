

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_5_6(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
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
  double x10 = sq[0];
  double x11 = 0.02554*x10;
  double x12 = x5*x8;
  double x13 = x6*x9;
  double x14 = x0*x8;
  double x15 = x14*x2;
  double x16 = x13 + x15;
  double x17 = x13*x2;
  double x18 = x14 + x17;
  double x19 = x2*(x1 + x7 - 1);
  double x20 = x0*x9;
  double x21 = x6*x8;
  double x22 = x2*x21;
  double x23 = x20 - x22;
  double x24 = x2*x20;
  double x25 = -x21 + x24;
  double x26 = 0.088220000000000007*x20;
  double x27 = cq[0];
  double x28 = x0*x4;
  double x29 = x27*x28;
  double x30 = x10*x16;
  double x31 = x4*x6;
  double x32 = x27*x31;
  double x33 = x10*x23;
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
  double x50 = x18*x38;
  double x51 = -x18*x45 + x46*(x10*x50 + x23*x39);
  double x52 = -x10*x18*x39 + x23*x38;
  double x53 = x25*x39;
  double x54 = -x29 + x30;
  double x55 = -x44*(x10*x28 + x16*x27) + x46*(x38*x54 + x53);
  double x56 = x25*x38;
  double x57 = x39*x54 - x56;
  double x58 = -0.54191999999999996*x21 + 0.54191999999999996*x24;
  double x59 = 0.54191999999999996*x20 - 0.54191999999999996*x22;
  double x60 = 4*x25*x27*x43 - x46*(x10*x56 - x16*x39);
  double x61 = x10*x53 + x16*x38;
  double x62 = x32 + x33;
  double x63 = x44*(-x10*x31 + x23*x27) + x46*(x18*x39 - x38*x62);
  double x64 = x39*x62 + x50;
  double x65 = 0.54191999999999996*x14 + 0.54191999999999996*x17;
  double x66 = 0.54191999999999996*x13 + 0.54191999999999996*x15;
  *val = (-0.25728000000000001*x12*(x11*x9 + 0.088220000000000007*x8) - 0.060165000000000003*x12*(-x34 - x37*x41 - x42*x47) - 0.01821*x12*(-x34 - x41*x48 - x47*x49) + 0.052914523900000003*x16*(x16 + x18*x19) - 0.25728000000000001*x16*(x11*x25 + 0.088220000000000007*x13 + 0.088220000000000007*x15 + x19*(0.088220000000000007*x14 + 0.088220000000000007*x17 + 0.02554*x32 + 0.02554*x33)) - 0.060165000000000003*x16*(x19*(-x37*x64 + x42*x63 + x65) - x37*x61 + x42*x60 + x66) - 0.01821*x16*(x19*(-x48*x64 + x49*x63 + x65) - x48*x61 + x49*x60 + x66) + 0.052914523900000003*x23*(x19*x25 + x23) + 0.25728000000000001*x23*(x11*x18 + x19*(-x2*x26 + 0.088220000000000007*x21 - 0.02554*x29 + 0.02554*x30) + 0.088220000000000007*x22 - x26) - 0.060165000000000003*x23*(x19*(x37*x57 + x42*x55 + x58) - x37*x52 + x42*x51 + x59) - 0.01821*x23*(x19*(x48*x57 + x49*x55 + x58) - x48*x52 + x49*x51 + x59) + 0.052914523900000003*x5*pow(x8, 2))/(x1*x3 + x1*x5 + x3*x7 + x5*x7);
}
