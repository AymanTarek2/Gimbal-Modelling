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
  double x2 = cos(q_5);
  double x3 = x0*x2;
  double x4 = cos(q_3);
  double x5 = cos(q_4);
  double x6 = x4*x5;
  double x7 = sin(q_4);
  double x8 = x4*x7;
  double x9 = x1*x8;
  double x10 = sin(q_0);
  double x11 = x0*x1;
  double x12 = -x11 + x2*x4*x7;
  double x13 = cos(q_0);
  double x14 = x13*x6;
  double x15 = 0.02741*x11 - 0.02741*x2*x4*x7 + 0.093049999999999994*x6;
  double x16 = x10*x6 + x12*x13;
  double x17 = sin(q_1);
  double x18 = x16*x17;
  double x19 = cos(q_1);
  double x20 = 0.2582889370066549*x10*x12 - 0.2582889370066549*x14 - 0.96606771244047496*x3 - 0.96606771244047496*x9;
  double x21 = x19*x20;
  double x22 = x10*x12;
  *val = g*m_base_link*(0.027333480599999994*x0*x1 - 0.027333480599999994*x2*x8 - 0.093055436000000005*x3 - 0.11104456400000001*x6 - 0.093055436000000005*x9) + g*m_end_effector*(0.096196919199306855*x13*x4*x5 - x15 + 0.012028851236577825*x16*x17 + 0.012028851236577825*x19*x20 - 0.096196919199306855*x22 - 0.32690931520259248*x3 - 0.32690931520259248*x9 - 3.4694469519536142e-18*(x16*x19 - x17*x20)*cos(q_2) + 3.4694469519536142e-18*(-0.93328682501997218*x14 + 0.2582889370066549*x18 + 0.2582889370066549*x21 + 0.93328682501997218*x22 + 0.24952460252270103*x3 + 0.24952460252270103*x9)*sin(q_2)) + g*m_link_2*(0.025549999999999989*x10*x12 - 0.025549999999999989*x14 - x15 - 0.25392999999999999*x3 - 0.25392999999999999*x9) + g*m_link_3*(0.062001646394292974*x13*x4*x5 - x15 - 0.017686989069877607*x18 - 0.017686989069877607*x21 - 0.062001646394292974*x22 - 0.31776682907069642*x3 - 0.31776682907069642*x9);
}
