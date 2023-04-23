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

void debug_func(void) {
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
