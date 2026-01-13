#include <math.h>
#include "../params.h"
void calculate_G_3(const double q[9], const double dq[9], double *val) {
  double q_0 = q[0]; double dq_0 = dq[0];
  double q_1 = q[1]; double dq_1 = dq[1];
  double q_2 = q[2]; double dq_2 = dq[2];
  double q_3 = q[3]; double dq_3 = dq[3];
  double q_4 = q[4]; double dq_4 = dq[4];
  double q_5 = q[5]; double dq_5 = dq[5];
  double q_6 = q[6]; double dq_6 = dq[6];
  double q_7 = q[7]; double dq_7 = dq[7];
  double q_8 = q[8]; double dq_8 = dq[8];
  double x0 = sin(q_3);
  double x1 = sin(q_5);
  double x2 = x0*x1;
  double x3 = cos(q_3);
  double x4 = cos(q_4);
  double x5 = x3*x4;
  double x6 = sin(q_4);
  double x7 = cos(q_5);
  double x8 = 2*g;
  double x9 = x0*x7;
  double x10 = sin(q_0);
  double x11 = -x2 + x3*x6*x7;
  double x12 = cos(q_0);
  double x13 = x12*x5;
  double x14 = x1*x3*x6;
  double x15 = 6.0000000000001025e-5*x2 - 6.0000000000001025e-5*x3*x6*x7;
  double x16 = x10*x11;
  double x17 = x10*x5 + x11*x12;
  double x18 = sin(q_1);
  double x19 = x17*x18;
  double x20 = cos(q_1);
  double x21 = 0.2582889370066549*x10*x11 - 0.2582889370066549*x13 - 0.96606771244047496*x14 - 0.96606771244047496*x9;
  double x22 = x20*x21;
  *val = m_base_link*x8*(-3.4694469519536142e-18*x2 + 3.4694469519536142e-18*x3*x6*x7 - 1.3877787807814457e-17*x5) + m_end_effector*x8*(0.037943975293278594*x12*x3*x4 - 0.20028474339438354*x14 - x15 - 0.037943975293278594*x16 - 0.089852554946397045*x19 - 0.089852554946397045*x22 - 0.20028474339438354*x9 - 3.4694469519536142e-18*(x17*x20 - x18*x21)*cos(q_2) + 3.4694469519536142e-18*(-0.93328682501997218*x13 + 0.24952460252270103*x14 + 0.93328682501997218*x16 + 0.2582889370066549*x19 + 0.2582889370066549*x22 + 0.24952460252270103*x9)*sin(q_2)) + m_link_2*x8*(0.025549999999999989*x10*x11 - 0.025549999999999989*x13 - 0.14288000000000001*x14 - x15 - 0.14288000000000001*x9) + m_link_3*x8*(0.001643433328076236*x12*x3*x4 - 0.19057939016063152*x14 - x15 - 0.001643433328076236*x16 - 0.063689999999999997*x19 - 0.063689999999999997*x22 - 0.19057939016063152*x9);
}
