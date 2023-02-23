using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor RDrive1;
extern motor RDrive2;
extern motor RDrive3;
extern motor RDrive4;
extern motor RDrive5;
extern motor LDrive1;
extern motor LDrive2;
extern motor LDrive3;
extern motor LDrive4;
extern motor LDrive5;
extern motor Intake;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );