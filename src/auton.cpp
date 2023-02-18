#include "../include/main.h"

void autonomous(void) {
  switch (auton_mode) {
    case AWP:
      //tmp
      break;
    case HALF_AWP_L:
      // Get roller a
      drive_straight(-2, 10, 24);
      roller.spinFor(DIR_FWD, .35, ROT_REV, true);
      // Path to firing spot
      drive_straight(6, 36, 24);
      drive_turn(PI / 4, WHEEL_TO_WHEEL_DIST / 2, 24, 24, true);
      drive_straight(59, 60, 24);
      drive_turn(7 * PI / 4 - 0.2, WHEEL_TO_WHEEL_DIST / 2, 24, 24, true);
      // Fire
      flywheel.spin(DIR_FWD, 9.7, VLT_VLT);
      wait(1800, msec);
      indexer.set(1);
      wait(500, msec);
      indexer.set(0);
      wait(1500, msec);
      indexer.set(1);
      // Stop
      wait(500, msec);
      flywheel.stop(brakeType::coast);
      indexer.set(0);
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
      flywheel.spin(DIR_FWD, 12, VLT_VLT);
      wait(500, msec);
      flywheel.spin(DIR_FWD, HOPPER_VLT, VLT_VLT);
      wait(8000, msec);
      for (int i = 0; i < 9; i++) {
        indexer.set(1);
        wait(300, msec);
        indexer.set(0);
        flywheel.spin(DIR_FWD, HOPPER_VLT, VLT_VLT);
        master.rumble(".");
        wait(1200, msec);
      }
      flywheel.stop(brakeType::coast);

      // Path to roller a
      current_heading = inrtl.rotation();
      drive_straight(12, 48, 36);
      drive_turn(PI / 2, WHEEL_TO_WHEEL_DIST, 24, 24, true);
      drive_straight(-48, 72, 36);
      drive_turn(2 * PI - .5, WHEEL_TO_WHEEL_DIST / 2, 24, 24, true);
      drive_straight(-6, 20, 24);
      // Get roller a
      drive_r.spin(DIR_FWD, -15, VEL_PCT);
      drive_l.spin(DIR_FWD, -15, VEL_PCT);
      drive_r.setMaxTorque(15, pct);
      drive_l.setMaxTorque(15, pct);
      wait(250, msec);
      roller.spinFor(DIR_FWD, -0.8, ROT_REV, true);
      drive_r.stop(brakeType::coast);
      drive_l.stop(brakeType::coast);
      drive_r.setMaxTorque(100, pct);
      drive_l.setMaxTorque(100, pct);
      // Path to roller b
      drive_straight(24, 36, 24);
      drive_turn(5 * PI / 2, WHEEL_TO_WHEEL_DIST / 2, 24, 24, true);
      drive_straight(-18, 36, 18);
      drive_r.spin(DIR_FWD, -15, VEL_PCT);
      drive_l.spin(DIR_FWD, -15, VEL_PCT);
      drive_r.setMaxTorque(15, pct);
      drive_l.setMaxTorque(15, pct);
      wait(250, msec);
      roller.spinFor(DIR_FWD, -0.8, ROT_REV, true);
      drive_r.stop(brakeType::coast);
      drive_l.stop(brakeType::coast);
      drive_r.setMaxTorque(100, pct);
      drive_l.setMaxTorque(100, pct);
      // Path to roller c
      drive_straight(14, 36, 24);
      drive_turn(17 * PI / 4 - .4, WHEEL_TO_WHEEL_DIST / 2, 24, 24, true);
      drive_straight(94, 72, 36);
      drive_turn(18 * PI / 4 - .1, WHEEL_TO_WHEEL_DIST / 2, 24, 24, true);
      drive_straight(44, 48, 36);
      drive_turn(20 * PI / 4, WHEEL_TO_WHEEL_DIST / 2, 24, 24, true);
      drive_straight(-16, 36, 24);
      // Get roller c
      drive_r.spin(DIR_FWD, -15, VEL_PCT);
      drive_l.spin(DIR_FWD, -15, VEL_PCT);
      drive_r.setMaxTorque(15, pct);
      drive_l.setMaxTorque(15, pct);
      wait(250, msec);
      roller.spinFor(DIR_FWD, -0.8, ROT_REV, true);
      drive_r.stop(brakeType::coast);
      drive_l.stop(brakeType::coast);
      drive_r.setMaxTorque(100, pct);
      drive_l.setMaxTorque(100, pct);
      // Path to roller d
      drive_straight(18, 26, 24);
      drive_turn(26 * PI / 4, WHEEL_TO_WHEEL_DIST / 2, 24, 24, true);
      drive_straight(20, 36, 24);
      drive_turn(30 * PI / 4, WHEEL_TO_WHEEL_DIST / 2, 24, 24, true);
      drive_straight(-5, 36, 24);
      // Get roller d
      drive_r.spin(DIR_FWD, -15, VEL_PCT);
      drive_l.spin(DIR_FWD, -15, VEL_PCT);
      drive_r.setMaxTorque(15, pct);
      drive_l.setMaxTorque(15, pct);
      wait(250, msec);
      roller.spinFor(DIR_FWD, -0.8, ROT_REV, true);
      drive_r.stop(brakeType::coast);
      drive_l.stop(brakeType::coast);
      drive_r.setMaxTorque(100, pct);
      drive_l.setMaxTorque(100, pct);
      // Path to expansion
      drive_straight(20, 36, 24);
      drive_turn(37 * PI / 4 - .2, WHEEL_TO_WHEEL_DIST / 2, 24, 24, true);
      // Expand
      expansion.set(1);
      drive_straight(-8, 24, 24);
      break;
  }
}
