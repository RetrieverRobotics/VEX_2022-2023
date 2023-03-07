/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// FlyWheel             motor_group   3, 2            
// intake               motor         11              
// RightDrive           motor_group   6, 7            
// LeftDrive            motor_group   17, 16          
// Roller               motor         12              
// Indexer              motor         13              
// LimitSwitchA         limit         A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
int quadrant=0;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
int  x1Start=10, x2Start= 240, y1Start= 10, y2Start= 120, width= 230,  height= 110;   
 //Draw "buttons"   
    Brain.Screen.drawRectangle(x1Start,y1Start,width,height,color::green);
    Brain.Screen.printAt(x1Start+80,y1Start+30,"Roll and Push");   
    Brain.Screen.drawRectangle(x2Start,y1Start,width,height,color::blue);
    Brain.Screen.printAt(x2Start+80,y1Start+30,"Roll");   
    Brain.Screen.drawRectangle(x1Start,y2Start,width,height,color::red);
    Brain.Screen.printAt(x1Start+80,y2Start+30,"Nothing");   
    Brain.Screen.drawRectangle(x2Start,y2Start,width,height,color::yellow);
    Brain.Screen.printAt(x2Start+80,y2Start+30,"Nothing");   
      
    
 //Create an infinite loop
    while(true){
    //Once the screen is pressing figure out which button was pressed
        if(Brain.Screen.pressing()){ //if there is a Brain Press, check which quadrant
            if(Brain.Screen.yPosition() < y2Start&& Brain.Screen.xPosition()< x2Start){
                quadrant= 1;    //If it is set, set the quadrant to 1.
                break;          //Exit out of the infinite loop
               
            }    
            else if(Brain.Screen.yPosition() <=y2Start&& Brain.Screen.xPosition() >= x2Start){
                quadrant = 2;   //then it must be on the right side, so set the quadrant to 2. 
                break;          //Exit out of the infinite loop               
            }
            else if(Brain.Screen.yPosition() >=y2Start&& Brain.Screen.xPosition() < x2Start){
                quadrant = 3;   //If it is, set the quadrant to 3. 
                break;          //Exit out of the infinite loop               
            }
            else{
                quadrant=4;     //....then it must be on the right side, so set the quadrant to 4.
                break;          // Exit out of the infinite loop
            }
        }          
    }
    //Transition to running the program
    Brain.Screen.clearScreen();
    Brain.Screen.print("Program selected: ");
    Brain.Screen.print(quadrant);
    task::sleep(1000);
    Brain.Screen.newLine();
    Brain.Screen.print("Press screen again to be ready to run!");
    while(!Brain.Screen.pressing()){} 
    Brain.Screen.clearScreen();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  Roller.setVelocity(65,percent);
  LeftDrive.setVelocity(65,percent);
  RightDrive.setVelocity(65,percent);

  switch(quadrant){
    case 1: Brain.Screen.printAt(1,40,"Running Roll and Push");
    //This auton is just for scoring color roller

    //robot starts on roller and drives forward a little bit
    LeftDrive.spinFor(forward,0.5, turns,false);
    RightDrive.spinFor(forward,0.5, turns);

    //roller turns color roller
    Roller.spinFor(reverse,0.5,turns);

    //back up from roller
    LeftDrive.spinFor(forward,1, turns,false);
    RightDrive.spinFor(forward,1, turns);
    //Turn 90 degrees facing our color basket
    LeftDrive.spinFor(reverse,1.5, turns,false);
    RightDrive.spinFor(forward,1.5, turns);

    //Robot drives forward and pushes disks in goal
    LeftDrive.spinFor(forward,8, turns,false);
    RightDrive.spinFor(forward,8, turns);

    break;
case 2: Brain.Screen.printAt(1,40,"Running Roll");
    //This auton is for scoring color roller and pushing disks in goal

    //robot starts on roller and drives forward a little bit
    LeftDrive.spinFor(forward,0.5, turns,false);
    RightDrive.spinFor(forward,0.5, turns);

    //roller turns color roller
    Roller.spinFor(reverse,0.5,turns);

    //back up from roller
    LeftDrive.spinFor(forward,1, turns,false);
    RightDrive.spinFor(forward,1, turns);
    break;

  default: Brain.Screen.print("Invalid Input!!!!");
    break; 
  }

  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  intake.setVelocity(80,percent);
  Roller.setVelocity(65,percent);
  Indexer.setVelocity(80,percent);
  Indexer.setStopping(hold);
  FlyWheel.setVelocity(100,percent);// 100 percent should shoot from 2-3 tiles away
  bool indexer_load = false;
  float speed = 1;//varible that controlers the speed of drivetrain


  while (1) {

    if (Controller1.ButtonA.pressing()){
      //FlyWheel.setVelocity(100,percent);
      speed = 1; //100 percent over all drivetrain speed
    }
    else if(Controller1.ButtonY.pressing()){// haven't checked 80 percent yet
      //FlyWheel.setVelocity(80,percent);
      speed = 0.7;//70 percent over all drivetrain speed
    }

    if(Controller1.ButtonUp.pressing()&&indexer_load == false){
      //spins Indexer until it hits the limit switch witch means its  ready to load
      if (LimitSwitchA.pressing()){
        Indexer.stop(hold);
        indexer_load=true;
      }
      else{
        Indexer.spin(forward); 
      }
    }
    else if (Controller1.ButtonUp.pressing()&&indexer_load == true) {
      Indexer.spinFor(forward,1,turns); //resets the indexer to the top
      indexer_load = false;
    }

    //Sets the drivetrain to work with the Controller
    LeftDrive.spin(vex::directionType::rev, speed*Controller1.Axis3.position(), vex::velocityUnits::pct);
    RightDrive.spin(vex::directionType::rev, speed*Controller1.Axis2.position(), vex::velocityUnits::pct);

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
