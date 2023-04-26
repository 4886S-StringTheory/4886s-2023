#include "../include/main.h"

void debug_funcAAA(void) {
    float fly_vel = 9.45;
    while (1) {
        flywheel.spin(DIR_FWD, fly_vel, VLT_VLT);
        fly_vel += LEFT_STICK_Y / 700.0;
        printf("fly_vel: %.2f\n", fly_vel);

        roller.spin(DIR_FWD, BTN__PCT * (BTN_L1.pressing() - BTN_R1.pressing()), VEL_PCT);

        wait(30, msec);
    }
}

void debug_funcBBB(void) {
    float MAX_VEL = 1000;
    float ACCEL = 60;

    float mov_trg = 0;
    float error = mov_trg - FLY_VEL;
    float kP = 0.6866;

    while (true) {
        error = mov_trg - FLY_VEL;
        if (mov_trg < MAX_VEL) mov_trg += ACCEL / 50;
        flywheel.spin(DIR_FWD, 9.5 + error * kP, VLT_VLT);

        kP += RIGHT_STICK_X / 3000.0;

        printf("kP: %f\n", kP);

        wait(20, msec);
    }

}

void debug_func(void) {
    float kP = 0.058;
    float kI = 0.0;
    float kD = 0.1;

    double tune_consts[3];

    float baseline = 9.7;
    float target_vel = 1000;
    float current_vel = FLY_VEL;
    float sum = 0;
    float prev_error = 0;

    float pid_adjustment;

    while (true) {
        tune_consts[0] = kP;
        tune_consts[1] = kI;
        tune_consts[2] = kD;
        current_vel = FLY_VEL;

        pid_adjustment = pid(target_vel, current_vel, &sum, &prev_error, tune_consts);
        if (pid_adjustment < baseline * -1) pid_adjustment = baseline * -1;

        printf("pid: %.2f\nbaseline: %.2f\ncurrent_vel: %.1f\n", pid_adjustment, baseline, current_vel);
        printf("target_vel: %.1f\n\n", target_vel);

        flywheel.spin(DIR_FWD, baseline + pid_adjustment, VLT_VLT);

        kD += LEFT_STICK_Y / 1500.0;
        baseline += RIGHT_STICK_X / 1000.0;
        target_vel += (BTN_RIGHT.pressing() - BTN_LEFT.pressing()) * 2.0;

        sum = 0;

        roller.spin(DIR_FWD, (BTN_L1.pressing() - BTN_R1.pressing()) * 12, VLT_VLT);

        wait(20, msec);
    }
}
