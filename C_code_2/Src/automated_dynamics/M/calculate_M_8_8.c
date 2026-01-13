#include <math.h>
#include "../params.h"
void calculate_M_8_8(const double q[9], const double dq[9], double *val) {
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
  double x1 = cos(q_4);
  double x2 = sin(q_3);
  double x3 = cos(q_5);
  double x4 = x2*x3;
  double x5 = sin(q_5);
  double x6 = x0*sin(q_4);
  double x7 = x5*x6;
  double x8 = pow(x4 + x7, 2);
  double x9 = x2*x5 - x3*x6;
  double x10 = cos(q_0);
  double x11 = x0*x1;
  double x12 = x10*x11;
  double x13 = sin(q_0);
  double x14 = x13*x9;
  double x15 = x10*x9 - x11*x13;
  double x16 = sin(q_1);
  double x17 = x15*x16;
  double x18 = cos(q_1);
  double x19 = 0.2582889370066549*x12 + 0.2582889370066549*x14 + 0.96606771244047496*x4 + 0.96606771244047496*x7;
  double x20 = x18*x19;
  double x21 = x15*x18 - x16*x19;
  double x22 = sin(q_2);
  double x23 = cos(q_2);
  double x24 = 0.93328682501997218*x12 + 0.93328682501997218*x14 + 0.2582889370066549*x17 + 0.2582889370066549*x20 - 0.24952460252270103*x4 - 0.24952460252270103*x7;
  *val = m_base_link*(pow(x0, 2)*pow(x1, 2) + x8 + pow(x9, 2)) + (1.0/2.0)*m_end_effector*(2*pow(x21*x22 + x23*x24, 2) + 2*pow(x21*x23 - x22*x24, 2) + (-0.49904920504540207*x12 - 0.49904920504540207*x14 + 1.9321354248809499*x17 + 1.9321354248809499*x20 + 0.13342634996005548*x4 + 0.13342634996005548*x7)*(-0.24952460252270103*x12 - 0.24952460252270103*x14 + 0.96606771244047496*x17 + 0.96606771244047496*x20 + 0.06671317498002774*x4 + 0.06671317498002774*x7)) + m_link_2*(pow(x15, 2) + x8 + pow(x12 + x14, 2)) + (1.0/2.0)*m_link_3*(2*pow(x21, 2) + 2*pow(x17 + x20, 2) + (0.96606771244047496*x12 + 0.96606771244047496*x14 - 0.2582889370066549*x4 - 0.2582889370066549*x7)*(1.9321354248809499*x12 + 1.9321354248809499*x14 - 0.51657787401330979*x4 - 0.51657787401330979*x7));
}
