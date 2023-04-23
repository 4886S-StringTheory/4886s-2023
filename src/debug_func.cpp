#include "../include/main.h"

void debug_func(void) {
    while (1) {
        if (BTN_UP.PRESSED) {
            drive_straight(100, 48, 24);
        }
        if (BTN_R1.PRESSED) {
            drive_turn(90, WHEEL_TO_WHEEL_DIST / 2.0, 24, 24, false);
        }
        if (BTN_R2.PRESSED) {
            drive_turn(90, WHEEL_TO_WHEEL_DIST / 2.0, 24, 24, true);
        }
        if (BTN_L1.PRESSED) {
            drive_turn(-90, WHEEL_TO_WHEEL_DIST / 2.0, 24, 24, false);
        }
        if (BTN_L2.PRESSED) {
            drive_turn(-90, WHEEL_TO_WHEEL_DIST / 2.0, 24, 24, true);
        }
        if (BTN_B.PRESSED) {
            drive_turn(20 * 360, WHEEL_TO_WHEEL_DIST / 2.0, 36, 24, true);
        }

        wait(20, msec);
    }
}
