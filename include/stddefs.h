#ifndef _STDDEFS_H_
#define _STDDEFS_H_

// Important Numbers
#define PI 3.1415926535897932384626433832795

// Ratios
#define TRQ_INSERT gearSetting::ratio36_1
#define SPD_INSERT gearSetting::ratio18_1
#define TRB_INSERT gearSetting::ratio6_1

#define STICK_TRQ 1
#define STICK_SPD 2
#define STICK_TRB 6
#define BTN_TRQ 100
#define BTN_SPD 200
#define BTN_TRB 600
#define BTN_PCT 100

#define GEAR_12 12.0
#define GEAR_36 36.0
#define GEAR_48 48.0
#define GEAR_60 60.0
#define GEAR_72 72.0
#define GEAR_84 84.0

// Wheels
#define LRG_OMNI_DIAM 4
#define MED_OMNI_DIAM 3.25
#define SML_OMNI_DIAM 2.75
#define LRG_WHEEL_DIAM 5
#define MED_WHEEL_DIAM 4
#define SML_WHEEL_DIAM 2.75
#define TRACT_WHEEL_DIAM 3.25

#define LRG_OMNI_CIRC 13.1
#define MED_OMNI_CIRC 10.2
#define SML_OMNI_CIRC 8.6
#define LRG_WHEEL_CIRC 15.6
#define MED_WHEEL_CIRC 13.1
#define SML_WHEEL_CIRC 8.6
#define TRACT_WHEEL_CIRC 10.2

// Unit Conversions
#define FULL_ROT_DEG 360
#define HALF_ROT_DEG 180
#define QRTR_ROT_DEG 90

#define IN_CM 2.54
#define RAD_DEG 57.29578
#define SEC_MSEC 1000

// Controller Parts
// for use with controller named 'master'
#define LEFT_STICK_Y master.Axis3.value()
#define LEFT_STICK_X master.Axis4.value()
#define RIGHT_STICK_Y master.Axis2.value()
#define RIGHT_STICK_X master.Axis1.value()

#define BTN_L1 master.ButtonL1
#define BTN_L2 master.ButtonL2
#define BTN_R1 master.ButtonR1
#define BTN_R2 master.ButtonR2

#define BTN_UP master.ButtonUp
#define BTN_DOWN master.ButtonDown
#define BTN_LEFT master.ButtonLeft
#define BTN_RIGHT master.ButtonRight

#define BTN_X master.ButtonX
#define BTN_B master.ButtonB
#define BTN_Y master.ButtonY
#define BTN_A master.ButtonA

#define C_SCREEN master.Screen

// Brain Parts
// for use with brain named 'Brain'
#define BATTERY Brain.Battery
#define B_SCREEN Brain.Screen
#define B_SCRN_WIDTH 480
#define B_SCRN_HEIGHT 272
#define B_SCRN_XMID (B_SCRN_WIDTH / 2)
#define B_SCRN_YMID (B_SCRN_HEIGHT / 2)

// Sensor Values
// for use with inertial sensor named 'inrtl' and vision sensor names 'vis'
#define HEADING inrtl.heading()
#define ROTATION inrtl.rotation()
#define YAW inrtl.yaw()
#define ROLL inrtl.roll()
#define PITCH inrtl.pitch()

// Ports
#define PORTA Brain.ThreeWirePort.A
#define PORTB Brain.ThreeWirePort.B
#define PORTC Brain.ThreeWirePort.C
#define PORTD Brain.ThreeWirePort.D
#define PORTE Brain.ThreeWirePort.E
#define PORTF Brain.ThreeWirePort.F
#define PORTG Brain.ThreeWirePort.G
#define PORTH Brain.ThreeWirePort.H

// Shorthand parameters
#define DIR_FWD directionType::fwd
#define DIR_REV directionType::rev
#define VEL_PCT velocityUnits::pct
#define VEL_RPM velocityUnits::rpm
#define VEL_DPS velocityUnits::dps
#define ROT_DEG rotationUnits::deg
#define ROT_REV rotationUnits::rev
#define ROT_RAW rotationUnits::raw
#define PCT_PCT percentUnits::pct
#define TRQ_NM torqueUnits::Nm
#define TRQ_INLB torqueUnits::InLb
#define TIME_SEC timeUnits::sec
#define TIME_MSEC timeUnits::msec

#endif // _STDDEFS_H_