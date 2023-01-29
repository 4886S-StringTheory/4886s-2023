#include "../include/main.h"

bool within_range(double value, double base, double range) {
    return ((value <= base + range) && (value >= base - range));
}

void pid_move(float inches, float max_in_per_sec, float in_per_sec_sec = 24, bool do_decel = true) {
    float target_vel = DRIVE_VEL;
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

    while (pos <= start_pos + inches) {

        // Accelerate
        if (target_vel < max_in_per_sec) {
            target_vel += in_per_sec_sec / 50; // divide by 50 because 50 Hz
            if (target_vel > max_in_per_sec) target_vel = max_in_per_sec;
        }
        
        // PID
        error = target_pos - pos;
        sum += error;
        deriv = error - prev_error;
        prev_error = error;

        output = (kP * error) + (kI * sum) + (kD * deriv);

        drive_l.spin(DIR_FWD, output, VLT_VLT);
        drive_r.spin(DIR_FWD, output, VLT_VLT);

        wait(20, msec); // 50 Hz
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