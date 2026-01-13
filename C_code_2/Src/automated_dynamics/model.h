#ifndef MODEL_H
#define MODEL_H

void compute_dynamics(const double q_meas[3], const double q_dot_meas[3], const double q_acc_meas[3], const double b_pos[3], const double b_vel[3], const double b_acc[3], const double b_ori[3], const double b_dori[3], const double b_ddori[3], double M[9][9], double C[9][9], double G[9], double tau[9]);
#endif
