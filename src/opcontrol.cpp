#include "../include/main.h"

void opcontrol(void) {
  sands_of_time.reset();

  while (true) {
    // Drive
    switch (control_mode) {
      case TNK_STD:
        drive_r.spin(DIR_FWD, RIGHT_STICK_Y * drive_speed * STICK_PCT, VEL_PCT);
        drive_l.spin(DIR_FWD, LEFT_STICK_Y * drive_speed * STICK_PCT, VEL_PCT);
        break;
      case OSA_STD:
        drive_r.spin(DIR_FWD, (LEFT_STICK_Y - LEFT_STICK_X * SENSITIVITY) * drive_speed * STICK_PCT, VEL_PCT);
        drive_l.spin(DIR_FWD, (LEFT_STICK_Y + LEFT_STICK_X * SENSITIVITY) * drive_speed * STICK_PCT, VEL_PCT);
        break;
      case TSA_STD: //def
        drive_r.spin(DIR_FWD, (LEFT_STICK_Y - RIGHT_STICK_X * SENSITIVITY) * drive_speed * STICK_PCT, VEL_PCT);
        drive_l.spin(DIR_FWD, (LEFT_STICK_Y + RIGHT_STICK_X * SENSITIVITY) * drive_speed * STICK_PCT, VEL_PCT);
        break;
      case TNK_REV:
        drive_l.spin(DIR_REV, RIGHT_STICK_Y * drive_speed * STICK_PCT, VEL_PCT);
        drive_r.spin(DIR_REV, LEFT_STICK_Y * drive_speed * STICK_PCT, VEL_PCT);
        break;
      case OSA_REV:
        drive_l.spin(DIR_REV, (LEFT_STICK_Y - LEFT_STICK_X * SENSITIVITY) * drive_speed * STICK_PCT, VEL_PCT);
        drive_r.spin(DIR_REV, (LEFT_STICK_Y + LEFT_STICK_X * SENSITIVITY) * drive_speed * STICK_PCT, VEL_PCT);
        break;
      case TSA_REV:
        drive_r.spin(DIR_REV, (LEFT_STICK_Y + RIGHT_STICK_X * SENSITIVITY) * drive_speed * STICK_PCT, VEL_PCT);
        drive_l.spin(DIR_REV, (LEFT_STICK_Y - RIGHT_STICK_X * SENSITIVITY) * drive_speed * STICK_PCT, VEL_PCT);
        break;
    }

    // Intake
    //intake.spin(DIR_FWD, (BTN_L2.pressing() - BTN_L1.pressing()) * BTN_PCT, VEL_PCT);

    // Roller
    roller.spin(DIR_FWD, (BTN_R2.pressing() - BTN_R1.pressing()) * .5 * BTN_PCT, VEL_PCT);

    // Flywheel
    indexer.set(BTN_L1.pressing());
    if (BTN_L2.pressing()) flywheel.spin(fwd, 12, voltageUnits::volt);
    else flywheel.spin(fwd, 12, volt);

    // Expansion
    if (BTN_Y.pressing()) expansion.set(1);

    // Timer - buzz w/ 20s left
    if (sands_of_time.time(sec) > 85 && sands_of_time.time(sec) < 85.2) master.rumble("....");

    wait(20, msec);

    // Break and enter testing mode
    if (b_scrn_vrtside() == 1 && b_scrn_hrzside() == 0) {
        debug_test();
        break;
    }
  }
}