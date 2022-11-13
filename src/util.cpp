#include "../include/main.h"

// rising edge detection - wip
bool rising_edge(int val) {
    //printf("val: %i\n", val);
    static int prev_val = val;  // value last cycle
    bool val_rising;
    val_rising = (val > prev_val);
    //printf("rising: %i\n", val_rising);

    prev_val = val;    // set up for next cycle
    //printf("prev_val: %i\n", prev_val);
    return val_rising;
}

// returns 0 for left, 1 for right, 2 for neither
int b_scrn_hrzside(void) {
    if (!B_SCREEN.pressing()) return 2;
    if (B_SCREEN.xPosition() < B_SCRN_XMID) return 0;
    return 1;
}

// returns 0 for top, 1 for bottom, 2 for neither
int b_scrn_vrtside(void) {
    if (!B_SCREEN.pressing()) return 2;
    if (B_SCREEN.yPosition() < B_SCRN_YMID) return 0;
    return 1;
}