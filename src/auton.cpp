#include "../include/main.h"

void autonomous(void) {
  switch (auton_mode) {
    case AWP:
      //tmp
    case HALF_AWP_L:
      //tmp
    case HALF_AWP_R:
      //tmp
    case ROLLER:
      drive_l.spinFor(DIR_FWD, -1 * DRIVE_IN_REV, ROT_REV, false);
      drive_r.spinFor(DIR_FWD, -1 * DRIVE_IN_REV, ROT_REV, true);
      roller.spinFor(DIR_FWD, .25, rev, true);
  }
}