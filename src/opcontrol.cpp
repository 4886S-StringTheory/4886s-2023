#include "../include/main.h"

void opcontrol(void) {
  while (true) {
    C_SCREEN.print("DRIVER CONTROL");
    // Drive
    switch (control_mode) {
      case 0:     // tank std
        drive_r.spin(DIR_FWD, RIGHT_STICK_Y * drive_speed, VEL_PCT);
        drive_l.spin(DIR_FWD, LEFT_STICK_Y * drive_speed, VEL_PCT);
      case 1:     // osa std
        drive_r.spin(DIR_FWD, (LEFT_STICK_Y - LEFT_STICK_X * SENSITIVITY) * drive_speed, VEL_PCT);
        drive_l.spin(DIR_FWD, (LEFT_STICK_Y + LEFT_STICK_X * SENSITIVITY) * drive_speed, VEL_PCT);
      case 2:     // tsa std
        drive_r.spin(DIR_FWD, (LEFT_STICK_Y - RIGHT_STICK_X * SENSITIVITY) * drive_speed, VEL_PCT);
        drive_l.spin(DIR_FWD, (LEFT_STICK_Y + RIGHT_STICK_X * SENSITIVITY) * drive_speed, VEL_PCT);
      case 3:     // tank rev
        drive_l.spin(DIR_REV, RIGHT_STICK_Y * drive_speed, VEL_PCT);
        drive_r.spin(DIR_REV, LEFT_STICK_Y * drive_speed, VEL_PCT);
      case 4:     // osa rev
        drive_l.spin(DIR_REV, (LEFT_STICK_Y - LEFT_STICK_X * SENSITIVITY) * drive_speed, VEL_PCT);
        drive_r.spin(DIR_REV, (LEFT_STICK_Y + LEFT_STICK_X * SENSITIVITY) * drive_speed, VEL_PCT);
      case 5:     // tsa rev
        drive_l.spin(DIR_REV, (LEFT_STICK_Y - RIGHT_STICK_X * SENSITIVITY) * drive_speed, VEL_PCT);
        drive_r.spin(DIR_REV, (LEFT_STICK_Y + RIGHT_STICK_X * SENSITIVITY) * drive_speed, VEL_PCT);
    }

    // Intake
    intake.spin(DIR_FWD, (BTN_L2.pressing() - BTN_L1.pressing()) * BTN_PCT, VEL_PCT);

    // Roller
    roller.spin(DIR_FWD, BTN_R2.pressing() * BTN_PCT, VEL_PCT);

    wait(20, msec);
  }
}