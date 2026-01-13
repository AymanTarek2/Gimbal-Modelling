#include <math.h>
#include "model.h"

void calculate_M_0_0(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_M_0_1(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_M_0_2(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_M_1_0(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_M_1_1(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_M_1_2(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_M_2_0(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_M_2_1(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_M_2_2(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_C_0_0(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_C_0_1(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_C_0_2(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_C_1_0(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_C_1_1(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_C_1_2(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_C_2_0(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_C_2_1(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_C_2_2(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_G_0(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_G_1(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);
void calculate_G_2(    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    const double sq[3], const double cq[3],
    const double sbp[3], const double cbp[3],
    const double sbo[3], const double cbo[3],
    double L1, double L2, double *val);

void compute_dynamics(
    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    double L1, double L2,
    double M[3][3], double C[3][3], double G[3], double tau[3]) {

  // --- SPEED: Pre-calculate ALL Trig ONCE --- 
  double sq[3], cq[3], sbp[3], cbp[3], sbo[3], cbo[3];
  for(int i=0; i<3; i++) {
      sq[i] = sin(q[i]);          cq[i] = cos(q[i]);
      sbp[i] = sin(base_pos[i]);  cbp[i] = cos(base_pos[i]);
      sbo[i] = sin(base_ori[i]);  cbo[i] = cos(base_ori[i]);
  }

  // 1. Mass Matrix
  calculate_M_0_0(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &M[0][0]);
  calculate_M_0_1(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &M[0][1]);
  calculate_M_0_2(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &M[0][2]);
  calculate_M_1_0(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &M[1][0]);
  calculate_M_1_1(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &M[1][1]);
  calculate_M_1_2(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &M[1][2]);
  calculate_M_2_0(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &M[2][0]);
  calculate_M_2_1(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &M[2][1]);
  calculate_M_2_2(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &M[2][2]);

  // 2. Coriolis Matrix
  calculate_C_0_0(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &C[0][0]);
  calculate_C_0_1(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &C[0][1]);
  calculate_C_0_2(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &C[0][2]);
  calculate_C_1_0(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &C[1][0]);
  calculate_C_1_1(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &C[1][1]);
  calculate_C_1_2(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &C[1][2]);
  calculate_C_2_0(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &C[2][0]);
  calculate_C_2_1(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &C[2][1]);
  calculate_C_2_2(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &C[2][2]);

  // 3. Gravity Vector
  calculate_G_0(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &G[0]);
  calculate_G_1(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &G[1]);
  calculate_G_2(q, dq, ddq, base_pos, base_vel, base_acc, base_ori, base_dori, base_ddori, sq, cq, sbp, cbp, sbo, cbo, L1, L2, &G[2]);

  // 4. Compute Torque
  for(int i=0; i<3; i++) {
      tau[i] = 0.0;
      for(int j=0; j<3; j++) tau[i] += M[i][j] * ddq[j];
      for(int j=0; j<3; j++) tau[i] += C[i][j] * dq[j];
      tau[i] += G[i];
  }
}
