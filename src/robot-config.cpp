#include "../include/main.h"

using namespace vex;

// Core elements
brain Brain;
controller master;

// All perpetrators of motion
// Bad Ports: 13
motor drive_rf = motor(PORT11, DRIVE_INSERT, false);
motor drive_rm = motor(PORT13, DRIVE_INSERT, false);
motor drive_rb = motor(PORT15, DRIVE_INSERT, false);
motor drive_lf = motor(PORT14, DRIVE_INSERT, true);
motor drive_lm = motor(PORT13, DRIVE_INSERT, true);
motor drive_lb = motor(PORT12, DRIVE_INSERT, true);
motor flywheel = motor(PORT1, FLYWHEEL_INSERT, true);
motor roller = motor(PORT20, ROLLER_INSERT, true);
motor intake = motor(PORT13, INTAKE_INSERT, true);
digital_out expansion = digital_out(PORTA);
digital_out indexer = digital_out(PORTH);

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
motor_group drive_r (drive_rf, drive_rm, drive_rb);
motor_group drive_l (drive_lf, drive_lm, drive_lb);

timer sands_of_time;