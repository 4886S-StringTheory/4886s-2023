#include "../include/main.h"

// heavily customized - no need for standardization
void debug(void) {
    float sum = 0;
    float prev_error = 0;
    double kP = .035, kI = 0, kD = 0;
    int toggle_tuning_const = 0;
    double tune_constants[3] = {kP, kI, kD};
    while (1) {
        flywheel.spin(DIR_FWD, pid(2000, FLY_VEL, &sum, &prev_error, tune_constants), VLT_VLT);
        if (BTN_UP.PRESSED) {
            master.rumble(".");
            toggle_tuning_const = 0;
            C_SCREEN.clearScreen();
            C_SCREEN.setCursor(0, 0);
            C_SCREEN.print("kP");
        }
        if (BTN_RIGHT.PRESSED) {
            master.rumble(".");
            toggle_tuning_const = 1;
            C_SCREEN.clearScreen();
            C_SCREEN.setCursor(0, 0);
            C_SCREEN.print("kI");
        }
        if (BTN_DOWN.PRESSED) {
            master.rumble(".");
            toggle_tuning_const = 2;
            C_SCREEN.clearScreen();
            C_SCREEN.setCursor(0, 0);
            C_SCREEN.print("kD");
        }

        if (toggle_tuning_const == 0) {
            kP += LEFT_STICK_Y * .00001;
            if (BTN_Y.PRESSED) kP = 0.0;
        }
        if (toggle_tuning_const == 1) {
            kI += LEFT_STICK_Y * .00000001;
            if (BTN_Y.PRESSED) kI = 0;
        }
        if (toggle_tuning_const == 2) {
            kD += LEFT_STICK_Y * .00001;
            if (BTN_Y.PRESSED) kD = 0;
        }

        B_SCRN.clearScreen();
        B_SCRN.setCursor(1, 1);
        B_SCRN.print("pid: %f", pid(2000, FLY_VEL, &sum, &prev_error, tune_constants));
        B_SCRN.setCursor(2, 1);
        B_SCRN.print("kP: %lf", tune_constants[0]);
        B_SCRN.setCursor(3, 1);
        B_SCRN.print("kI: %.16f", tune_constants[1]);
        B_SCRN.setCursor(4, 1);
        B_SCRN.print("kD: %lf", tune_constants[2]);
        B_SCRN.setCursor(5, 1);
        B_SCRN.print("fly_vel: %.1f", FLY_VEL);

        tune_constants[0] = kP;
        tune_constants[1] = kI;
        tune_constants[2] = kD;

        printf("\n\nfly_vel: %f\n\n", FLY_VEL);

        wait (20, msec);

        // Break and enter speed control
        if (b_scrn_vrtside() == DOWN && b_scrn_hrzside() == LEFT) {
            speed_control();
            break;
        }
        if (b_scrn_vrtside() == DOWN && b_scrn_hrzside() == RIGHT) {
            tune_drive();
            break;
        }
    }
}

void speed_control(void) {
    int fly_rpm = 2400;
    float fly_vlt = 0;
    while (1) {
        fly_rpm += 5;

        if (FLY_VEL < fly_rpm) fly_vlt = 12;
        else fly_vlt = 7.2;

        flywheel.spin(DIR_FWD, fly_vlt, VLT_VLT);

        if (FLY_VEL >= fly_rpm) master.rumble(".");

        indexer.set(BTN_L1.pressing());

        B_SCRN.clearScreen();
        B_SCRN.setCursor(1,1);
        B_SCRN.print("fly_rpm: %i", fly_rpm);
    }
}

void tune_drive(void) {
    //tmp
}