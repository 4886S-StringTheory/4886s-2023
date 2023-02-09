float pid(float setpoint, float current_value, float *sum, float *prev_error, double constants[3]);
void pid_move(float dist, float max_vel, float accel_rate, bool decel);
void fly_pid(float rpm, char competition_state);

bool within_range(double value, double base, double range);
float stop_dist(float current_vel, float accel, float target_vel);

int b_scrn_hrzside(void);
int b_scrn_vrtside(void);
int *side_pressed(void);