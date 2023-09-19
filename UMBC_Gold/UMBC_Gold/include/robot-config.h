using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor_group FlyWheel;
extern motor intake;
extern motor_group RightDrive;
extern motor_group LeftDrive;
extern motor Roller;
extern motor Indexer;
extern limit LimitSwitchA;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );