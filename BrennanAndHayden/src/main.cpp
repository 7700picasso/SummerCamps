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
motor roller (PORT15, ratio6_1, true);

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

void inchdrive( float inches) {
  RM.setPosition(0,rev);
  float x = RM.position(rev) * 3.1415926535897932384626 * 4;
  float error = inches - x;
  float accuracy = 0.2;
  float kp = 5;
  while(fabs(error) > accuracy){
    float speed = kp*error;
    drive(speed, speed, 10);
    x = RM.position(rev) * 3.1415926535897932384626 * 4;
    error = inches - x;
    Brain.Screen.printAt(10, 50, "inches driven = %.2f", x);
  }
  Brain.Screen.printAt(10,70,"done");
  driveStop();
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
inchdrive(31.5);
drive(0, 100, 1000);
driveStop();
intake.spin(fwd, 100, pct);
wait(5,sec);
intake.stop(coast);
inchdrive(-5);


// inchdrive(30);
// driveStop();
// wait(1,sec);
// drive(-25, 25, 685*2/3*2);
// driveStop();
// wait(1,sec);
// inchdrive(18);
// drive(100,100,500);
// driveStop();
// intake.spin(fwd, 100, pct);
// driveStop();

// roller.spin(fwd, 100, pct);
// intake.spin(fwd,20, pct);
// inchdrive(23);
// roller.stop(coast);
// roller.spin(fwd, 25, pct);
// inchdrive(-17);
// intake.stop(coast);
// drive(50, -50, 550);
// inchdrive(25);
// drive(-50, 50, 645);
// roller.stop(coast);
// inchdrive(16);
// intake.spin(fwd, 100, pct);
// wait(5,sec);
// intake.stop(coast);
// driveStop();
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
    intake.stop(coast);
  }

  if (Controller.ButtonL1.pressing()){
    roller.spin(fwd, 100, pct);
  }
  else if (Controller.ButtonL2.pressing()){
    roller.spin(fwd, -100, pct);
  }
  else{
    roller.stop(coast);
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
