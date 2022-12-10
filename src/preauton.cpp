#include "../include/main.h"

void pre_auton(void) {
    B_SCRN.clearScreen();
    B_SCRN.setCursor(1, 1);
    B_SCRN.print("%s", control_types[control_mode]);
    B_SCRN.setCursor(2, 1);
    B_SCRN.print("%s", auton_types[auton_mode]);  

    while (!(b_scrn_vrtside() == 1)) {        
        // Cycle control modes
        if (b_scrn_hrzside() == 0 && b_scrn_vrtside() == 0) {   // top left
            control_mode++;
            if (control_mode > TSA_REV) control_mode = TNK_STD; 
            B_SCRN.setCursor(1, 1);
            B_SCRN.clearLine();
            B_SCRN.print("%s", control_types[control_mode]);

            while (B_SCRN.pressing()) wait(20, msec);
        }
        // Cycle autonomous
        if (b_scrn_hrzside() == 1 && b_scrn_vrtside() == 0) {
            auton_mode++;
            if (auton_mode > ROLLER) auton_mode = AWP;
            B_SCRN.setCursor(2, 1);
            B_SCRN.clearLine();
            B_SCRN.print("%s", auton_types[auton_mode]);

            while (B_SCRN.pressing()) wait(20, msec);
        }
    }
    B_SCRN.setCursor(10, 10);
    B_SCRN.print("locked");
    control_mode = TSA_REV;     // tmp?
    return;
} // 61 lines