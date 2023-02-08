#include "../include/main.h"

void opcontrol(void) {
  int fly_speed = 0;
  float flywheel_speeds[2] = {LOW, HIGH};
  float fly_vlt;
  float prev_fly_vel = FLY_VEL;

  // better buzz
  bool reved = false;
  bool ready_to_rumble = true;

  sands_of_time.reset();

  while (true) {
    // Drive
    switch (control_mode) {
      case TNK_STD:
        drive_r.spin(DIR_FWD, RIGHT_STICK_Y * drive_speed * STICK__PCT, VEL_PCT);
        drive_l.spin(DIR_FWD, LEFT_STICK_Y * drive_speed * STICK__PCT, VEL_PCT);
        break;
      case OSA_STD:
        drive_r.spin(DIR_FWD, (LEFT_STICK_Y - LEFT_STICK_X * SENSITIVITY) * drive_speed * STICK__PCT, VEL_PCT);
        drive_l.spin(DIR_FWD, (LEFT_STICK_Y + LEFT_STICK_X * SENSITIVITY) * drive_speed * STICK__PCT, VEL_PCT);
        break;
      case TSA_STD: //def
        drive_r.spin(DIR_FWD, (LEFT_STICK_Y - RIGHT_STICK_X * SENSITIVITY) * drive_speed * STICK__PCT, VEL_PCT);
        drive_l.spin(DIR_FWD, (LEFT_STICK_Y + RIGHT_STICK_X * SENSITIVITY) * drive_speed * STICK__PCT, VEL_PCT);
        break;
      case TNK_REV:
        drive_l.spin(DIR_REV, RIGHT_STICK_Y * drive_speed * STICK__PCT, VEL_PCT);
        drive_r.spin(DIR_REV, LEFT_STICK_Y * drive_speed * STICK__PCT, VEL_PCT);
        break;
      case OSA_REV:
        drive_l.spin(DIR_REV, (LEFT_STICK_Y - LEFT_STICK_X * SENSITIVITY) * drive_speed * STICK__PCT, VEL_PCT);
        drive_r.spin(DIR_REV, (LEFT_STICK_Y + LEFT_STICK_X * SENSITIVITY) * drive_speed * STICK__PCT, VEL_PCT);
        break;
      case TSA_REV:
        drive_r.spin(DIR_REV, (LEFT_STICK_Y + RIGHT_STICK_X * SENSITIVITY) * drive_speed * STICK__PCT, VEL_PCT);
        drive_l.spin(DIR_REV, (LEFT_STICK_Y - RIGHT_STICK_X * SENSITIVITY) * drive_speed * STICK__PCT, VEL_PCT);
        break;
    }

    // Roller
    roller.spin(DIR_FWD, (BTN_R2.pressing() * .3 - BTN_R1.pressing()) * BTN__PCT, VEL_PCT);

    // Flywheel
    if (FLY_VEL < flywheel_speeds[fly_speed] && BTN_L2.pressing()) fly_vlt = 12;
    else if (BTN_L2.pressing()) fly_vlt = 7.2;
    else fly_vlt = 5;

    flywheel.spin(DIR_FWD, fly_vlt, VLT_VLT);

    if (FLY_VEL >= flywheel_speeds[fly_speed] && BTN_L2.pressing()) master.rumble(".");

    // if (within_range(FLY_VEL, flywheel_speeds[fly_speed], 25)) {
    //   if (ready_to_rumble) {
    //     ready_to_rumble = false;
    //     master.rumble("...");
    //   }
    // }
    // else ready_to_rumble = true;

    // Change flywheel speed
    if (BTN_DOWN.PRESSED) {
      fly_speed++;
      if (fly_speed > 1) fly_speed = 0;
      if (fly_speed == 0) master.rumble("-");
      else master.rumble("--");
    }

    // Fire
    indexer.set(BTN_L1.pressing());

    // Expansion
    if (BTN_Y.pressing()) expansion.set(1);

    // Timer - buzz w/ 20s left
    if (sands_of_time.time(sec) > 85 && sands_of_time.time(sec) < 85.2) master.rumble("....");

    wait(20, msec);

    // Break and enter testing mode
    if (b_scrn_vrtside() == DOWN && b_scrn_hrzside() == LEFT) {
        debug();
        break;
    }
  }
}