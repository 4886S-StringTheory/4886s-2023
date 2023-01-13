#include "../include/main.h"

// heavily customized - no need for standardization
void debug_test(void) {
    B_SCRN.clearScreen();
    B_SCRN.setFillColor("#000000");
    double vel = 0;
    while (true) {
        vel += (LEFT_STICK_Y / (127.0)) * 6 / 2;
        printf("help: %f\n", (LEFT_STICK_Y / (127.0)) / 5);
        printf("vel: %f\n", vel);
        printf("masterd: %.1ld\n", LEFT_STICK_Y);
        if (vel > 12) vel = 12;
        if (vel < -12) vel = -12;
        flywheel.spin(fwd, vel, voltageUnits::volt);

        B_SCRN.printAt(0, CHAR_HI * 1, "temp (C): %f", flywheel.temperature(TMP_C));
        B_SCRN.printAt(0, CHAR_HI * 2, "volts: %f", flywheel.voltage());
        B_SCRN.printAt(0, CHAR_HI * 3, "rpm: %f", flywheel.velocity(velocityUnits::rpm) * 6);
        B_SCRN.printAt(0, CHAR_HI * 4, "efficiency: %f", flywheel.efficiency());
        B_SCRN.printAt(0, CHAR_HI * 5, "torque: %f", flywheel.torque());

        printf("temp (C): %f", flywheel.temperature(TMP_C));
        printf("volts: %f", flywheel.voltage());
        printf("rpm: %f", flywheel.velocity(velocityUnits::rpm) * 6);
        printf("efficiency: %f", flywheel.efficiency());
        printf("torque: %f", flywheel.torque());

        wait(500, msec);
    }
}