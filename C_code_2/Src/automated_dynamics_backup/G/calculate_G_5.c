#include <math.h>
#include "../params.h"
void calculate_G_5(const double q[9], const double dq[9], double *val) {
  double q_0 = q[0]; double dq_0 = dq[0];
  double q_1 = q[1]; double dq_1 = dq[1];
  double q_2 = q[2]; double dq_2 = dq[2];
  double q_3 = q[3]; double dq_3 = dq[3];
  double q_4 = q[4]; double dq_4 = dq[4];
  double q_5 = q[5]; double dq_5 = dq[5];
  double q_6 = q[6]; double dq_6 = dq[6];
  double q_7 = q[7]; double dq_7 = dq[7];
  double q_8 = q[8]; double dq_8 = dq[8];
  double x0 = cos(q_3);
  double x1 = cos(q_5);
  double x2 = sin(q_5);
  double x3 = sin(q_3)*sin(q_4);
  double x4 = x2*x3;
  double x5 = 2*g;
  double x6 = x0*x2;
  double x7 = sin(q_0);
  double x8 = x0*x1 - x4;
  double x9 = x1*x3;
  double x10 = -6.0000000000001025e-5*x0*x1 + 6.0000000000001025e-5*x4;
  double x11 = x7*x8;
  double x12 = -0.96606771244047496*x6 + 0.2582889370066549*x7*x8 - 0.96606771244047496*x9;
  double x13 = cos(q_1);
  double x14 = x12*x13;
  double x15 = sin(q_1);
  double x16 = x8*cos(q_0);
  double x17 = x15*x16;
  *val = m_base_link*x5*(3.4694469519536142e-18*x0*x1 - 3.4694469519536142e-18*x4) + m_end_effector*x5*(-x10 - 0.037943975293278594*x11 - 0.089852554946397045*x14 - 0.089852554946397045*x17 - 0.20028474339438354*x6 - 0.20028474339438354*x9 - 3.4694469519536142e-18*(-x12*x15 + x13*x16)*cos(q_2) + 3.4694469519536142e-18*(0.93328682501997218*x11 + 0.2582889370066549*x14 + 0.2582889370066549*x17 + 0.24952460252270103*x6 + 0.24952460252270103*x9)*sin(q_2)) + m_link_2*x5*(-x10 - 0.14288000000000001*x6 + 0.025549999999999989*x7*x8 - 0.14288000000000001*x9) + m_link_3*x5*(-x10 - 0.001643433328076236*x11 - 0.063689999999999997*x14 - 0.063689999999999997*x17 - 0.19057939016063152*x6 - 0.19057939016063152*x9);
}
