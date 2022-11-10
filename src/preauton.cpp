#include "../include/main.h"

void pre_auton(void) {
  bool auton_select = true;
  bool up = false;
  bool right = false;
  bool anti_up = up;
  bool anti_right = right;

  C_SCREEN.clearScreen();
  C_SCREEN.setCursor(1, 2);
  C_SCREEN.print("%s", control_types[control_mode]);
  C_SCREEN.setCursor(2, 2);
  C_SCREEN.print("%s", auton_types[auton_mode]);

  do {
    // end condition
    if (BTN_X.pressing()) auton_select = false;

    // selection
    if (BTN_UP.pressing()) up = true;      // toggle control mode
    if (BTN_RIGHT.pressing()) right = true;     // toggle auton program
    
    // btn_up rising edge
    if ((up != anti_up) && up == true) {
      // cycle control modes
      control_mode++;
      if (control_mode > 5) control_mode = 0;

      // print drive type to controller screen
      C_SCREEN.setCursor(1, 2);
      C_SCREEN.clearLine();
      wait(12, msec);     // wait, because if we don't things get funky
      C_SCREEN.print("%s", control_types[control_mode]);
    }

    // btn_right rising edge
    if ((right != anti_right) && right == true) {
      // cycle auton modes
      auton_mode++;
      if (auton_mode > 3) auton_mode = 0;

      // print auton modes to controller
      C_SCREEN.setCursor(2, 2);
      C_SCREEN.clearLine();
      wait(12, msec);     // wait for functioning controller screen
      C_SCREEN.print("%s", auton_types[auton_mode]);
    }

    // more stuff for rising edge detection
    anti_up = up;
    anti_right = right;
    up = false;
    right = false;
  } while (auton_select);

  C_SCREEN.clearScreen();
  wait(10, msec);
  
  return;
}