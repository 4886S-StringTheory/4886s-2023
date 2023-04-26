#include "../include/main.h"

// Control
int control_mode = TSA_STD;
float drive_speed = 1.0;

// Autonomous
int auton_mode = AWP;
float current_heading = 0;
float fly_rpm = 2000;
bool fly_pid_enabled = false;

// Selection
const char *control_types[6] = {"tank std", "osa std", "tsa std",

                                "tank rev", "osa rev", "tsa rev"};
const char *auton_types[4] = {"awp", "half awp l", "half awp r", "roller"};
