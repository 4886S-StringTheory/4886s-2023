// Physical bits
#define DRIVE_GEARING (GEAR_48 / GEAR_72)
#define DRIVE_REV__IN (DRIVE_GEARING * PI * TRACT_WHEEL_DIAM)
#define WHEEL_TO_WHEEL_DIST 12

#define DRIVE_KP 0.6
#define DIR_KP 0.4

#define DRIVE_INSERT TRB_INSERT
#define FLYWHEEL_INSERT TRB_INSERT
#define ROLLER_INSERT SPD_INSERT

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

// Drive speeds
#define SLOW 0.5
#define FAST 1.0

// Flywheel speeds
#define LOW 2050
#define HIGH 2950

// Brain
#define X 0
#define Y 1
#define LEFT 1
#define UP 1
#define RIGHT 2
#define DOWN 2

// Auton consts
#define HOPPER_VLT 8

// Misc - defines
#define CHAR_HI 20
#define CHAR_WI 12
#define FLY_VEL fly_rot.velocity(VEL_RPM)
#define DRIVE_VEL ((drive_r.velocity(VEL_RPM) + drive_l.velocity(VEL_RPM)) / 2)
#define DRIVE_POS ((drive_r.position(ROT_REV) * DRIVE_REV__IN + drive_l.position(ROT_REV) * DRIVE_REV__IN) / 2)
#define DEADBAND 5

// Control
#define SENSITIVITY 0.7
extern int control_mode;
extern float drive_speed;

// Autonomous
extern int auton_mode;
extern float current_heading;

// Selection
extern const char *control_types[6];
extern const char *auton_types[4];