#include <stdio.h>
#include <math.h>     
#include <string.h>   
#include <fcntl.h>    
#include <io.h>       
#include <windows.h> 

#include "backstepping.h"
#include "update_states.h"
#include "model.h" 
#include "trajectory_planning.h"
#include "communication.h"    
#include "inverse_position.h" 
#include "base_estimation.h" 

#define DT 0.002
#define PI 3.14159265358979323846

// --- Math Helpers ---
double normalize_angle(double angle) {
    while (angle > PI) angle -= 2.0 * PI;
    while (angle <= -PI) angle += 2.0 * PI;
    return angle;
}

double angle_diff(double a, double b) {
    double d = a - b;
    while (d > PI) d -= 2.0 * PI;
    while (d <= -PI) d += 2.0 * PI;
    return d;
}

// Standard ZYX RPY to Quat
void rpy_to_quat(const double rpy[3], double q[4]) {
    double r=rpy[0], p=rpy[1], y=rpy[2];
    double cr = cos(r*0.5); double sr = sin(r*0.5);
    double cp = cos(p*0.5); double sp = sin(p*0.5);
    double cy = cos(y*0.5); double sy = sin(y*0.5);

    q[0] = cr*cp*cy + sr*sp*sy; 
    q[1] = sr*cp*cy - cr*sp*sy; 
    q[2] = cr*sp*cy + sr*cp*sy; 
    q[3] = cr*cp*sy - sr*sp*cy; 
}

// ROBUST Quat to RPY with Continuity
// Picks the RPY solution closest to 'prev' to avoid 180-deg flips at Pitch=90
void quat_to_rpy_continuous(const double q[4], const double prev[3], double out[3]) {
    double w=q[0], x=q[1], y=q[2], z=q[3];
    
    // Standard Solution (Pitch restricted to -90..90)
    double r1, p1, y1;
    double sinp = 2.0 * (w*y - x*z);
    if (fabs(sinp) >= 1) p1 = copysign(PI/2, sinp);
    else p1 = asin(sinp);
    
    r1 = atan2(2.0*(w*x + y*z), 1.0 - 2.0*(x*x + y*y));
    y1 = atan2(2.0*(w*z + x*y), 1.0 - 2.0*(y*y + z*z));

    // Alternative Solution (Pitch > 90, Roll/Yaw flipped)
    // P2 = PI - P1
    // R2 = R1 + PI
    // Y2 = Y1 + PI
    double p2 = PI - p1;
    double r2 = r1 + PI;
    double y2 = y1 + PI;

    // Normalize
    p1 = normalize_angle(p1); r1 = normalize_angle(r1); y1 = normalize_angle(y1);
    p2 = normalize_angle(p2); r2 = normalize_angle(r2); y2 = normalize_angle(y2);

    // Compare distances to previous state
    double d1 = fabs(angle_diff(p1, prev[1])) + fabs(angle_diff(r1, prev[0])) + fabs(angle_diff(y1, prev[2]));
    double d2 = fabs(angle_diff(p2, prev[1])) + fabs(angle_diff(r2, prev[0])) + fabs(angle_diff(y2, prev[2]));

    if (d1 < d2) {
        out[0] = r1; out[1] = p1; out[2] = y1;
    } else {
        out[0] = r2; out[1] = p2; out[2] = y2;
    }
}

// Timer
LARGE_INTEGER frequency;
void timer_init() { QueryPerformanceFrequency(&frequency); }
void timer_start(LARGE_INTEGER *start) { QueryPerformanceCounter(start); }
double timer_delta_seconds(LARGE_INTEGER start) {
    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);
    return (double)(end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;
}

int main() {
    _setmode(_fileno(stdin), _O_BINARY);
    _setmode(_fileno(stdout), _O_BINARY);
    setvbuf(stdout, NULL, _IONBF, 0);
    timer_init();

    double L1 = 0.13548; 
    double L2 = 0.09637; 
    double ddq_dummy[3] = {0,0,0}, tau_dummy[3];

    Matrix3x3 M, C;
    Vector3 G;
    Vector3 u_control;
    Vector3 dbg_M, dbg_C, dbg_G, dbg_E, dbg_K;

    RobotState state_in;
    ControlOutput control_out;
    TrajectoryPoint desired_state;

    // State Tracking
    static double prev_base_rpy[3] = {0.0, 0.0, 0.0};
    int first_run = 1;

    double target_global_roll  = 1.4;
    double target_global_pitch = 0.0;
    double target_global_yaw   = 0.0;

    const double RAD2DEG = 180.0 / PI;
    const double DEG2RAD = PI / 180.0;

    fprintf(stderr, "[C-Controller] Robust Mode Started.\n");

    int iter = 0;
    while (read_robot_state(&state_in)) {
        
        // Init State
        if (first_run) {
            prev_base_rpy[0] = state_in.base_ori[0];
            prev_base_rpy[1] = state_in.base_ori[1];
            prev_base_rpy[2] = state_in.base_ori[2];
            first_run = 0;
        }

        // Gains
        ControlGains gains;
        for(int i=0; i<DOF; i++) {
            for(int j=0; j<DOF; j++) {
                gains.Lambda[i][j] = (i==j) ? state_in.gain_lambda[i] : 0.0;
                gains.K[i][j]      = (i==j) ? state_in.gain_k[i]      : 0.0;
            }
        }

        // 1. Data Conv & Setup
        double ee_quat[4];
        rpy_to_quat(state_in.ee_rpy, ee_quat);
        
        double target_rpy[3] = {target_global_roll, target_global_pitch, target_global_yaw};
        double target_quat[4];
        rpy_to_quat(target_rpy, target_quat);

        // 2. Base Estimation
        double base_quat[4];
        double base_vel[3];
        
        estimate_base_state(ee_quat, state_in.ee_vel, state_in.q, state_in.q_dot, base_quat, base_vel);

        // 3. Inverse Kinematics
        double q1_deg, q2_deg, q3_deg;
        inverse_position_kinematics_quat(base_quat, target_quat, &q1_deg, &q2_deg, &q3_deg);
        
        desired_state.x_d[0] = q1_deg * DEG2RAD;
        desired_state.x_d[1] = q2_deg * DEG2RAD;
        desired_state.x_d[2] = q3_deg * DEG2RAD;
        desired_state.dx_d[0] = 0; desired_state.dx_d[1] = 0; desired_state.dx_d[2] = 0;
        desired_state.ddx_d[0] = 0; desired_state.ddx_d[1] = 0; desired_state.ddx_d[2] = 0;

        // 4. Dynamics (With Continuity Fix)
        // Convert the estimated Base Quat to RPY using the previous state as a guide.
        // This prevents the Euler angles from flipping signs when pitch > 90.
        double current_base_rpy[3];
        quat_to_rpy_continuous(base_quat, prev_base_rpy, current_base_rpy);
        
        // Update history
        prev_base_rpy[0] = current_base_rpy[0];
        prev_base_rpy[1] = current_base_rpy[1];
        prev_base_rpy[2] = current_base_rpy[2];

        compute_dynamics(
            state_in.q, state_in.q_dot, ddq_dummy,          
            state_in.base_pos, state_in.base_vel, state_in.base_acc, 
            current_base_rpy, base_vel, state_in.base_ddori, // Use Continuous RPY
            L1, L2, M, C, G, tau_dummy
        );
        
        // --- ADDED DAMPING TERM ---
        // M[0][0] += 1e-4;
        // M[1][1] += 1e-4;
        // M[2][2] += 1e-4;
        // --------------------------
        
        // 5. Backstepping
        compute_backstepping_control(
            state_in.q, state_in.q_dot, desired_state,      
            M, C, G, gains, state_in.gain_pos_error, u_control,          
            dbg_M, dbg_C, dbg_G, dbg_E, dbg_K 
        );
        
        control_out.torque[0] = u_control[0];
        control_out.torque[1] = u_control[1];
        control_out.torque[2] = u_control[2];

        // Pass through debug
        control_out.q_des[0] = desired_state.x_d[0];
        control_out.q_des[1] = desired_state.x_d[1];
        control_out.q_des[2] = desired_state.x_d[2];
        control_out.q_curr[0] = state_in.q[0];
        control_out.q_curr[1] = state_in.q[1];
        control_out.q_curr[2] = state_in.q[2];
        control_out.ee_des[0] = target_rpy[0];
        control_out.ee_des[1] = target_rpy[1];
        control_out.ee_des[2] = target_rpy[2];
        control_out.ee_curr[0] = 0; control_out.ee_curr[1] = 0; control_out.ee_curr[2] = 0;

        write_control_output(&control_out);
        iter++;

        if (iter % 10 == 0) {
            fprintf(stderr, "\n--- GIMBAL STATE REPORT (Iter: %d) ---\n", iter);
            fprintf(stderr, "EE Desired  : %.4f  %.4f  %.4f\n", 
                normalize_angle(target_rpy[0]), target_rpy[1], normalize_angle(target_rpy[2]));
            fprintf(stderr, "EE Current  : %.4f  %.4f  %.4f\n", 
                normalize_angle(state_in.ee_rpy[0]), state_in.ee_rpy[1], normalize_angle(state_in.ee_rpy[2]));
            fprintf(stderr, "Qs Desired  : %.4f  %.4f  %.4f\n", 
                normalize_angle(desired_state.x_d[0]), normalize_angle(desired_state.x_d[1]), normalize_angle(desired_state.x_d[2]));
            fprintf(stderr, "Q Current   : %.4f  %.4f  %.4f\n", 
                normalize_angle(state_in.q[0]), normalize_angle(state_in.q[1]), normalize_angle(state_in.q[2]));
            fprintf(stderr, "Base Est    : %.4f  %.4f  %.4f\n", 
                normalize_angle(current_base_rpy[0]), current_base_rpy[1], normalize_angle(current_base_rpy[2]));
            fprintf(stderr, "Real Base   : %.4f  %.4f  %.4f\n", 
                normalize_angle(state_in.base_ori[0]), state_in.base_ori[1], normalize_angle(state_in.base_ori[2]));
            fprintf(stderr, "---------------------------------------\n");


            fprintf(stderr, "--- DYNAMICS MATRICES (Scientific Notation) ---\n");
            
            // 1. Print Mass Matrix (M)
            fprintf(stderr, "M Matrix:\n");
            for(int r=0; r<3; r++) {
                fprintf(stderr, "  [%10.3e  %10.3e  %10.3e]\n", M[r][0], M[r][1], M[r][2]);
            }

            // 2. Calculate and Print Determinant of M (Crucial for singularity check)
            double detM = M[0][0]*(M[1][1]*M[2][2] - M[1][2]*M[2][1]) -
                          M[0][1]*(M[1][0]*M[2][2] - M[1][2]*M[2][0]) +
                          M[0][2]*(M[1][0]*M[2][1] - M[1][1]*M[2][0]);
            fprintf(stderr, "Det(M): %10.3e\n", detM);

            // 3. Print Coriolis Matrix (C)
            fprintf(stderr, "C Matrix:\n");
            for(int r=0; r<3; r++) {
                fprintf(stderr, "  [%10.3e  %10.3e  %10.3e]\n", C[r][0], C[r][1], C[r][2]);
            }

            // 4. Print Gravity Vector (G)
            fprintf(stderr, "G Vector:\n");
            fprintf(stderr, "  [%10.3e  %10.3e  %10.3e]\n", G[0], G[1], G[2]);
            
            fprintf(stderr, "---------------------------------------\n");
        
        }
    }
    return 0;
}