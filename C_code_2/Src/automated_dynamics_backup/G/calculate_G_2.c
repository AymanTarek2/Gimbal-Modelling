#include <math.h>
#include "../params.h"
void calculate_G_2(const double q[9], const double dq[9], double *val) {
  double q_0 = q[0]; double dq_0 = dq[0];
  double q_1 = q[1]; double dq_1 = dq[1];
  double q_2 = q[2]; double dq_2 = dq[2];
  double q_3 = q[3]; double dq_3 = dq[3];
  double q_4 = q[4]; double dq_4 = dq[4];
  double q_5 = q[5]; double dq_5 = dq[5];
  double q_6 = q[6]; double dq_6 = dq[6];
  double q_7 = q[7]; double dq_7 = dq[7];
  double q_8 = q[8]; double dq_8 = dq[8];
  double x0 = cos(q_1);
  double x1 = sin(q_0);
  double x2 = sin(q_3);
  double x3 = x2*cos(q_4);
  double x4 = cos(q_0);
  double x5 = sin(q_5);
  double x6 = cos(q_3);
  double x7 = cos(q_5);
  double x8 = x2*sin(q_4);
  double x9 = x5*x6 + x7*x8;
  double x10 = x1*x3 + x4*x9;
  double x11 = sin(q_1);
  double x12 = x6*x7;
  double x13 = x5*x8;
  double x14 = x3*x4;
  double x15 = x1*x9;
  double x16 = 0.96606771244047496*x12 - 0.96606771244047496*x13 - 0.2582889370066549*x14 + 0.2582889370066549*x15;
  *val = 2*g*m_end_effector*(3.4694469519536142e-18*(x0*x10 - x11*x16)*sin(q_2) + 3.4694469519536142e-18*(0.2582889370066549*x0*x16 + 0.2582889370066549*x10*x11 - 0.24952460252270103*x12 + 0.24952460252270103*x13 - 0.93328682501997218*x14 + 0.93328682501997218*x15)*cos(q_2));
}
