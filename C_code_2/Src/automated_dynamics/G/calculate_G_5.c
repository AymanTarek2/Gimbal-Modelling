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
  double x1 = sin(q_5);
  double x2 = x0*x1;
  double x3 = cos(q_5);
  double x4 = sin(q_3);
  double x5 = sin(q_4);
  double x6 = x4*x5;
  double x7 = x3*x6;
  double x8 = sin(q_0);
  double x9 = x1*x6;
  double x10 = x0*x3 - x9;
  double x11 = -0.02741*x0*x3 + 0.02741*x9;
  double x12 = 0.2582889370066549*x10*x8 - 0.96606771244047496*x2 - 0.96606771244047496*x7;
  double x13 = cos(q_1);
  double x14 = x12*x13;
  double x15 = x10*x8;
  double x16 = sin(q_1);
  double x17 = cos(q_0);
  double x18 = x10*x17;
  double x19 = x16*x18;
  *val = g*m_base_link*(-0.027333480599999994*x0*x3 + 0.027333480599999994*x1*x4*x5 - 0.093055436000000005*x2 - 0.093055436000000005*x7) + g*m_end_effector*(0.012028851236577825*x10*x16*x17 - x11 + 0.012028851236577825*x12*x13 - 0.096196919199306855*x15 - 0.32690931520259248*x2 - 0.32690931520259248*x7 - 3.4694469519536142e-18*(-x12*x16 + x13*x18)*cos(q_2) + 3.4694469519536142e-18*(0.2582889370066549*x14 + 0.93328682501997218*x15 + 0.2582889370066549*x19 + 0.24952460252270103*x2 + 0.24952460252270103*x7)*sin(q_2)) + g*m_link_2*(0.025549999999999989*x10*x8 - x11 - 0.25392999999999999*x2 - 0.25392999999999999*x7) + g*m_link_3*(-x11 - 0.017686989069877607*x14 - 0.062001646394292974*x15 - 0.017686989069877607*x19 - 0.31776682907069642*x2 - 0.31776682907069642*x7);
}
