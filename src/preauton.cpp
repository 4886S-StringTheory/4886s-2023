#include "../include/main.h"

void pre_auton(void) {
    C_SCREEN.clearScreen();
    C_SCREEN.setCursor(1, 2);
    C_SCREEN.print("%s", control_types[control_mode]);
    C_SCREEN.setCursor(2, 2);
    C_SCREEN.print("%s", auton_types[auton_mode]);  

    while (true) {
        if (BTN_A.pressing()) break;   // end condition
        
        // Cycle control modes
        if (rising_edge(BTN_UP.pressing())) {
            control_mode++;
            if (control_mode > TSA_REV) control_mode = TNK_STD; 
            C_SCREEN.setCursor(1, 2);
            C_SCREEN.clearLine();
            C_SCREEN.print("%s", control_types[control_mode]);
        }
        // Cycle autonomous
        if (rising_edge(BTN_RIGHT.pressing())) {
            auton_mode++;
            if (auton_mode > ROLLER) auton_mode = AWP;
            C_SCREEN.setCursor(2, 2);
            C_SCREEN.clearLine();
            C_SCREEN.print("%s", auton_types[auton_mode]);
        }
    }
    C_SCREEN.clearScreen();
    wait(10, msec);

    return;
} // 61 lines