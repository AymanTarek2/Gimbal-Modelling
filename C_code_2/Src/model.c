#define _USE_MATH_DEFINES
#include <math.h>
#include "model.h"

void compute_dynamics(
    const double q[3], const double dq[3], const double ddq[3],
    const double base_pos[3], const double base_vel[3], const double base_acc[3],
    const double base_ori[3], const double base_dori[3], const double base_ddori[3],
    double M[9][9], double C[9][9], double G[9], double tau[9]) {

  double sq[3], cq[3], sbo[3], cbo[3];
  for(int i=0; i<3; i++) {
      sq[i] = sin(q[i]);          cq[i] = cos(q[i]);
      sbo[i] = sin(base_ori[i]);  cbo[i] = cos(base_ori[i]);
  }

  // Base Rotation Matrix (Body -> World)  -- R_base
  double R[3][3];
  R[0][0] = cbo[1]*cbo[2];
  R[0][1] = -cbo[1]*sbo[2];
  R[0][2] = sbo[1];
  R[1][0] = cbo[0]*sbo[2] + cbo[2]*sbo[0]*sbo[1];
  R[1][1] = cbo[0]*cbo[2] - sbo[0]*sbo[1]*sbo[2];
  R[1][2] = -cbo[1]*sbo[0];
  R[2][0] = -cbo[0]*cbo[2]*sbo[1] + sbo[0]*sbo[2];
  R[2][1] = cbo[0]*sbo[1]*sbo[2] + cbo[2]*sbo[0];
  R[2][2] = cbo[0]*cbo[1];

  // M Calls
  calculate_M_0_0(sq, cq, sbo, cbo, &M[0][0]);
  calculate_M_0_1(sq, cq, sbo, cbo, &M[0][1]);
  calculate_M_0_2(sq, cq, sbo, cbo, &M[0][2]);
  calculate_M_0_3(sq, cq, sbo, cbo, &M[0][3]);
  calculate_M_0_4(sq, cq, sbo, cbo, &M[0][4]);
  calculate_M_0_5(sq, cq, sbo, cbo, &M[0][5]);
  calculate_M_0_6(sq, cq, sbo, cbo, &M[0][6]);
  calculate_M_0_7(sq, cq, sbo, cbo, &M[0][7]);
  calculate_M_0_8(sq, cq, sbo, cbo, &M[0][8]);
  calculate_M_1_0(sq, cq, sbo, cbo, &M[1][0]);
  calculate_M_1_1(sq, cq, sbo, cbo, &M[1][1]);
  calculate_M_1_2(sq, cq, sbo, cbo, &M[1][2]);
  calculate_M_1_3(sq, cq, sbo, cbo, &M[1][3]);
  calculate_M_1_4(sq, cq, sbo, cbo, &M[1][4]);
  calculate_M_1_5(sq, cq, sbo, cbo, &M[1][5]);
  calculate_M_1_6(sq, cq, sbo, cbo, &M[1][6]);
  calculate_M_1_7(sq, cq, sbo, cbo, &M[1][7]);
  calculate_M_1_8(sq, cq, sbo, cbo, &M[1][8]);
  calculate_M_2_0(sq, cq, sbo, cbo, &M[2][0]);
  calculate_M_2_1(sq, cq, sbo, cbo, &M[2][1]);
  calculate_M_2_2(sq, cq, sbo, cbo, &M[2][2]);
  calculate_M_2_3(sq, cq, sbo, cbo, &M[2][3]);
  calculate_M_2_4(sq, cq, sbo, cbo, &M[2][4]);
  calculate_M_2_5(sq, cq, sbo, cbo, &M[2][5]);
  calculate_M_2_6(&M[2][6]);
  calculate_M_2_7(&M[2][7]);
  calculate_M_2_8(&M[2][8]);
  calculate_M_3_0(sq, cq, sbo, cbo, &M[3][0]);
  calculate_M_3_1(sq, cq, sbo, cbo, &M[3][1]);
  calculate_M_3_2(sq, cq, sbo, cbo, &M[3][2]);
  calculate_M_3_3(sq, cq, sbo, cbo, &M[3][3]);
  calculate_M_3_4(sq, cq, sbo, cbo, &M[3][4]);
  calculate_M_3_5(sq, cq, sbo, cbo, &M[3][5]);
  calculate_M_3_6(sq, cq, sbo, cbo, &M[3][6]);
  calculate_M_3_7(sq, cq, sbo, cbo, &M[3][7]);
  calculate_M_3_8(sq, cq, sbo, cbo, &M[3][8]);
  calculate_M_4_0(sq, cq, sbo, cbo, &M[4][0]);
  calculate_M_4_1(sq, cq, sbo, cbo, &M[4][1]);
  calculate_M_4_2(sq, cq, sbo, cbo, &M[4][2]);
  calculate_M_4_3(sq, cq, sbo, cbo, &M[4][3]);
  calculate_M_4_4(sq, cq, sbo, cbo, &M[4][4]);
  calculate_M_4_5(sq, cq, sbo, cbo, &M[4][5]);
  calculate_M_4_6(sq, cq, sbo, cbo, &M[4][6]);
  calculate_M_4_7(sq, cq, sbo, cbo, &M[4][7]);
  calculate_M_4_8(sq, cq, sbo, cbo, &M[4][8]);
  calculate_M_5_0(sq, cq, sbo, cbo, &M[5][0]);
  calculate_M_5_1(sq, cq, sbo, cbo, &M[5][1]);
  calculate_M_5_2(sq, cq, sbo, cbo, &M[5][2]);
  calculate_M_5_3(sq, cq, sbo, cbo, &M[5][3]);
  calculate_M_5_4(sq, cq, sbo, cbo, &M[5][4]);
  calculate_M_5_5(sq, cq, sbo, cbo, &M[5][5]);
  calculate_M_5_6(sq, cq, sbo, cbo, &M[5][6]);
  calculate_M_5_7(sq, cq, sbo, cbo, &M[5][7]);
  calculate_M_5_8(sq, cq, sbo, cbo, &M[5][8]);
  calculate_M_6_0(sq, cq, sbo, cbo, &M[6][0]);
  calculate_M_6_1(sq, cq, sbo, cbo, &M[6][1]);
  calculate_M_6_2(&M[6][2]);
  calculate_M_6_3(sq, cq, sbo, cbo, &M[6][3]);
  calculate_M_6_4(sq, cq, sbo, cbo, &M[6][4]);
  calculate_M_6_5(sq, cq, sbo, cbo, &M[6][5]);
  calculate_M_6_6(sbo, cbo, &M[6][6]);
  calculate_M_6_7(sbo, cbo, &M[6][7]);
  calculate_M_6_8(sbo, cbo, &M[6][8]);
  calculate_M_7_0(sq, cq, sbo, cbo, &M[7][0]);
  calculate_M_7_1(sq, cq, sbo, cbo, &M[7][1]);
  calculate_M_7_2(&M[7][2]);
  calculate_M_7_3(sq, cq, sbo, cbo, &M[7][3]);
  calculate_M_7_4(sq, cq, sbo, cbo, &M[7][4]);
  calculate_M_7_5(sq, cq, sbo, cbo, &M[7][5]);
  calculate_M_7_6(sbo, cbo, &M[7][6]);
  calculate_M_7_7(sbo, cbo, &M[7][7]);
  calculate_M_7_8(sbo, cbo, &M[7][8]);
  calculate_M_8_0(sq, cq, sbo, cbo, &M[8][0]);
  calculate_M_8_1(sq, cq, sbo, cbo, &M[8][1]);
  calculate_M_8_2(&M[8][2]);
  calculate_M_8_3(sq, cq, sbo, cbo, &M[8][3]);
  calculate_M_8_4(sq, cq, sbo, cbo, &M[8][4]);
  calculate_M_8_5(sq, cq, sbo, cbo, &M[8][5]);
  calculate_M_8_6(sbo, cbo, &M[8][6]);
  calculate_M_8_7(sbo, cbo, &M[8][7]);
  calculate_M_8_8(sbo, cbo, &M[8][8]);
  // C Calls
  calculate_C_0_0(dq, base_dori, sq, cq, sbo, cbo, &C[0][0]);
  calculate_C_0_1(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[0][1]);
  calculate_C_0_2(dq, base_dori, sq, cq, sbo, cbo, &C[0][2]);
  calculate_C_0_3(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[0][3]);
  calculate_C_0_4(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[0][4]);
  calculate_C_0_5(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[0][5]);
  calculate_C_0_6(dq, base_dori, sq, cq, sbo, cbo, &C[0][6]);
  calculate_C_0_7(dq, base_dori, sq, cq, sbo, cbo, &C[0][7]);
  calculate_C_0_8(dq, base_dori, sq, cq, sbo, cbo, &C[0][8]);
  calculate_C_1_0(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[1][0]);
  calculate_C_1_1(dq, base_dori, sq, cq, sbo, cbo, &C[1][1]);
  calculate_C_1_2(dq, base_dori, sq, cq, sbo, cbo, &C[1][2]);
  calculate_C_1_3(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[1][3]);
  calculate_C_1_4(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[1][4]);
  calculate_C_1_5(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[1][5]);
  calculate_C_1_6(dq, base_dori, sq, cq, sbo, cbo, &C[1][6]);
  calculate_C_1_7(dq, base_dori, sq, cq, sbo, cbo, &C[1][7]);
  calculate_C_1_8(dq, base_dori, sq, cq, sbo, cbo, &C[1][8]);
  calculate_C_2_0(dq, base_dori, sq, cq, sbo, cbo, &C[2][0]);
  calculate_C_2_1(dq, base_dori, sq, cq, sbo, cbo, &C[2][1]);
  calculate_C_2_2(dq, base_dori, sq, cq, sbo, cbo, &C[2][2]);
  calculate_C_2_3(dq, base_dori, sq, cq, sbo, cbo, &C[2][3]);
  calculate_C_2_4(dq, base_dori, sq, cq, sbo, cbo, &C[2][4]);
  calculate_C_2_5(dq, base_dori, sq, cq, sbo, cbo, &C[2][5]);
  calculate_C_2_6(&C[2][6]);
  calculate_C_2_7(&C[2][7]);
  calculate_C_2_8(&C[2][8]);
  calculate_C_3_0(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[3][0]);
  calculate_C_3_1(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[3][1]);
  calculate_C_3_2(dq, base_dori, sq, cq, sbo, cbo, &C[3][2]);
  calculate_C_3_3(dq, base_dori, sq, cq, sbo, cbo, &C[3][3]);
  calculate_C_3_4(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[3][4]);
  calculate_C_3_5(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[3][5]);
  calculate_C_3_6(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[3][6]);
  calculate_C_3_7(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[3][7]);
  calculate_C_3_8(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[3][8]);
  calculate_C_4_0(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[4][0]);
  calculate_C_4_1(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[4][1]);
  calculate_C_4_2(dq, base_dori, sq, cq, sbo, cbo, &C[4][2]);
  calculate_C_4_3(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[4][3]);
  calculate_C_4_4(dq, base_dori, sq, cq, sbo, cbo, &C[4][4]);
  calculate_C_4_5(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[4][5]);
  calculate_C_4_6(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[4][6]);
  calculate_C_4_7(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[4][7]);
  calculate_C_4_8(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[4][8]);
  calculate_C_5_0(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[5][0]);
  calculate_C_5_1(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[5][1]);
  calculate_C_5_2(dq, base_dori, sq, cq, sbo, cbo, &C[5][2]);
  calculate_C_5_3(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[5][3]);
  calculate_C_5_4(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[5][4]);
  calculate_C_5_5(dq, base_dori, sq, cq, sbo, cbo, &C[5][5]);
  calculate_C_5_6(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[5][6]);
  calculate_C_5_7(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[5][7]);
  calculate_C_5_8(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[5][8]);
  calculate_C_6_0(dq, base_dori, sq, cq, sbo, cbo, &C[6][0]);
  calculate_C_6_1(dq, base_dori, sq, cq, sbo, cbo, &C[6][1]);
  calculate_C_6_2(&C[6][2]);
  calculate_C_6_3(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[6][3]);
  calculate_C_6_4(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[6][4]);
  calculate_C_6_5(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[6][5]);
  calculate_C_6_6(base_dori, sbo, cbo, &C[6][6]);
  calculate_C_6_7(base_dori, sbo, cbo, &C[6][7]);
  calculate_C_6_8(base_dori, sbo, cbo, &C[6][8]);
  calculate_C_7_0(dq, base_dori, sq, cq, sbo, cbo, &C[7][0]);
  calculate_C_7_1(dq, base_dori, sq, cq, sbo, cbo, &C[7][1]);
  calculate_C_7_2(&C[7][2]);
  calculate_C_7_3(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[7][3]);
  calculate_C_7_4(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[7][4]);
  calculate_C_7_5(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[7][5]);
  calculate_C_7_6(base_dori, sbo, cbo, &C[7][6]);
  calculate_C_7_7(base_dori, sbo, cbo, &C[7][7]);
  calculate_C_7_8(base_dori, sbo, cbo, &C[7][8]);
  calculate_C_8_0(dq, base_dori, sq, cq, sbo, cbo, &C[8][0]);
  calculate_C_8_1(dq, base_dori, sq, cq, sbo, cbo, &C[8][1]);
  calculate_C_8_2(&C[8][2]);
  calculate_C_8_3(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[8][3]);
  calculate_C_8_4(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[8][4]);
  calculate_C_8_5(dq, base_vel, base_dori, sq, cq, sbo, cbo, &C[8][5]);
  calculate_C_8_6(base_dori, sbo, cbo, &C[8][6]);
  calculate_C_8_7(base_dori, sbo, cbo, &C[8][7]);
  calculate_C_8_8(base_dori, sbo, cbo, &C[8][8]);
  // G Calls
  calculate_G_0(sq, cq, sbo, cbo, &G[0]);
  calculate_G_1(sq, cq, sbo, cbo, &G[1]);
  calculate_G_2(&G[2]);
  calculate_G_3(sq, cq, sbo, cbo, &G[3]);
  calculate_G_4(sq, cq, sbo, cbo, &G[4]);
  calculate_G_5(sq, cq, sbo, cbo, &G[5]);
  calculate_G_6(&G[6]);
  calculate_G_7(&G[7]);
  calculate_G_8(&G[8]);

  // Torque = M*ddq + C*dq + G
  double full_dq[9] = {dq[0], dq[1], dq[2], base_dori[0], base_dori[1], base_dori[2], base_vel[0], base_vel[1], base_vel[2]};
  double full_ddq[9] = {ddq[0], ddq[1], ddq[2], base_ddori[0], base_ddori[1], base_ddori[2], base_acc[0], base_acc[1], base_acc[2]};

  for(int i=0; i<9; i++) {
      tau[i] = 0.0;
      for(int j=0; j<9; j++) tau[i] += M[i][j] * full_ddq[j];
      for(int j=0; j<9; j++) tau[i] += C[i][j] * full_dq[j];
      tau[i] += G[i];
  }

}
