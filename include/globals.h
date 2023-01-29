// Gearings
#define DRIVE_GEARING (GEAR_48 / GEAR_72)
#define DRIVE_REV__IN (DRIVE_GEARING * PI * TRACT_WHEEL_DIAM)

// Motor inserts
#define DRIVE_INSERT TRB_INSERT
#define FLYWHEEL_INSERT TRB_INSERT
#define ROLLER_INSERT TRB_INSERT

// Autonmous modes
#define AWP 0
#define HALF_AWP_L 1
#define HALF_AWP_R 2
#define ROLLER 3
#define SKILLS 4

// Control modes
#define TNK_STD 0
#define OSA_STD 1
#define TSA_STD 2
#define TNK_REV 3
#define OSA_REV 4
#define TSA_REV 5

// Flywheel speeds
#define LOW 2580
#define HIGH 2950

// Misc - defines
#define CHAR_HI 20
#define FLY_DEADBAND 20
#define FLY_VEL (flywheel.velocity(VEL_RPM) * 6)
#define DRIVE_VEL ((drive_r.velocity(VEL_RPM) + drive_l.velocity(VEL_RPM)) / 2)

// Control
#define SENSITIVITY 0.75
extern int control_mode;
extern float drive_speed;

// Autonomous
extern int auton_mode;

// Selection
extern const char *control_types[6];
extern const char *auton_types[4];