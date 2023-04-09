#include "../include/main.h"

using namespace vex;

// Core elements
brain Brain;
controller master;

// All perpetrators of motion
// Bad Ports: 13
motor drive_rf = motor(PORT1, DRIVE_INSERT, false);
motor drive_rb = motor(PORT2, DRIVE_INSERT, false);
motor drive_lf = motor(PORT3, DRIVE_INSERT, true);
motor drive_lb = motor(PORT4, DRIVE_INSERT, true);
motor roller_r = motor(PORT16, ROLLER_INSERT, false);
motor roller_l = motor(PORT15, ROLLER_INSERT, false);
motor flywheel_top = motor(PORT19, FLYWHEEL_INSERT, false);
motor flywheel_low = motor(PORT18, FLYWHEEL_INSERT, true);
digital_out expansion = digital_out(PORTA);
digital_out flap = digital_out(PORTB);

// Signaures for vision
vision::signature REAR_RED_GOAL = vision::signature(0, 0, 0, 0, 0, 0, 0, 0, 0);
vision::signature REAR_BLUE_GOAL = vision::signature(0, 0, 0, 0, 0, 0, 0, 0, 0);
vision::signature REAR_DISC = vision::signature(0, 0, 0, 0, 0, 0, 0, 0, 0);
vision::signature FRONT_RED_GOAL = vision::signature(0, 0, 0, 0, 0, 0, 0, 0, 0);
vision::signature FRONT_BLUE_GOAL = vision::signature(0, 0, 0, 0, 0, 0, 0, 0, 0);
vision::signature FRONT_DISC = vision::signature(0, 0, 0, 0, 0, 0, 0, 0, 0);

// Sensors
inertial inrtl = inertial(PORT17);
rotation fly_rot = rotation(PORT10, true);
vision rear_optics = vision(PORT11, 0, REAR_RED_GOAL, REAR_BLUE_GOAL, REAR_DISC);
vision front_optics = vision(PORT12, 0, FRONT_RED_GOAL, FRONT_BLUE_GOAL, FRONT_DISC);

// Motor groups
motor_group drive_r (drive_rf, drive_rb);
motor_group drive_l (drive_lf, drive_lb);
motor_group flywheel (flywheel_top, flywheel_low);
motor_group roller (roller_r, roller_l);

timer sands_of_time;