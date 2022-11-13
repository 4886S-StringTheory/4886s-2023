#include "../include/main.h"

void pre_auton(void) {
    B_SCREEN.clearScreen();
    B_SCREEN.setCursor(1, 1);
    B_SCREEN.print("%s", control_types[control_mode]);
    B_SCREEN.setCursor(2, 1);
    B_SCREEN.print("%s", auton_types[auton_mode]);  

    while (!(b_scrn_vrtside() == 1)) {        
        // Cycle control modes
        if (b_scrn_hrzside() == 0 && b_scrn_vrtside() == 0) {
            control_mode++;
            if (control_mode > TSA_REV) control_mode = TNK_STD; 
            B_SCREEN.setCursor(1, 1);
            B_SCREEN.clearLine();
            B_SCREEN.print("%s", control_types[control_mode]);
            printf("%s\n", control_types[control_mode]);

            while (B_SCREEN.pressing()) {
                wait(500, msec);
                break;
            }  // cycle every half second while pressed
        }
        // Cycle autonomous
        if (b_scrn_hrzside() == 1 && b_scrn_vrtside() == 0) {
            auton_mode++;
            if (auton_mode > ROLLER) auton_mode = AWP;
            B_SCREEN.setCursor(2, 1);
            B_SCREEN.clearLine();
            B_SCREEN.print("%s", auton_types[auton_mode]);

            while (B_SCREEN.pressing()) {
                wait(500, msec);
                break;
            }   // cycle every half second while pressed
        }
    }
    B_SCREEN.setCursor(10, 10);
    B_SCREEN.print("locked");
    return;
} // 61 lines