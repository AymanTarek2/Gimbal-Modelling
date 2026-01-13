#include <math.h>
#include "../params.h"
void calculate_M_7_7(const double q[9], const double dq[9], double *val) {
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
  double x1 = cos(q_4);
  double x2 = sin(q_5);
  double x3 = cos(q_3);
  double x4 = cos(q_5);
  double x5 = x0*sin(q_4);
  double x6 = x2*x3 + x4*x5;
  double x7 = x3*x4;
  double x8 = x2*x5;
  double x9 = pow(-x7 + x8, 2);
  double x10 = sin(q_0);
  double x11 = x0*x1;
  double x12 = cos(q_0);
  double x13 = x10*x11 + x12*x6;
  double x14 = x11*x12;
  double x15 = x10*x6;
  double x16 = sin(q_1);
  double x17 = x13*x16;
  double x18 = cos(q_1);
  double x19 = -0.2582889370066549*x14 + 0.2582889370066549*x15 + 0.96606771244047496*x7 - 0.96606771244047496*x8;
  double x20 = x18*x19;
  double x21 = x13*x18 - x16*x19;
  double x22 = sin(q_2);
  double x23 = cos(q_2);
  double x24 = -0.93328682501997218*x14 + 0.93328682501997218*x15 + 0.2582889370066549*x17 + 0.2582889370066549*x20 - 0.24952460252270103*x7 + 0.24952460252270103*x8;
  *val = m_base_link*(pow(x0, 2)*pow(x1, 2) + pow(x6, 2) + x9) + (1.0/2.0)*m_end_effector*(2*pow(x21*x22 + x23*x24, 2) + 2*pow(x21*x23 - x22*x24, 2) + (0.24952460252270103*x14 - 0.24952460252270103*x15 + 0.96606771244047496*x17 + 0.96606771244047496*x20 + 0.06671317498002774*x7 - 0.06671317498002774*x8)*(0.49904920504540207*x14 - 0.49904920504540207*x15 + 1.9321354248809499*x17 + 1.9321354248809499*x20 + 0.13342634996005548*x7 - 0.13342634996005548*x8)) + m_link_2*(pow(x13, 2) + x9 + pow(-x14 + x15, 2)) + (1.0/2.0)*m_link_3*(2*pow(x21, 2) + 2*pow(x17 + x20, 2) + (-1.9321354248809499*x14 + 1.9321354248809499*x15 - 0.51657787401330979*x7 + 0.51657787401330979*x8)*(-0.96606771244047496*x14 + 0.96606771244047496*x15 - 0.2582889370066549*x7 + 0.2582889370066549*x8));
}
