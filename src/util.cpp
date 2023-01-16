#include "../include/main.h"

void pid_move(float dist, float max_vel, float accel_rate = 24, bool decel = true) {
    // Initialize variables
    float vel = (drive_r.velocity(VEL_RPM) + drive_l.velocity(VEL_RPM)) / 2;
    float target_vel = vel;
    float pos = (drive_r.position(ROT_REV) * DRIVE_REV__IN + drive_l.position(ROT_REV) * DRIVE_REV__IN) / 2;
    float target_pos = pos;
    float start_pos = pos;

    float error;
    float prev_error = error;
    float sum = 0;
    float deriv;

    float kP = 1;
    float kI = 1;
    float kD = 1;

    float output;

    while (pos <= start_pos + dist) {

        // Accelerate
        if (target_vel < max_vel) {
            target_vel += accel_rate / 50; // divide by 50 because 50 Hz
            if (target_vel > max_vel) target_vel = max_vel;
        }
        
        // PID
        error = target_pos - pos;
        sum += error;
        deriv = error - prev_error;
        prev_error = error;

        output = (kP * error) + (kI * sum) + (kD * deriv);

        drive_l.spin(DIR_FWD, output, VLT_VLT);
        drive_r.spin(DIR_FWD, output, VLT_VLT);


        wait (20, msec); // 50 Hz
    }
}

// returns 0 for left, 1 for right, 2 for neither
int b_scrn_hrzside(void) {
    if (!B_SCRN.pressing()) return 2;
    if (B_SCRN.xPosition() < B_SCRN_X_MID) return 0;
    return 1;
}

// returns 0 for top, 1 for bottom, 2 for neither
int b_scrn_vrtside(void) {
    if (!B_SCRN.pressing()) return 2;
    if (B_SCRN.yPosition() < B_SCRN_Y_MID) return 0;
    return 1;
}