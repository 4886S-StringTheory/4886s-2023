#include "../include/main.h"

void autonomous(void) {
    switch (auton_mode) {
        case AWP:
            break;
        case HALF_AWP_L:
            /* TODO
             * 
             * Fire 2
             * Roller
             * Intake 3
             * Fire
             *
             * Threads?
             *
             */

            // Fire 2
            flywheel.spin(DIR_FWD, 12, VLT_VLT);
            drive_straight(14, 48, 24);
            flywheel.spin(DIR_FWD, 10, VLT_VLT);
            wait(1000, msec);
            roller.spinFor(DIR_FWD, -3, ROT_REV);
            wait(500, msec);
            roller.spinFor(DIR_FWD, -3, ROT_REV);
            // Roller
            drive_turn(-20, WHEEL_TO_WHEEL_DIST / 2.0, 36, 24);
            drive_straight(-12, 48, 24);
            roller.spinFor(DIR_FWD, 3, ROT_REV);

            break;
        case HALF_AWP_R:
            break;
        case ROLLER:
            break;
        case SKILLS:
            break;
    }
}
