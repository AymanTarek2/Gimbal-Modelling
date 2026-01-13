#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#define DOF 3

// Total Doubles: 37
typedef struct {
    double q[DOF];
    double q_dot[DOF];
    double base_pos[3];
    double base_vel[3];
    double base_acc[3];
    double base_ori[3];  
    double base_dori[3]; 
    double base_ddori[3];

    // INPUT: Euler Angles (Real Sensor Format)
    double ee_rpy[3];    // [Roll, Pitch, Yaw]
    double ee_vel[3];    

    double gain_lambda[DOF];
    double gain_k[DOF];
    double gain_pos_error;
} RobotState;

typedef struct {
    double torque[DOF];
    double q_des[DOF];
    double q_curr[DOF];
    double ee_des[3];
    double ee_curr[3];
} ControlOutput;

int read_robot_state(RobotState *state);
void write_control_output(ControlOutput *out);

#endif