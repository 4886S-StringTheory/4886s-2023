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
      master.rumble(".");
      drive_straight(-2, 10, 24);
      roller.spinFor(DIR_FWD, .35, ROT_REV, true);
      break;
    case SKILLS:
      sands_of_time.reset();

      // Shoot first 9
      flywheel.spin(DIR_FWD, HOPPER_VLT, VLT_VLT);
      wait(1200, msec);
      for (int i = 0; i < 9; i++) {
        indexer.set(1);
        flywheel.spin(DIR_FWD, 12, VLT_VLT);
        wait(300, msec);
        indexer.set(0);
        flywheel.spin(DIR_FWD, HOPPER_VLT, VLT_VLT);
        wait(300, msec);
      }
      flywheel.stop(brakeType::coast);

      // Hit rollers
      drive_turn(PI / 2, 18.5, 24, 24, false);
      drive_straight(-48, 48, 24);  
      break;
  }
}
