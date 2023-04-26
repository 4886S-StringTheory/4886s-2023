#include "../include/main.h"

float pid(float setpoint, float current_value, float *sum, float *prev_error, double constants[3]) {
    float error = setpoint - current_value;
    *sum += error;
    float deriv = error - *prev_error;
    *prev_error = error;

    // Debug
//    printf("error: %.1f\nkP: %.3f\nintegral: %.1f\nkI: %.3f\nderiv: %.1f\nkD: %.3f\n\n", error, constants[0], *sum, constants[1], deriv, constants[2]);

    return (error * constants[0]) + (*sum * constants[1]) + (deriv * constants[2]);
}

void pid_turn(float deg, float rpm, float accel) {
    //tmp
}

// 4886T PID
void drive_straight(float dist, float maxVel, float accel) {
    float vel_rpm;

    float vel = 0;
    float pos = 0;
    float currLeft;
    float currRight;
    float LeftPosStart = drive_l.position(turns);
    float RightPosStart = drive_r.position(turns);
    int tickSpeed = 20;
    int currentTimer = sands_of_time.time(msec);
    int ticksPerSec = (1000 / tickSpeed);

    float r_pos_err;
    float l_pos_err;
    float dir_err;

    if (dist > 0) {
        while (vel >= 0) {
            currLeft = (drive_l.position(ROT_REV) - LeftPosStart) *
                DRIVE_REV__IN;
            currRight = (drive_r.position(ROT_REV) - RightPosStart) *
                DRIVE_REV__IN; /// this converts the code into inches
            if (pos + stop_dist(vel, accel) >= dist) {
                vel -= accel / ticksPerSec; // decell
            } else if (vel < maxVel) {
                vel += accel / ticksPerSec;
            } else {
                vel = maxVel;
            }
            pos += vel / ticksPerSec;

            // error vals
            r_pos_err = pos - currRight;
            l_pos_err = pos - currLeft;
            dir_err = (inrtl.rotation(ROT_DEG)*GYRO_CORRECTION) - current_heading;
            vel_rpm = vel / DRIVE_REV__IN * 60;

            drive_r.spin(DIR_FWD, DRIVE_KP * r_pos_err + vel_rpm + DIR_KP * dir_err, VEL_RPM);
            drive_l.spin(DIR_FWD, DRIVE_KP * l_pos_err + vel_rpm + DIR_KP - dir_err, VEL_RPM);

            currentTimer += tickSpeed; // wait until tickSpeed milliseconds have
                                       // passed since last iteration of while loop
            while (sands_of_time.time(msec) < currentTimer) {
                // wait
            }
        }
    }
    else if (dist < 0) {
        while(vel >= 0){
            currLeft = (drive_l.position(turns) - LeftPosStart) *
                DRIVE_REV__IN;
            currRight = (drive_r.position(turns) - RightPosStart) *
                DRIVE_REV__IN; 
            if(pos - stop_dist(vel, accel) <= dist) {
                vel -= accel / ticksPerSec;
            } else if(vel < maxVel) {
                vel += accel / ticksPerSec;
            } else {
                vel = maxVel;
            }
            pos -= vel/ ticksPerSec;

            r_pos_err = pos - currRight;
            l_pos_err = pos - currLeft;
            dir_err = (inrtl.rotation(ROT_DEG)*GYRO_CORRECTION) - current_heading;
            vel_rpm = vel / DRIVE_REV__IN * 60;

            drive_r.spin(DIR_FWD, DRIVE_KP * r_pos_err - vel_rpm + DIR_KP * dir_err, VEL_RPM);
            drive_l.spin(DIR_FWD, DRIVE_KP * l_pos_err - vel_rpm - DIR_KP * dir_err, VEL_RPM);

            currentTimer += tickSpeed; // wait until tickSpeed milliseconds have
                                       // passed since last iteration of while loop
            while (sands_of_time.time(msec) < currentTimer) {
            }

        }
    }
    drive_r.stop(brakeType::coast);
    drive_l.stop(brakeType::coast);
}

// 4886T PID
void drive_turn(float deg, float outerRadius, float maxVel, float accel, bool reversed) {
    float radians = deg / RAD__DEG;
    radians = radians + current_heading / RAD__DEG;     // user turns based on relative position, not net pos

    float vel_rpm;

    int innerRadius = outerRadius - WHEEL_TO_WHEEL_DIST;
    float radiusRatio = innerRadius / outerRadius;
    float vel = 0;
    float angleLeft;

    float pos = 0;
    float currLeft;
    float currRight;
    float LeftPosStart = drive_l.position(ROT_REV);
    float RightPosStart = drive_r.position(ROT_REV);
    float tickSpeed = 20.0;
    int currentTimer = sands_of_time.time(msec);
    float ticksPerSec = (1000 / tickSpeed);

    float l_dist_traveled;
    float r_dist_traveled;
    float rad_remaining;

    if (radians > (inrtl.rotation(degrees)*GYRO_CORRECTION) / RAD__DEG) { // turning right
        printf("right\n");
        while (vel >= 0) {
            printf("corrected gyro: %f\n", inrtl.rotation(degrees)*GYRO_CORRECTION);
            printf("gyro: %f\n\n", inrtl.rotation(degrees));
            l_dist_traveled = drive_l.position(ROT_REV) - LeftPosStart;
            r_dist_traveled = drive_r.position(ROT_REV) - RightPosStart;
            rad_remaining = radians - (inrtl.rotation(degrees)*GYRO_CORRECTION) / RAD__DEG;

            angleLeft = rad_remaining;// - 0.1 * inrtl.gyroRate(zaxis, dps) / RAD__DEG; // correction for gyro inaccuracies?
            currLeft = l_dist_traveled * DRIVE_REV__IN;
            currRight = r_dist_traveled * DRIVE_REV__IN; /// this converts the code into inches

            if (stop_dist(vel, accel) >= angleLeft * outerRadius) {
                vel -= (float)accel / ticksPerSec; // decel
            } else if (vel < maxVel) {
                vel += (float)accel / ticksPerSec;
            } else {
                vel = maxVel;
            }
            pos += vel / ticksPerSec;

            if ((inrtl.rotation(degrees)*GYRO_CORRECTION) / RAD__DEG >= radians) {
                break;
            }

            vel_rpm = vel / DRIVE_REV__IN * 60;

            if (!reversed) {
                drive_r.spin(DIR_FWD, DRIVE_KP * (pos * radiusRatio - currRight) + vel_rpm, VEL_RPM);
                drive_l.spin(DIR_FWD, DRIVE_KP * (pos - currLeft) + vel_rpm * radiusRatio, VEL_RPM);
            }
            else {
                drive_r.spin(DIR_FWD, -DRIVE_KP * (pos + currRight) - vel_rpm, VEL_RPM);
                drive_l.spin(DIR_FWD, -DRIVE_KP * (pos * radiusRatio + currLeft) - vel_rpm * radiusRatio, VEL_RPM);
            }

            currentTimer += tickSpeed; // wait until tickSpeed milliseconds have
                                       // passed since last iteration of while loop
            while (sands_of_time.time(msec) < currentTimer) {
                // wait
            }
        }
    }
    else if (radians < (inrtl.rotation(degrees)*GYRO_CORRECTION) / RAD__DEG) {
        printf("left\n");
        while (vel >= 0) {
            //printf("targ: %.2f\n", radians);
            //printf("angle: %.2f\n", inrtl.rotation(ROT_DEG) / RAD__DEG);
            l_dist_traveled = drive_l.position(ROT_REV) - LeftPosStart;
            r_dist_traveled = drive_r.position(ROT_REV) - RightPosStart;
            rad_remaining = radians - inrtl.rotation(ROT_DEG) / RAD__DEG;

            currLeft = (l_dist_traveled) * DRIVE_REV__IN;
            currRight = (r_dist_traveled) * DRIVE_REV__IN; /// this converts the code into inches

            angleLeft =  -rad_remaining;// + 0.1 * inrtl.gyroRate(zaxis, dps) / RAD__DEG; // correctio for inrtl inaccuracies?

            if (angleLeft * outerRadius <= stop_dist(vel, accel)) {
                vel -= (float)accel / ticksPerSec; // decel
            } else if (vel < maxVel) {
                vel += (float)accel  / ticksPerSec;
            } else {
                vel = maxVel;
            }
            pos += vel / ticksPerSec;

            if ((inrtl.rotation(degrees)*GYRO_CORRECTION) / RAD__DEG <= radians) {
                break;
            }

            vel_rpm = vel / DRIVE_REV__IN * 60;

            if (reversed) {
                printf("!rev");
                drive_r.spin(DIR_FWD, -DRIVE_KP * (pos * radiusRatio + currRight) - vel_rpm * radiusRatio, VEL_RPM);
                drive_l.spin(DIR_FWD, -DRIVE_KP * (pos + currLeft) - vel_rpm, VEL_RPM);
            }
            else {
                drive_r.spin(DIR_FWD, DRIVE_KP * (pos - currRight) + vel_rpm, VEL_RPM);
                drive_l.spin(DIR_FWD, DRIVE_KP * (pos * radiusRatio - currLeft) + vel_rpm * radiusRatio, VEL_RPM);
            }

            currentTimer += tickSpeed; // wait until tickSpeed milliseconds have
                                       // passed since last iteration of while loop
            while (sands_of_time.time(msec) < currentTimer) {
                // wait
            }
        }
    }
    printf("exit drive_turn");
    drive_l.stop(brakeType::coast);
    drive_r.stop(brakeType::coast);
    current_heading = radians * RAD__DEG;
    printf("curr_head: %f\n", current_heading);
}

void press_back(bool toggle_pressing) {
    if (toggle_pressing) {
        drive_r.setMaxTorque(20, PCT_PCT);
        drive_l.setMaxTorque(20, PCT_PCT);
        drive_r.spin(DIR_FWD, -20, VEL_PCT);
        drive_l.spin(DIR_FWD, -20, VEL_PCT);
    }
    else {
        drive_r.setMaxTorque(100, PCT_PCT);
        drive_l.setMaxTorque(100, PCT_PCT);
        drive_r.spin(DIR_FWD, 0, VEL_PCT);
        drive_l.spin(DIR_FWD, 0, VEL_PCT);
    }
}

// Controls flywheel in auton, maybe. No idea what im doing
int auton_fly_pid(void) {
    float kP = 0.058;
    float kI = 0.0;
    float kD = 0.1;

    double tune_consts[3];

    float baseline = 9.7;
    float target_vel = fly_rpm;
    float current_vel = FLY_VEL;
    float sum = 0;
    float prev_error = 0;

    float pid_adjustment;

    while (fly_pid_enabled) {
        tune_consts[0] = kP;
        tune_consts[1] = kI;
        tune_consts[2] = kD;
        current_vel = FLY_VEL;

        pid_adjustment = pid(target_vel, current_vel, &sum, &prev_error, tune_consts);
        if (pid_adjustment < baseline * -1) pid_adjustment = baseline * -1;

        flywheel.spin(DIR_FWD, baseline + pid_adjustment, VLT_VLT);

        sum = 0;

        this_thread::sleep_for(20);
    } 
    flywheel.stop(brakeType::coast);
    return 0;
}

bool within_range(double value, double base, double range) {
    return ((value <= base + range) && (value >= base - range));
}

float stop_dist(float current_vel, float accel, float target_vel) {     // 4886T's code - learn physics
    return -(target_vel * target_vel - current_vel * current_vel) / (2 * accel); 
    //derived from physics equation V^2 = (V0)^2 +  2a(X-X0)
    //set V to targetVel and solve for X-X0,
    // = (targetVel^2 - currentVel^2)/2*accel
}

int *side_pressed(void) {
    static int sides[2];
    if (!B_SCRN.PRESSED) {
        sides[0] = 0;
        sides[1] = 0;
        return sides;
    }

    if (B_SCRN.xPosition() < B_SCRN_X_MID) sides[X] = LEFT;
    else sides[X] = RIGHT;

    if (B_SCRN.yPosition() < B_SCRN_Y_MID) sides[Y] = UP;
    else sides[Y] = DOWN;

    return sides;
}
