#include "../include/main.h"

void pre_auton(void) {
  bool auton_select = true;
  bool up = false;
  bool right = false;
  bool anti_up = up;
  bool anti_right = right;

  C_SCREEN.clearScreen();

  do {
    // end condition
    if (BTN_B.pressing()) auton_select = false;

    // selection
    if (BTN_UP.pressing()) up = true;      // toggle controle mode
    else if (BTN_RIGHT.pressing()) right = !right;
    
    // something approaching a rising edge detector
    if ((up != anti_up) && up == true) {
      control_mode++;
      if (control_mode > 3) control_mode = 0;

      // print drive type to controller screen
      C_SCREEN.clearScreen();
      C_SCREEN.setCursor(2, 2);
      wait(10, msec);
      C_SCREEN.print(control_mode);
    }

    if (right != anti_right){
      //tmp
    }

    anti_up = up;
    anti_right = right;
    up = false;
  } while (auton_select);

  C_SCREEN.clearScreen();
  wait(10, msec);
  
  return;
}