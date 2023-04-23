#include "../include/main.h"

void opcontrol(void) {
    bool spin_flywheel = true;
    float drive_speeds[2] = {SLOW, FAST};
    int dspeed_select = 0;

    int fly_speed = 0;
    float flywheel_speeds[2] = {LOW, HIGH};
    float fly_vlt;

    int fly_targ = IDLE;
    int max_fly_vel = flywheel_speeds[fly_speed];

    int expand_sequence = UNFIRED;

    sands_of_time.reset();

    while (true) {
        // Drive
        switch (control_mode) {
            case TNK_STD:
                drive_r.spin(DIR_FWD, RIGHT_STICK_Y * drive_speed * STICK__PCT, VEL_PCT);
                drive_l.spin(DIR_FWD, LEFT_STICK_Y * drive_speed * STICK__PCT, VEL_PCT);
                break;
            case OSA_STD:
                drive_r.spin(DIR_FWD, (LEFT_STICK_Y - LEFT_STICK_X * SENSITIVITY) * drive_speed * STICK__PCT, VEL_PCT);
                drive_l.spin(DIR_FWD, (LEFT_STICK_Y + LEFT_STICK_X * SENSITIVITY) * drive_speed * STICK__PCT, VEL_PCT);
                break;
            case TSA_STD:
                drive_r.spin(DIR_FWD, (LEFT_STICK_Y - RIGHT_STICK_X * SENSITIVITY * drive_speed) * drive_speed * STICK__PCT, VEL_PCT);
                drive_l.spin(DIR_FWD, (LEFT_STICK_Y + RIGHT_STICK_X * SENSITIVITY * drive_speed) * drive_speed * STICK__PCT, VEL_PCT);
                break;
            case TNK_REV:
                drive_l.spin(DIR_REV, RIGHT_STICK_Y * drive_speed * STICK__PCT, VEL_PCT);
                drive_r.spin(DIR_REV, LEFT_STICK_Y * drive_speed * STICK__PCT, VEL_PCT);
                break;
            case OSA_REV:
                drive_l.spin(DIR_REV, (LEFT_STICK_Y - LEFT_STICK_X * SENSITIVITY) * drive_speed * STICK__PCT, VEL_PCT);
                drive_r.spin(DIR_REV, (LEFT_STICK_Y + LEFT_STICK_X * SENSITIVITY) * drive_speed * STICK__PCT, VEL_PCT);
                break;
            case TSA_REV:
                drive_r.spin(DIR_REV, (LEFT_STICK_Y + RIGHT_STICK_X * SENSITIVITY) * drive_speed * STICK__PCT, VEL_PCT);
                drive_l.spin(DIR_REV, (LEFT_STICK_Y - RIGHT_STICK_X * SENSITIVITY) * drive_speed * STICK__PCT, VEL_PCT);
                break;
        }

        // Change drive speed
        if (BTN_R2.PRESSED) {
            dspeed_select++;
            if (dspeed_select > 1) dspeed_select = 0;
            drive_speed = drive_speeds[dspeed_select];
        }

        // Intake
        roller.spin(DIR_FWD, (BTN_L1.pressing() - BTN_R1.pressing()) * BTN__PCT, VEL_PCT);

        // Flywheel
        if (BTN_RIGHT.PRESSED) spin_flywheel = !spin_flywheel;
        printf("spin_fly: %i\n", spin_flywheel);

        if (FLY_VEL < flywheel_speeds[fly_speed] && BTN_L2.pressing()) fly_vlt = 12;
        else if (BTN_L2.pressing()) fly_vlt = 8.5;
        else fly_vlt = 7;

        if (spin_flywheel) flywheel.spin(DIR_FWD, fly_vlt, VLT_VLT);
        else flywheel.stop();
        // Buzz
        if (FLY_VEL >= flywheel_speeds[fly_speed] && BTN_L2.pressing()) master.rumble(".");

        // //tmp
        // if (!BTN_L2.pressing()) fly_targ = IDLE;
        // if ((FLY_VEL < flywheel_speeds[fly_speed]) && BTN_L2.pressing()) {
        //   fly_targ += FLY_ACCEL; // for use on 20ms cycle
        // }
        // if (fly_targ > flywheel_speeds[fly_speed]) {
        //   fly_targ = max_fly_vel;
        // }
        // fly_vlt = (fly_targ - FLY_VEL) * FLY_KP;
        // if (fly_vlt < 0) fly_vlt = 0;
        // flywheel.spin(DIR_FWD, fly_vlt, VLT_VLT);

        // printf("fly_vlt: %.2f\n", fly_vlt);
        // printf("FLY_VEL: %.2lf\n", FLY_VEL);
        // printf("fly_trg: %i\n\n", fly_targ);

        // Change flywheel speed
        if (BTN_DOWN.PRESSED) {
            fly_speed++;
            if (fly_speed > 1) fly_speed = 0;
            if (fly_speed == 0) master.rumble("-");
            else master.rumble("--");
        }

        // Expansion / Blocke
        if (BTN_Y.pressing()) expansion.set(1);
        if (BTN_B.pressing()) blocker.set(1);

        // Timer - buzz w/ 20s left
        if (sands_of_time.time(sec) > 85 && sands_of_time.time(sec) < 85.2) master.rumble("....");

        wait(20, msec);
    }
}
