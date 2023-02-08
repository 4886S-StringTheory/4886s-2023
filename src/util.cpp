#include "../include/main.h"

float pid(float setpoint, float current_value, float *sum, float *prev_error, double constants[3]) {
    float error = setpoint - current_value;
    *sum += error;
    float deriv = error - *prev_error;
    *prev_error = error;

    // Debug
    printf("error: %f\tkP: %f\tintegral: %f\tkI: %f\tderiv: %f\tkD: %f\t", error, constants[0], *sum, constants[1], deriv, constants[2]);

    return (error * constants[0]) + (*sum * constants[1]) + (deriv * constants[2]);
}

void pid_move(float inches, float max_in_per_sec, float in_per_sec_sec = 24, bool do_decel = true) {
    float target_vel = DRIVE_VEL;
    float target_pos = DRIVE_POS;
    float start_pos = DRIVE_POS;
    float start_dir = inrtl.angle(ROT_DEG);

    // PID variables
    float prev_pos_error = 0;
    float pos_sum = 0;
    float prev_dir_error = 0;
    float dir_sum = 0;

    // PID tuning constants
    double pos_constants[3] = {1, 1, 1};    // kP, kI, kD
    double dir_constants[3] = {1, 1, 1};    // kP, kI, kD

    // Outputs
    float pos_out;
    float dir_out;
    float dir_mod = .2;

    while (!within_range(start_pos + inches, DRIVE_POS, 1)) {
        // Accelerate
        if (target_vel < max_in_per_sec) {
            target_vel += in_per_sec_sec / 50; // divide by 50 because 50 Hz
            if (target_vel > max_in_per_sec) target_vel = max_in_per_sec;
        }
        
        // Find output based on expected position
        target_pos += target_vel / 50;
        pos_out = pid(target_pos, DRIVE_POS, &pos_sum, &prev_pos_error, dir_constants);

        dir_out = pid(start_dir, inrtl.angle(ROT_DEG), &dir_sum, &prev_dir_error, dir_constants);

        drive_l.spin(DIR_FWD, pos_out + dir_out * dir_mod, VLT_VLT);
        drive_r.spin(DIR_FWD, pos_out + dir_out * dir_mod, VLT_VLT);

        wait(20, msec); // 50 Hz
    }
}

bool within_range(double value, double base, double range) {
    return ((value <= base + range) && (value >= base - range));
}

float stop_dist(float current_vel, float accel, float target_vel = 0) {     // 4886T's code - learn physics
  return -(target_vel * target_vel - current_vel * current_vel) / (2 * accel); 
  //derived from physics equation V^2 = (V0)^2 +  2a(X-X0)
  //set V to targetVel and solve for X-X0,
  // = (targetVel^2 - currentVel^2)/2*accel
}

// returns 0 for left, 1 for right, 2 for neither
int b_scrn_hrzside(void) {
    if (!B_SCRN.pressing()) return 2;
    if (B_SCRN.xPosition() < B_SCRN_X_MID) return LEFT;
    return RIGHT;
}

// returns 0 for top, 1 for bottom, 2 for neither
int b_scrn_vrtside(void) {
    if (!B_SCRN.pressing()) return 2;
    if (B_SCRN.yPosition() < B_SCRN_Y_MID) return UP;
    return DOWN;
}