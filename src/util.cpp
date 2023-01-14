#include "../include/main.h"

/*
void pid_move(float dist, float max_vel, float accel = 24, bool decel = false) {
    // accel
    float vel = drive_r.velocity(VEL_RPM) + drive_l.velocity(VEL_RPM) / 2;
    float pos = 
    float target_vel = vel;
    while ()
}
*/

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