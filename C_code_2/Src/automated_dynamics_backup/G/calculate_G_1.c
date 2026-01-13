#include <math.h>
#include "../params.h"
void calculate_G_1(const double q[9], const double dq[9], double *val) {
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
  double x2 = x1*cos(q_4);
  double x3 = cos(q_0);
  double x4 = sin(q_5);
  double x5 = cos(q_3);
  double x6 = cos(q_5);
  double x7 = x1*sin(q_4);
  double x8 = x4*x5 + x6*x7;
  double x9 = x0*x2 + x3*x8;
  double x10 = cos(q_1);
  double x11 = x10*x9;
  double x12 = sin(q_1);
  double x13 = 0.2582889370066549*x0*x8 - 0.2582889370066549*x2*x3 - 0.96606771244047496*x4*x7 + 0.96606771244047496*x5*x6;
  double x14 = 2*g;
  *val = m_end_effector*x14*(-0.089852554946397045*x11 + 0.089852554946397045*x12*x13 + 3.4694469519536142e-18*(0.2582889370066549*x11 - 0.2582889370066549*x12*x13)*sin(q_2) - 3.4694469519536142e-18*(-x10*x13 - x12*x9)*cos(q_2)) + m_link_3*x14*(-0.063689999999999997*x11 + 0.063689999999999997*x12*x13);
}
