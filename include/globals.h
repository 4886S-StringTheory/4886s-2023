// Motor gearings
#define DRIVE_GEARING TRB_MTR
#define FLYWHEEL_GEARING TRB_MTR
#define INTAKE_GEARING SPD_MTR
#define ROLLER_GEARING SPD_MTR

// Control
#define SENSITIVITY 0.75
extern int control_mode;
extern float drive_speed;

// Autonomous
extern int auton_mode;
extern const char *control_types[6];
extern const char *auton_types[4];