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
            flywheel.spin(DIR_FWD, 12, VLT_VLT);
            drive_straight(16, 48, 24);
            flywheel.spin(DIR_FWD, 10, VLT_VLT);
            wait(1000, msec);
            roller.spinFor(DIR_FWD, 2.5, ROT_REV, true);
            wait(500, msec);
            roller.spinFor(DIR_FWD, 5, ROT_REV, true);
            drive_straight(-3, 48, 24);

            // Roller
            drive_turn(-80, WHEEL_TO_WHEEL_DIST / 2.0, 36, 24);
            drive_straight(-25, 36, 24);
            drive_turn(60, WHEEL_TO_WHEEL_DIST / 2.0, 12, 12);
            drive_straight(-8.5, 12, 24);
            drive_l.spin(DIR_FWD, -20, VEL_PCT);
            drive_r.spin(DIR_FWD, -20, VEL_PCT);
            // Set torque to 20%
            drive_l.setMaxTorque(20, PCT_PCT);
            drive_r.setMaxTorque(20, PCT_PCT);
            roller.spinFor(DIR_FWD, 3, ROT_REV, true);
            // Set torque to 100%
            drive_l.setMaxTorque(100, PCT_PCT);
            drive_r.setMaxTorque(100, PCT_PCT);
            drive_l.stop();
            drive_l.stop();


            // Intake 3
            drive_straight(5, 12, 12);
            drive_turn(-47, WHEEL_TO_WHEEL_DIST/ 2.0, 36, 24);
            roller.spin(DIR_FWD, -12, VLT_VLT);
            drive_straight(64, 28, 24);


            // Fire 3
            drive_turn(90, WHEEL_TO_WHEEL_DIST / 2.0, 12, 12);
            roller.spin(DIR_FWD, 0, VLT_VLT);
            wait(50, msec);
            for (int i = 0; i < 2; i++) {
                roller.spinFor(DIR_FWD, 2.5, ROT_REV, true);
                wait(1000, msec);
            }
            roller.spinFor(DIR_FWD, 3.5, ROT_REV, true);

            break;
        case HALF_AWP_R:

        //set Torque to 20%
        drive_l.setMaxTorque(20, PCT_PCT);
        drive_r.setMaxTorque(20, PCT_PCT);
        drive_r.spin(DIR_FWD, -20, VEL_PCT);
        drive_l.spin(DIR_FWD, -20, VEL_PCT);

        roller.spinFor(DIR_FWD, 2, ROT_REV, true);
        // Set torque to 100%
        drive_l.setMaxTorque(100, PCT_PCT);
        drive_r.setMaxTorque(100, PCT_PCT);

        drive_straight(4, 28, 24);
        drive_turn(53, WHEEL_TO_WHEEL_DIST / 2.0, 12, 12);
        drive_turn(-21, WHEEL_TO_WHEEL_DIST * 12.0, 100, 50, false);
        wait(2000, msec);
       // drive_turn(-10, WHEEL_TO_WHEEL_DIST * 13.5, 100, 50, false);
        drive_turn(-135, WHEEL_TO_WHEEL_DIST / 3.0, 36, 24);
        drive_straight(-4, 28, 24);
        
        //set Torque to 20%
         drive_l.setMaxTorque(20, PCT_PCT);
        drive_r.setMaxTorque(20, PCT_PCT);
        drive_r.spin(DIR_FWD, -20, VEL_PCT);
        drive_l.spin(DIR_FWD, -20, VEL_PCT);
        roller.spinFor(DIR_FWD, 3, ROT_REV, true);
        drive_r.spin(DIR_FWD, 0, VEL_PCT);
        drive_l.spin(DIR_FWD, 0, VEL_PCT);
        // Set torque to 100%
        drive_l.setMaxTorque(100, PCT_PCT);
        drive_r.setMaxTorque(100, PCT_PCT);





            break;
        case ROLLER:
            break;
        case SKILLS:
            break;
    }
}
