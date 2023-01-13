#include "../include/main.h"

void pre_auton(void) {
    B_SCRN.setFillColor("#0000aa");
    B_SCRN.clearScreen();
    B_SCRN.drawRectangle(0, B_SCRN_YMID, B_SCRN_XMID, B_SCRN_YMID);
    B_SCRN.printAt(B_SCRN_XMID - 200, (B_SCRN_HEIGHT * 3 / 4) - (CHAR_HI / 2), "debug_test()");
}