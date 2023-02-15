#include "../include/main.h"

float pid(float setpoint, float current_value, float *sum, float *prev_error, double constants[3]) {
    float error = setpoint - current_value;
    *sum += error;
    *sum = 0;
    float deriv = error - *prev_error;
    *prev_error = error;

    // Debug
    printf("error: %.1f, kP: %.3f, integral: %.1f, kI: %.3f, deriv: %.1f, kD: %.3f\n", error, constants[0], *sum, constants[1], deriv, constants[2]);

    return (error * constants[0]) + (*sum * constants[1]) + (deriv * constants[2]);
}

void pid_move(float dist, float max_vel, float accel, bool do_decel) {
    float target_vel = DRIVE_VEL;
    float target_pos = DRIVE_POS;
    float start_pos = DRIVE_POS;
    float start_dir = HEADING;

    float sum = 0;
    float prev_error;

    // Outputs
    float pos_out;
    float dir_out;

    double tune[4] = {.1, 0, 0, .6};
    while (!within_range(start_pos + dist, DRIVE_POS, .25)) {
        float dist_traveled = DRIVE_POS - start_pos;
        float dist_to_targ = dist - dist_traveled;

        /*
        if (dist > 0) { // if moving forward
            printf("fwd - "); //dbg
            if (dist_to_targ <= stop_dist(target_vel, accel) && do_decel) { // check for decel
                printf("decel\n"); //dbg
                target_vel -= accel / 50.0;
            }
            else if (target_vel < max_vel) {    // check for accel
                printf("accel\n");
                target_vel += accel / 50.0; // divide by 50 because 50 Hz
                if (target_vel > max_vel) target_vel = max_vel;
            }
        }
        else if (dist < 0) {    // if moving backward
            printf("rev - "); //dbg
            if (dist_to_targ <= stop_dist(target_vel, accel) && do_decel) { // check for decel
                printf("decel\n"); //dbg
                target_vel += accel / 50.0;
            }
            else if (target_vel > -max_vel) {   // check for accel
                printf("accel\n"); //dbg
                target_vel -= accel / 50.0; // divide by 50 because 50 Hz
                printf("targ_vel: %.2f\n", target_vel);
            }
            else target_vel = max_vel;
        }
        else break;
        */

        if (stop_dist(target_vel, accel) >= dist_to_targ) {
            target_vel -= accel / 50.0;
            if (target_vel > abs(max_vel)) target_vel = max_vel;
        }
        else if (stop_dist(target_vel, accel) <= dist_to_targ ) {
            //target_vel +=
        }
        
        // Find output based on expected position
        target_pos += target_vel / 50;
        pos_out = target_vel + (target_pos - DRIVE_POS) * tune[3];

        dir_out = (start_dir - HEADING) * tune[0];

        drive_l.spin(DIR_FWD, pos_out + dir_out, VLT_VLT);
        drive_r.spin(DIR_FWD, pos_out - dir_out, VLT_VLT);

        wait(20, msec); // 50 Hz
    }
    printf("broken\n");
    if (do_decel) {
        drive_l.stop(brakeType::brake);
        drive_l.stop(brakeType::brake);
    }
    else {
        drive_l.stop(brakeType::coast);
        drive_r.stop(brakeType::coast);
    }
}

void pid_turn(float deg, float rpm, float accel) {
    //tmp
}

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
            dir_err = inrtl.rotation(ROT_DEG) - current_heading;
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
            dir_err = inrtl.rotation(ROT_DEG) - current_heading;
            vel_rpm = vel / DRIVE_REV__IN * 60;

            drive_r.spin(DIR_FWD, DRIVE_KP * r_pos_err - vel_rpm + DIR_KP * dir_err, VEL_RPM);
            drive_l.spin(DIR_FWD, DRIVE_KP * l_pos_err - vel_rpm - DIR_KP * dir_err, VEL_RPM);

            currentTimer += tickSpeed; // wait until tickSpeed milliseconds have
                                        // passed since last iteration of while loop
            while (sands_of_time.time(msec) < currentTimer) {
            }

        }
    }

}

void drive_turn(float radians, float outerRadius, float maxVel, float accel, bool reversed) {
    float vel_rpm;

    int innerRadius = outerRadius - WHEEL_TO_WHEEL_DIST;
    float radiusRatio = innerRadius / outerRadius;
    float vel = 0;
    float angleLeft;

    float pos = 0;
    float currLeft;
    float currRight;
    float LeftPosStart = drive_l.position(turns);
    float RightPosStart = drive_r.position(turns);
    int tickSpeed = 20;
    int currentTimer = sands_of_time.time(msec);
    int ticksPerSec = (1000 / tickSpeed);

    float l_dist_traveled;
    float r_dist_traveled;
    float r_pos_err;
    float l_pos_err;

    if (radians > 0 / RAD__DEG) { // turning right
        while (vel >= 0) {
            l_dist_traveled = drive_l.position(ROT_REV) - LeftPosStart;
            r_dist_traveled = drive_r.position(ROT_REV) - RightPosStart;

            angleLeft = (radians - inrtl.rotation(degrees) / RAD__DEG) - 0.1 * inrtl.gyroRate(zaxis, dps) / RAD__DEG; // no idea
            currLeft = l_dist_traveled * DRIVE_REV__IN;
            currRight = r_dist_traveled * DRIVE_REV__IN; /// this converts the code into inches

            if (stop_dist(vel, accel) >= angleLeft * outerRadius) {
                vel -= accel / ticksPerSec; // decel
            } else if (vel < maxVel) {
                vel += accel / ticksPerSec;
            } else {
                vel = maxVel;
            }
            pos += vel / ticksPerSec;

            if (inrtl.rotation(degrees) / RAD__DEG >= radians) {
                break;
            }

            r_pos_err = pos - currRight;
            l_pos_err = pos = currLeft;
            vel_rpm = vel / DRIVE_REV__IN * 60;

            if (!reversed) {
                drive_r.spin(DIR_FWD, DRIVE_KP * (pos * radiusRatio - currRight) + vel_rpm, VEL_RPM);
                drive_l.spin(DIR_FWD, DRIVE_KP * l_pos_err + vel_rpm * radiusRatio, VEL_RPM);
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
    else if (radians < inrtl.rotation(degrees) / RAD__DEG) {
        while (vel >= 0) {
            l_dist_traveled = drive_l.position(ROT_REV) - LeftPosStart;
            r_dist_traveled = drive_r.position(ROT_REV) - RightPosStart;

            currLeft = (l_dist_traveled) * DRIVE_REV__IN;
            currRight = (r_dist_traveled) * DRIVE_REV__IN; /// this converts the code into inches

            angleLeft =  -(radians - (inrtl.rotation(degrees)) / RAD__DEG) + 0.1 * inrtl.gyroRate(zaxis, dps) / RAD__DEG;

            if (angleLeft * outerRadius <= stop_dist(vel, accel)) {
                vel -= (float)accel / ticksPerSec; // decel
            } else if (vel < maxVel) {
                vel += accel  / ticksPerSec;
            } else {
                vel = maxVel;
            }
            pos += vel / ticksPerSec;

            if (inrtl.rotation(degrees) / RAD__DEG <= radians) {
                break;
            }
            if (reversed) {
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
    drive_l.stop(brakeType::coast);
    drive_r.stop(brakeType::coast);
    current_heading = radians * RAD__DEG;
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

// returns 0 for left, 1 for right, 2 for neither
int b_scrn_hrzside(void) {
    if (!B_SCRN.pressing()) return 0;
    if (B_SCRN.xPosition() < B_SCRN_X_MID) return LEFT;
    return RIGHT;
}

// returns 0 for top, 1 for bottom, 2 for neither
int b_scrn_vrtside(void) {
    if (!B_SCRN.pressing()) return 0;
    if (B_SCRN.yPosition() < B_SCRN_Y_MID) return UP;
    return DOWN;
}

int *side_pressed(void) {
    static int sides[2];
    sides[X] = b_scrn_hrzside();
    sides[Y] = b_scrn_vrtside();

    return sides;
}