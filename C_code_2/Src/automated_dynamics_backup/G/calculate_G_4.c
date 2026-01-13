#include <math.h>
#include "../params.h"
void calculate_G_4(const double q[9], const double dq[9], double *val) {
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
  double x1 = x0*sin(q_4);
  double x2 = cos(q_5);
  double x3 = cos(q_4);
  double x4 = x0*x3;
  double x5 = x2*x4;
  double x6 = 2*g;
  double x7 = cos(q_0);
  double x8 = x1*x7;
  double x9 = x4*sin(q_5);
  double x10 = sin(q_0);
  double x11 = x10*x5;
  double x12 = -6.0000000000001025e-5*x0*x2*x3;
  double x13 = x0*x2*x3*x7 - x1*x10;
  double x14 = sin(q_1);
  double x15 = x13*x14;
  double x16 = cos(q_1);
  double x17 = 0.2582889370066549*x11 + 0.2582889370066549*x8 - 0.96606771244047496*x9;
  double x18 = x16*x17;
  *val = m_base_link*x6*(1.3877787807814457e-17*x1 + 3.4694469519536142e-18*x5) + m_end_effector*x6*(-0.037943975293278594*x11 - x12 - 0.089852554946397045*x15 - 0.089852554946397045*x18 - 0.037943975293278594*x8 - 0.20028474339438354*x9 - 3.4694469519536142e-18*(x13*x16 - x14*x17)*cos(q_2) + 3.4694469519536142e-18*(0.93328682501997218*x11 + 0.2582889370066549*x15 + 0.2582889370066549*x18 + 0.93328682501997218*x8 + 0.24952460252270103*x9)*sin(q_2)) + m_link_2*x6*(0.025549999999999989*x11 + 6.0000000000001025e-5*x5 + 0.025549999999999989*x8 - 0.14288000000000001*x9) + m_link_3*x6*(-0.001643433328076236*x11 - x12 - 0.063689999999999997*x15 - 0.063689999999999997*x18 - 0.001643433328076236*x8 - 0.19057939016063152*x9);
}
