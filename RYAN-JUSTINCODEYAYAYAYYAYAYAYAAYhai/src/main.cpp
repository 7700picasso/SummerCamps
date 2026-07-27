/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      7/27/2026, 1:58:05 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

brain Brain;
motor justin(PORT11, ratio18_1, false);
motor ryan(PORT20, ratio18_1, true);
controller something = controller(primary);
// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton() {
 
}

void drive(int justinspeed, int ryanspeed, int wt){
  justin.spin(forward, justinspeed, pct);
  ryan.spin(forward, ryanspeed, pct);
  wait(wt, msec);
}

void brakeMotor(){
  justin.stop(brake);
  ryan.stop(brake);
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
  // Insert autonomous user code here.
  // ..........................................................................
  drive(50, 50, 1000);
  brakeMotor();
  drive(50, -50, 650);
  brakeMotor();
  drive(50, 50, 1400);
  brakeMotor();
  drive(-50, 50, 750);
  brakeMotor();
  drive(50, 50, 1750);
  brakeMotor();
  drive(-50, 50, 800);
  brakeMotor();
  drive(50, 50, 1650);
  brakeMotor();
  drive(50, -50, 590);
  brakeMotor();
  drive(50, 50, 1700);
  brakeMotor();
  drive(-50, 50, 690);
  brakeMotor();
  drive(50, 50, 1500);
  brakeMotor();
  drive(-50, -50, 1750);
  brakeMotor();
  drive(50, -50, 650);
  drive(50, 50, 1400);
  brakeMotor();

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
  while (1) {
    
    int jleft = something.Axis3.position();
    int rright = something.Axis2.position();

    drive(jleft, rright, 10);
    wait(20, msec); 
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
