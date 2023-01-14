#include "../include/main.h"

void pre_auton(void) {
    B_SCRN.setFillColor("#0000aa");
    B_SCRN.clearScreen();
    B_SCRN.drawRectangle(0, B_SCRN_Y_MID, B_SCRN_X_MID, B_SCRN_Y_MID);
    B_SCRN.printAt(B_SCRN_X_MID - 200, (B_SCRN_HEIGHT * 3 / 4) - (CHAR_HI / 2), "debug_test()");
}