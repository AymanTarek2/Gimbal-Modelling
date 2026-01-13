#include <math.h>
#include "../params.h"
void calculate_G_0(const double q[9], const double dq[9], double *val) {
  double q_0 = q[0]; double dq_0 = dq[0];
  double q_1 = q[1]; double dq_1 = dq[1];
  double q_2 = q[2]; double dq_2 = dq[2];
  double q_3 = q[3]; double dq_3 = dq[3];
  double q_4 = q[4]; double dq_4 = dq[4];
  double q_5 = q[5]; double dq_5 = dq[5];
  double q_6 = q[6]; double dq_6 = dq[6];
  double q_7 = q[7]; double dq_7 = dq[7];
  double q_8 = q[8]; double dq_8 = dq[8];
  double x0 = sin(q_0);
  double x1 = sin(q_3);
  double x2 = cos(q_4);
  double x3 = x0*x1*x2;
  double x4 = x1*sin(q_4)*cos(q_5) + sin(q_5)*cos(q_3);
  double x5 = cos(q_0);
  double x6 = x4*x5;
  double x7 = 2*g;
  double x8 = -x0*x4 + x1*x2*x5;
  double x9 = sin(q_1);
  double x10 = x8*x9;
  double x11 = cos(q_1);
  double x12 = 0.2582889370066549*x3 + 0.2582889370066549*x6;
  double x13 = x11*x12;
  *val = m_end_effector*x7*(-0.089852554946397045*x10 - 0.089852554946397045*x13 - 0.037943975293278594*x3 - 0.037943975293278594*x6 - 3.4694469519536142e-18*(x11*x8 - x12*x9)*cos(q_2) + 3.4694469519536142e-18*(0.2582889370066549*x10 + 0.2582889370066549*x13 + 0.93328682501997218*x3 + 0.93328682501997218*x6)*sin(q_2)) + m_link_2*x7*(0.025549999999999989*x3 + 0.025549999999999989*x6) + m_link_3*x7*(-0.063689999999999997*x10 - 0.063689999999999997*x13 - 0.001643433328076236*x3 - 0.001643433328076236*x6);
}
