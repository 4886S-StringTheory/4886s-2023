int b_scrn_vrtside(void);
int b_scrn_side(char *argv);

void pid_move(float dist, float max_vel, float accel_rate, bool decel);
void fly_pid(float rpm, char competition_state);
bool within_range(double value, double base, double range);