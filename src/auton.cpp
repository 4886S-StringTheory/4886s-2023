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
            roller.setVelocity(100, PCT_PCT);
//            flywheel.spin(DIR_FWD, 12, VLT_VLT);
            drive_straight(16, 48, 24);
//            flywheel.spin(DIR_FWD, 10, VLT_VLT);
            wait(1000, msec);
            roller.spinFor(DIR_FWD, 3, ROT_REV, true);
            wait(500, msec);
            roller.spinFor(DIR_FWD, 3, ROT_REV, true);

            // Roller
            drive_turn(-70, WHEEL_TO_WHEEL_DIST / 2.0, 36, 24);
            drive_straight(-25, 36, 24);
            drive_turn(54, WHEEL_TO_WHEEL_DIST / 2.0, 12, 12);
            drive_straight(-8.5, 12, 24);
            drive_l.spin(DIR_FWD, -20, VEL_PCT);
            drive_r.spin(DIR_FWD, -20, VEL_PCT);
            drive_l.setMaxTorque(20, PCT_PCT);
            drive_r.setMaxTorque(20, PCT_PCT);
            roller.spinFor(DIR_FWD, 3, ROT_REV, true);

            // Intake 3
            drive_straight(3, 12, 12);
            drive_turn(-45, WHEEL_TO_WHEEL_DIST, 36, 24);
            roller.spin(DIR_FWD, -12, VLT_VLT);
            drive_straight(60, 28, 24);

            // Fire 3
            drive_turn(90, WHEEL_TO_WHEEL_DIST / 2.0, 24, 24);
            for (int i = 0; i < 3; i++) {
                roller.spinFor(DIR_FWD, 3, ROT_REV, true);
                wait(1000, msec);
            }

            break;
        case HALF_AWP_R:
            break;
        case ROLLER:
            break;
        case SKILLS:
            break;
    }
}
