/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      8/5/2025, 9:14:16 AM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include <iostream>
using namespace vex;

// A global instance of competition
competition Competition;


controller Controller;


// define your global instances of motors and other devices here
motor LM (PORT14, ratio18_1, false); 
motor RM (PORT2, ratio18_1, true); 
motor intake(PORT9, ratio18_1, false); 

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
void driveTrain(int rspeed, int lspeed, int waitTime){
  RM.spin(forward, rspeed, pct );
  LM.spin(forward, lspeed, pct);
  wait(waitTime, msec);
}

void stopRobot(){
  RM.stop(brake);
  LM.stop(brake);
}

/*---------------------------------EDF------------------------------------------*/

void pre_auton(void) {

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
  LM.spin(fwd,12,volt);
  // ..........................................................................
  driveTrain(100, 200, 2120);
  wait(100, msec);
  driveTrain(20,0, 1000);


  stopRobot();

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
  while (1) {
    
    int lspeed = Controller.Axis3.position(pct);
    int rspeed = Controller.Axis2.position(pct);

    driveTrain(rspeed,lspeed,10);
    
    if (Controller.ButtonR1.pressing()){
      intake.spin(forward, 100, pct);
    }
    else if (Controller.ButtonR2.pressing()){
      intake.spin(reverse, 100, pct);
    }
    else {
      intake.stop(brake);
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  //std::cout<"start";
  //Controller.rumble("..");
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
