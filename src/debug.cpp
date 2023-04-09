#include "../include/main.h"

void debug(void) {
    B_SCRN.setPenColor("#f9f9f9");
    B_SCRN.setFillColor("#3c3c4d");
    B_SCRN.drawRectangle(0, 0, B_SCRN_X_MID, B_SCRN_Y_MID);                 // top left
    B_SCRN.drawRectangle(0, B_SCRN_Y_MID, B_SCRN_X_MID, B_SCRN_Y);          // bottom left
    B_SCRN.drawRectangle(B_SCRN_X_MID, 0, B_SCRN_X, B_SCRN_Y_MID);          // top right
    B_SCRN.drawRectangle(B_SCRN_X_MID, B_SCRN_Y_MID, B_SCRN_X, B_SCRN_Y);   // bottom right
    // Fill in text
    B_SCRN.printAt(B_SCRN_X_MID / 2 - CHAR_WI * (13 / 2), B_SCRN_Y_MID / 2 - CHAR_HI / 2, "tune_flywheel()");
    B_SCRN.printAt(B_SCRN_X_MID + B_SCRN_X_MID / 2 - CHAR_WI * (12 / 2), B_SCRN_Y_MID / 2 - CHAR_HI / 2, "tune_drive()");
    B_SCRN.printAt(B_SCRN_X_MID / 2 - CHAR_WI * (13 / 2), B_SCRN_Y_MID + B_SCRN_Y_MID / 2 - CHAR_HI / 2, "speed_control()");
    B_SCRN.printAt(B_SCRN_X_MID + B_SCRN_X_MID / 2 - CHAR_WI * (5 / 2), B_SCRN_Y_MID + B_SCRN_Y_MID / 2 - CHAR_HI / 2, "break");

    while (1) {
        // Break and enter functions
        if (side_pressed()[X] == RIGHT && side_pressed()[Y] == UP) {
            tune_drive();
        }

        if (side_pressed()[X] == LEFT && side_pressed()[Y] == UP) {
            tune_flywheel();
        }

        if (side_pressed()[X] == LEFT && side_pressed()[Y] == DOWN) {
            //speed_control();
        }

        // Back to opcontrol
        if (side_pressed()[Y] == DOWN && side_pressed()[Y]== RIGHT) {
            break;
        }

        wait (20, msec);
    }
}

void tune_flywheel(void) {
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
    }
}

void tune_drive(void) {
    // PID vars
    int max_vel = 12;
    int accel = 6;
    int inches = 180;

    float kP = 0.5;

    float target_vel = DRIVE_VEL;
    float target_pos = DRIVE_POS;
    float start_pos = DRIVE_POS;
    float start_dir = inrtl.angle(ROT_DEG);

    float sum = 0;
    float prev_error;

    // Outputs
    float pos_out;
    float dir_out;
    float dir_mod = .2;

    int toggle_const = 0;
    double tune[4] = {.1, 0, 0, .8};
    while (1) {
        // Select tuning var
        if (BTN_UP.PRESSED) {
            C_SCREEN.setCursor(1, 1);
            toggle_const = 0;
            master.rumble(".");
            C_SCREEN.clearScreen();
            C_SCREEN.print("DIR_KP");
        }
        if (BTN_RIGHT.PRESSED) {
            C_SCREEN.setCursor(1, 1);
            toggle_const = 1;
            master.rumble(".");
            C_SCREEN.clearScreen();
            C_SCREEN.print("dir_kI");
        }
        if (BTN_DOWN.PRESSED) {
            C_SCREEN.setCursor(1, 1);
            toggle_const = 2;
            master.rumble(".");
            C_SCREEN.clearScreen();
            C_SCREEN.print("dir_kD");
        }
        if (BTN_LEFT.PRESSED) {
            C_SCREEN.setCursor(1, 1);
            toggle_const = 3;
            master.rumble(".");
            C_SCREEN.clearScreen();
            C_SCREEN.print("kP");
        }

        tune[toggle_const] += LEFT_STICK_Y * .005;
        inches += RIGHT_STICK_Y * .01;

        // PID
        if (!within_range(start_pos + inches, DRIVE_POS, 1)) {
            // Accelerate
            if (inches - (DRIVE_POS - start_pos) <= stop_dist(target_vel, accel)) {
                target_vel -= accel / 50.0;
            }
            else if (target_vel < max_vel) {
                target_vel += accel / 50.0; // divide by 50 because 50 Hz
                if (target_vel > max_vel) target_vel = max_vel;
            }
            
            // Find output based on expected position
            target_pos += target_vel / 50;
            pos_out = target_vel + (target_pos - DRIVE_POS) * tune[3];

            if (DRIVE_POS >= start_pos + inches) pos_out = 0;

            dir_out = (start_dir - inrtl.rotation(ROT_DEG)) * tune[0];

            drive_l.spin(DIR_FWD, pos_out + dir_out, VLT_VLT);
            drive_r.spin(DIR_FWD, pos_out - dir_out, VLT_VLT);
        }
        else {
            target_vel = 0;
        }

        printf("kp: %.4f\n", tune[3]);
        printf("inches: %i\n", inches);
        printf("pos: %.3f\n", DRIVE_POS);
        printf("targ: %.2f\n", target_pos);
        printf("error: %.1f\n", target_pos - DRIVE_POS);
        printf("\n");
        wait(20, msec); // 50 Hz
    }
}

void speed_control(void) {
    /*
    int fly_rpm = 2400;
    float fly_vlt = 0;
    while (1) {
        fly_rpm += LEFT_STICK_Y;

        if (FLY_VEL < fly_rpm) fly_vlt = 12;
        else fly_vlt = 7.2;

        flywheel.spin(DIR_FWD, fly_vlt, VLT_VLT);

        if (FLY_VEL >= fly_rpm) master.rumble(".");

        indexer.set(BTN_L1.pressing());

        B_SCRN.clearScreen();
        B_SCRN.setCursor(1,1);
        B_SCRN.print("fly_rpm: %i", fly_rpm);
    }
    */
}

void measure_char(void) {
    // Print ruler
    for (int i = 0; i < B_SCRN_X; i++) {
        for (int j = 0; j < 20; j++) {
            if (j < 5 && i % 2 == 0) B_SCRN.drawPixel(i, j);
            if (j < 10 && i % 4 == 0) B_SCRN.drawPixel(i, j);
            if (i % 8 == 0) B_SCRN.drawPixel(i, j);
        }
    }

    // Print character
    B_SCRN.printAt(0, 21, "_|_|_|_|_|_|_|_|_WIWIWI");
}