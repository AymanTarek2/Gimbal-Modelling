#include <math.h>
#include "../params.h"
void calculate_M_6_6(const double q[9], const double dq[9], double *val) {
  double q_0 = q[0]; double dq_0 = dq[0];
  double q_1 = q[1]; double dq_1 = dq[1];
  double q_2 = q[2]; double dq_2 = dq[2];
  double q_3 = q[3]; double dq_3 = dq[3];
  double q_4 = q[4]; double dq_4 = dq[4];
  double q_5 = q[5]; double dq_5 = dq[5];
  double q_6 = q[6]; double dq_6 = dq[6];
  double q_7 = q[7]; double dq_7 = dq[7];
  double q_8 = q[8]; double dq_8 = dq[8];
  double x0 = sin(q_4);
  double x1 = sin(q_5);
  double x2 = cos(q_4);
  double x3 = pow(x2, 2);
  double x4 = pow(x1, 2)*x3;
  double x5 = cos(q_5);
  double x6 = cos(q_0);
  double x7 = x0*x6;
  double x8 = sin(q_0);
  double x9 = x2*x5;
  double x10 = x8*x9;
  double x11 = x0*x8 - x6*x9;
  double x12 = x1*x2;
  double x13 = cos(q_1);
  double x14 = sin(q_1);
  double x15 = 0.2582889370066549*x10 - 0.96606771244047496*x12 + 0.2582889370066549*x7;
  double x16 = x11*x13 + x14*x15;
  double x17 = x11*x14;
  double x18 = x13*x15;
  double x19 = cos(q_2);
  double x20 = sin(q_2);
  double x21 = 0.93328682501997218*x10 + 0.24952460252270103*x12 - 0.2582889370066549*x17 + 0.2582889370066549*x18 + 0.93328682501997218*x7;
  *val = m_base_link*(pow(x0, 2) + x3*pow(x5, 2) + x4) + (1.0/2.0)*m_end_effector*(2*pow(x16*x19 + x20*x21, 2) + 2*pow(x16*x20 - x19*x21, 2) + (0.24952460252270103*x10 + 0.06671317498002774*x12 + 0.96606771244047496*x17 - 0.96606771244047496*x18 + 0.24952460252270103*x7)*(0.49904920504540207*x10 + 0.13342634996005548*x12 + 1.9321354248809499*x17 - 1.9321354248809499*x18 + 0.49904920504540207*x7)) + m_link_2*(pow(x11, 2) + x4 + pow(x10 + x7, 2)) + (1.0/2.0)*m_link_3*(2*pow(x16, 2) + 2*pow(x17 - x18, 2) + (0.96606771244047496*x10 + 0.2582889370066549*x12 + 0.96606771244047496*x7)*(1.9321354248809499*x10 + 0.51657787401330979*x12 + 1.9321354248809499*x7));
}
