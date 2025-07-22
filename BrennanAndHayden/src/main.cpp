/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/21/2025, 1:31:30 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
controller Controller;
motor LM (PORT6, ratio18_1, false);
motor RM (PORT1, ratio18_1, true);
motor intake (PORT21, ratio18_1, true);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
void drive(int Lspeed, int Rspeed, int waitTime) {
  LM.spin(forward, Lspeed, pct);
  RM.spin(forward, Rspeed, pct);
  wait(waitTime, msec);
}

void driveStop(){
  LM.stop(brake);
  RM.stop(brake);
}
/*---------------------------------------------------------------------------*/

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
  Brain.Screen.printAt(10, 20, "HELLO");
  Brain.Screen.setFillColor(purple);
  Brain.Screen.setPenColor(green);
  Brain.Screen.drawCircle(240, 120, 100);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.setPenColor(red);
  Brain.Screen.drawRectangle(215, 95, 50, 50);
  drive(50, 50, 2650);
  drive(-50, 50, 305);
  drive(50, 50, 2250);
  drive(-50, 50, 350);
  drive(50, 50, 4000);
  drive(-50, 50, 580);
  drive(50, 50, 4000);
  drive(-50, 50, 610);
  drive(50, 50, 4500);
  driveStop();
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
    int Lspeed = Controller.Axis3.position(pct);
    int Rspeed = Controller.Axis2.position(pct);
    drive(Lspeed,Rspeed,10);
  if (Controller.ButtonR1.pressing()){
    intake.spin(fwd, 100, pct);
  }
  else if (Controller.ButtonR2.pressing()){
    intake.spin(fwd, -100, pct);
  }
  else{
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
