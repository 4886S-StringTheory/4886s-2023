#include "../include/main.h"

using namespace vex;

// Core elements
brain Brain;
controller master;

// All perpetrators of motion
motor drive_rf = motor(PORT1, DRIVE_GEARING, false);
motor drive_rb = motor(PORT2, DRIVE_GEARING, false);
motor drive_lf = motor(PORT3, DRIVE_GEARING, true);
motor drive_lb = motor(PORT4, DRIVE_GEARING, true);
motor flywheel = motor(PORT5, FLYWHEEL_GEARING, false);
motor roller = motor(PORT20, ROLLER_GEARING, false);
motor intake = motor(PORT11, INTAKE_GEARING, true);

// Signaures for vision
vision::signature REAR_RED_GOAL = vision::signature(0, 0, 0, 0, 0, 0, 0, 0, 0);
vision::signature REAR_BLUE_GOAL = vision::signature(0, 0, 0, 0, 0, 0, 0, 0, 0);
vision::signature REAR_DISC = vision::signature(0, 0, 0, 0, 0, 0, 0, 0, 0);
vision::signature FRONT_RED_GOAL = vision::signature(0, 0, 0, 0, 0, 0, 0, 0, 0);
vision::signature FRONT_BLUE_GOAL = vision::signature(0, 0, 0, 0, 0, 0, 0, 0, 0);
vision::signature FRONT_DISC = vision::signature(0, 0, 0, 0, 0, 0, 0, 0, 0);

// Sensors
inertial inrtl = inertial(PORT18);
vision rear_optics = vision(PORT19, 0, REAR_RED_GOAL, REAR_BLUE_GOAL, REAR_DISC);
vision front_optics = vision(PORT20, 0, FRONT_RED_GOAL, FRONT_BLUE_GOAL, FRONT_DISC);

// Motor groups
motor_group drive_r (drive_rf, drive_rb);
motor_group drive_l (drive_lf, drive_lb);

timer sands_of_time;