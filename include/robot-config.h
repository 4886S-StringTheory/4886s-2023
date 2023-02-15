using namespace vex;

// Core elements
extern brain Brain;
extern controller master;

// Perpetrators of movement
extern motor drive_rf;
extern motor drive_rm;
extern motor drive_rb;
extern motor drive_lf;
extern motor drive_lm;
extern motor drive_lb;
extern motor flywheel_top;
extern motor flywheel_low;
extern motor intake;
extern motor roller_r;
extern motor roller_l;
extern digital_out expansion;
extern digital_out indexer;
extern rotation fly_rot;

// Vision signatures
extern vision::signature REAR_RED_GOAL;
extern vision::signature REAR_BLUE_GOAL;
extern vision::signature REAR_DISC;
extern vision::signature FRONT_RED_GOAL;
extern vision::signature FRONT_BLUE_GOAL;
extern vision::signature FRONT_DISC;

// Sensors
extern inertial inrtl;
extern vision rear_optics;
extern vision front_optics;

// Motor groups
extern motor_group drive_r;
extern motor_group drive_l;
extern motor_group flywheel;
extern motor_group roller;

extern timer sands_of_time;