// Gearings
#define DRIVE_GEARING (GEAR_48 / GEAR_72)
#define DRIVE_IN_REV (DRIVE_GEARING * PI * TRACT_WHEEL_DIAM)

// Motor inserts
#define DRIVE_INSERT TRB_INSERT
#define FLYWHEEL_INSERT TRB_INSERT
#define INTAKE_INSERT SPD_INSERT
#define ROLLER_INSERT SPD_INSERT

// Autonmous modes
#define AWP 0
#define HALF_AWP_L 1
#define HALF_AWP_R 2
#define ROLLER 3

// Control modes
#define TNK_STD 0
#define OSA_STD 1
#define TSA_STD 2
#define TNK_REV 3
#define OSA_REV 4
#define TSA_REV 5

// Control
#define SENSITIVITY 0.75
extern int control_mode;
extern float drive_speed;

// Autonomous
extern int auton_mode;
extern const char *control_types[6];
extern const char *auton_types[4];