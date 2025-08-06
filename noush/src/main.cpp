/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      8/5/2025, 9:13:27 AM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
motor RM (PORT2, ratio18_1, true);
motor LM (PORT16, ratio18_1, false);
motor intake (PORT15, ratio18_1, false);
controller Controller;
// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */


void driveTrain(int rspeed, int lspeed, int waitTime) {
RM.spin(forward, rspeed, pct);
LM.spin(forward, lspeed, pct);
wait(waitTime, msec);
}

void stopRobot() {
  RM.stop(brake);
  LM.stop(brake);
}

void SpinRight(int lspeed) {
  RM.stop(brake);
  LM.spin(forward, lspeed , pct);
}

void SpinLeft(int rspeed) {
  LM.stop(brake);
  RM.spin(forward, rspeed , pct);
}
/*---------------------------------EOF---------------------------------------*/

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
  // ..........................................................................
  driveTrain(50, 50, 2000);
  wait(10000, msec);
  driveTrain(50, -50, 20000);
  wait(1000, msec); 
  driveTrain(50, -50, 360);
  wait(1000, msec);
  driveTrain(50, 50, 4000);
  wait(1000, msec);
  driveTrain(50, -50, 370);
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

    driveTrain(rspeed, lspeed, 10);

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
