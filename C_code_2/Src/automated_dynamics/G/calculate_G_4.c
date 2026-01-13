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
  double x1 = sin(q_4);
  double x2 = cos(q_4);
  double x3 = x0*x2;
  double x4 = x3*sin(q_5);
  double x5 = cos(q_5);
  double x6 = x3*x5;
  double x7 = cos(q_0);
  double x8 = x0*x1;
  double x9 = x7*x8;
  double x10 = sin(q_0);
  double x11 = x10*x6;
  double x12 = 0.02741*x6 + 0.093049999999999994*x8;
  double x13 = x0*x2*x5*x7 - x10*x8;
  double x14 = sin(q_1);
  double x15 = x13*x14;
  double x16 = cos(q_1);
  double x17 = 0.2582889370066549*x11 - 0.96606771244047496*x4 + 0.2582889370066549*x9;
  double x18 = x16*x17;
  *val = g*m_base_link*(0.11104456400000001*x0*x1 - 0.093055436000000005*x4 - 0.027333480599999994*x6) + g*m_end_effector*(-0.096196919199306855*x11 + x12 + 0.012028851236577825*x15 + 0.012028851236577825*x18 - 0.32690931520259248*x4 - 0.096196919199306855*x9 - 3.4694469519536142e-18*(x13*x16 - x14*x17)*cos(q_2) + 3.4694469519536142e-18*(0.93328682501997218*x11 + 0.2582889370066549*x15 + 0.2582889370066549*x18 + 0.24952460252270103*x4 + 0.93328682501997218*x9)*sin(q_2)) + g*m_link_2*(0.025549999999999989*x11 + x12 - 0.25392999999999999*x4 + 0.025549999999999989*x9) + g*m_link_3*(0.093049999999999994*x0*x1 + 0.02741*x0*x2*x5 - 0.062001646394292974*x11 - 0.017686989069877607*x15 - 0.017686989069877607*x18 - 0.31776682907069642*x4 - 0.062001646394292974*x9);
}
