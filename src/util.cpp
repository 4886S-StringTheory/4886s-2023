#include "../include/main.h"

// rising edge detection
bool rising_edge(int val) {
    static int prev_val = val;  // value last cycle
    bool val_rising = (val > prev_val);

    prev_val = val;    // set up for next cycle
    return val_rising;
}