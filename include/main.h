#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <thread>
#include <iostream>

#include "../../../../Library/Application Support/Code/User/globalStorage/vexrobotics.vexcode/sdk/cpp/V5/V5_20220726_10_00_00/vexv5/include/v5.h"
#include "../../../../Library/Application Support/Code/User/globalStorage/vexrobotics.vexcode/sdk/cpp/V5/V5_20220726_10_00_00/vexv5/include/vex_mevent.h"
#include "../../../../Library/Application Support/Code/User/globalStorage/vexrobotics.vexcode/sdk/cpp/V5/V5_20220726_10_00_00/vexv5/include/v5_vcs.h"

#include "robot-config.h"
#include "stddefs.h"
#include "globals.h"
#include "util.h"
#include "debug.h"

// Main function declarations
void pre_auton(void);
void autonomous(void);
void opcontrol(void);
