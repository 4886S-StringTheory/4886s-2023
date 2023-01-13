#include "../include/main.h"

void autonomous(void) {
  /*
  switch (auton_mode) {
    case AWP:
      //tmp
      break;
    case HALF_AWP_L:
      //tmp
      break;
    case HALF_AWP_R:
      //tmp
      break;
    case ROLLER:
      wait(1000, msec);
      master.rumble(".-.");
      //flywheel.stop(brakeType::brake);
      wait(1000, sec);
      //flywheel.spin(DIR_FWD, 12, volt);
      drive_l.spinFor(DIR_FWD, -1 / DRIVE_REV_IN, ROT_REV, false);
      //drive_r.spinFor(DIR_FWD, -1 / DRIVE_REV_IN, ROT_REV, true);
      //roller.spinFor(DIR_FWD, .25, rev, true);
      master.rumble("..");
      break;
  }
  */
  wait(1000, msec);
    master.rumble(".-.");
    //flywheel.stop(brakeType::brake);
    wait(1000, msec);
    //flywheel.spin(DIR_FWD, 12, volt);
    drive_l.spinFor(DIR_FWD, -1 / DRIVE_REV_IN, ROT_REV, false);
    drive_r.spinFor(DIR_FWD, -1 / DRIVE_REV_IN, ROT_REV, true);
    roller.spinFor(DIR_FWD, .25, rev, true);
    master.rumble("..");
}
