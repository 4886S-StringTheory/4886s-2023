#include "../include/main.h"

void autonomous(void) {
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
      drive_l.spinFor(DIR_FWD, -2 / DRIVE_REV__IN, ROT_REV, false);
      drive_r.spinFor(DIR_FWD, -2 / DRIVE_REV__IN, ROT_REV, true);
      roller.spinFor(DIR_FWD, .35, rev, true);
      break;
    case SKILLS:
      sands_of_time.reset();
      drive_l.spinFor(DIR_FWD, -2 / DRIVE_REV__IN, ROT_REV, false);
      drive_r.spinFor(DIR_FWD, -2 / DRIVE_REV__IN, ROT_REV, true);
      roller.spinFor(DIR_FWD, .75, rev, true);
      drive_l.spinFor(DIR_FWD, 3 / DRIVE_REV__IN, ROT_REV, false);
      drive_r.spinFor(DIR_FWD, 3 / DRIVE_REV__IN, ROT_REV, true);
      drive_r.spinFor(DIR_FWD, 0.53, ROT_REV, true);
      flywheel.spin(DIR_FWD, 10.78, VLT_VLT);
      wait(4000, msec);
      indexer.set(1);
      wait(500, msec);
      indexer.set(0);
      wait(2000, msec);
      indexer.set(1);
      wait(500, msec);
      
      drive_l.spinFor(DIR_FWD, 5 / DRIVE_REV__IN, ROT_REV, false);
      drive_r.spinFor(DIR_FWD, 5 / DRIVE_REV__IN, ROT_REV, true);

      drive_l.spinFor(DIR_FWD, 2, ROT_REV, true);
      wait(2000, msec);
      expansion.set(1);
  }
}
