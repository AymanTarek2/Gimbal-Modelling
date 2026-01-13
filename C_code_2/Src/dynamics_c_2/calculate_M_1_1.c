

#define _USE_MATH_DEFINES

#include <math.h>

#include "model.h"



#ifndef M_SQRT2

#define M_SQRT2 1.41421356237309504880

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846

#endif


void calculate_M_1_1(const double sq[3], const double cq[3], const double sbo[3], const double cbo[3], double *val) {
  double x0 = sbo[1];
  double x1 = sq[0];
  double x2 = cq[0];
  double x3 = cbo[2];
  double x4 = cbo[1];
  double x5 = x3*x4;
  double x6 = x0*x1 - x2*x5;
  double x7 = cq[1];
  double x8 = 4*x7;
  double x9 = sq[1];
  double x10 = M_SQRT2;
  double x11 = sqrt(6);
  double x12 = x10 + x11;
  double x13 = sbo[2];
  double x14 = x13*x4;
  double x15 = x10 - x11;
  double x16 = x0*x2 + x1*x5;
  double x17 = x12*x14 + x15*x16;
  double x18 = x17*x9 - x6*x8;
  double x19 = pow(x18, 2);
  double x20 = 0.00027064532750849994*pow(0.98479200834948566*x10 - x11, 2);
  double x21 = 0.00030978824502899999*pow(x10 - 0.42743233918577023*x11, 2);
  double x22 = sbo[0];
  double x23 = x22*x4;
  double x24 = cbo[0];
  double x25 = x13*x24;
  double x26 = x22*x3;
  double x27 = x0*x26 + x25;
  double x28 = x1*x23 + x2*x27;
  double x29 = x24*x3;
  double x30 = x13*x22;
  double x31 = x0*x30 - x29;
  double x32 = x1*x27 - x2*x23;
  double x33 = x12*x31 + x15*x32;
  double x34 = x28*x8 + x33*x9;
  double x35 = pow(x34, 2);
  double x36 = x24*x4;
  double x37 = -x0*x29 + x30;
  double x38 = -x1*x36 + x2*x37;
  double x39 = x0*x25 + x26;
  double x40 = x1*x37 + x2*x36;
  double x41 = -x12*x39 + x15*x40;
  double x42 = x38*x8 + x41*x9;
  double x43 = pow(x42, 2);
  double x44 = x12*x16 - x14*x15;
  double x45 = 4*x9;
  double x46 = x17*x7 + x45*x6;
  double x47 = x12*x40 + x15*x39;
  double x48 = -x38*x45 + x41*x7;
  double x49 = x12*x32 - x15*x31;
  double x50 = -x28*x45 + x33*x7;
  double x51 = cq[2];
  double x52 = x12*x51;
  double x53 = sq[2];
  double x54 = 4*x53;
  double x55 = x15*x51;
  double x56 = x12*x53;
  double x57 = 4*x51;
  double x58 = pow(x44, 2);
  double x59 = pow(x47, 2);
  double x60 = pow(x49, 2);
  double x61 = x18*x44;
  double x62 = x44*x46;
  double x63 = x42*x47;
  double x64 = x47*x48;
  double x65 = x34*x49;
  double x66 = x49*x50;
  *val = (1.0/64.0)*x19*x20 + (1.0/64.0)*x19*x21 + (1.0/64.0)*x20*x35 + (1.0/64.0)*x20*x43 + (1.0/64.0)*x21*x35 + (1.0/64.0)*x21*x43 + (1.0/64.0)*(x58 + x59 + x60)*(3.9389987500000003e-5*x58 + 3.9389987500000003e-5*x59 + 3.9389987500000003e-5*x60 + 1.7000000000000003e-10*x61 - 1.22701775e-5*x62 + 1.7000000000000003e-10*x63 - 1.22701775e-5*x64 + 1.7000000000000003e-10*x65 - 1.22701775e-5*x66) + (1.0/64.0)*(x61 + x63 + x65)*(1.7000000000000003e-10*x58 + 1.7000000000000003e-10*x59 + 1.7000000000000003e-10*x60 + 0.00013501434500000001*x61 + 5.7750000000000002e-10*x62 + 0.00013501434500000001*x63 + 5.7750000000000002e-10*x64 + 0.00013501434500000001*x65 + 5.7750000000000002e-10*x66) + (1.0/64.0)*(x62 + x64 + x66)*(-1.22701775e-5*x58 - 1.22701775e-5*x59 - 1.22701775e-5*x60 + 5.7750000000000002e-10*x61 + 0.00012504531750000001*x62 + 5.7750000000000002e-10*x63 + 0.00012504531750000001*x64 + 5.7750000000000002e-10*x65 + 0.00012504531750000001*x66) + 1.2997116699218751e-8*pow(x44*(-x12*x46 + x15*x44) + x47*(-x12*x48 + x15*x47) + x49*(-x12*x50 + x15*x49), 2) + 7.0561401367187505e-9*pow(x44*(x18*x54 + x44*x52 + x46*x55) + x47*(x42*x54 + x47*x52 + x48*x55) + x49*(x34*x54 + x49*x52 + x50*x55), 2) + 7.0561401367187505e-9*pow(x44*(x15*x46*x53 - x18*x57 + x44*x56) + x47*(x15*x48*x53 - x42*x57 + x47*x56) + x49*(x15*x50*x53 - x34*x57 + x49*x56), 2);
}
