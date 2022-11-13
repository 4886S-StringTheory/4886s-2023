#include "../include/main.h"

void opcontrol(void) {
  sands_of_time.reset();

  while (true) {
    C_SCREEN.print("DRIVER CONTROL");
    // Drive
    switch (control_mode) {
      case TNK_STD:
        printf("tnk_std\n");
        drive_r.spin(DIR_FWD, RIGHT_STICK_Y * drive_speed, VEL_PCT);
        drive_l.spin(DIR_FWD, LEFT_STICK_Y * drive_speed, VEL_PCT);
        break;
      case OSA_STD:
        printf("osa_std\n");
        drive_r.spin(DIR_FWD, (LEFT_STICK_Y - LEFT_STICK_X * SENSITIVITY) * drive_speed, VEL_PCT);
        drive_l.spin(DIR_FWD, (LEFT_STICK_Y + LEFT_STICK_X * SENSITIVITY) * drive_speed, VEL_PCT);
        break;
      case TSA_STD:
        printf("tsa_stdn\n");
        drive_r.spin(DIR_FWD, (LEFT_STICK_Y - RIGHT_STICK_X * SENSITIVITY) * drive_speed, VEL_PCT);
        drive_l.spin(DIR_FWD, (LEFT_STICK_Y + RIGHT_STICK_X * SENSITIVITY) * drive_speed, VEL_PCT);
        break;
      case TNK_REV:
        printf("tnk_rev\n");
        drive_l.spin(DIR_REV, RIGHT_STICK_Y * drive_speed, VEL_PCT);
        drive_r.spin(DIR_REV, LEFT_STICK_Y * drive_speed, VEL_PCT);
        break;
      case OSA_REV:
        printf("osa_rev\n");
        drive_l.spin(DIR_REV, (LEFT_STICK_Y - LEFT_STICK_X * SENSITIVITY) * drive_speed, VEL_PCT);
        drive_r.spin(DIR_REV, (LEFT_STICK_Y + LEFT_STICK_X * SENSITIVITY) * drive_speed, VEL_PCT);
        break;
      case TSA_REV:
        printf("tsa_rev\n");
        drive_l.spin(DIR_REV, (LEFT_STICK_Y - RIGHT_STICK_X * SENSITIVITY) * drive_speed, VEL_PCT);
        drive_r.spin(DIR_REV, (LEFT_STICK_Y + RIGHT_STICK_X * SENSITIVITY) * drive_speed, VEL_PCT);
        break;
    }

    // Intake
    intake.spin(DIR_FWD, (BTN_L2.pressing() - BTN_L1.pressing()) * BTN_PCT, VEL_PCT);

    // Roller
    roller.spin(DIR_FWD, BTN_R2.pressing() * BTN_PCT, VEL_PCT);

    // Timer
    if (sands_of_time.time(sec) > 95 && sands_of_time.time(sec) < 95.2) master.rumble("....");

    wait(20, msec);
  }
}