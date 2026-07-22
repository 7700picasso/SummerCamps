/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/21/2026, 3:08:19 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;
float pi = 3.14;
float dia = 4.00;
float gearRatio = 60.0/48.0;
// A global instance of competition
competition Competition;

vex::brain Brain;

motor LM = motor(PORT1, ratio18_1, false);
motor RM = motor(PORT9, ratio18_1, true);

void drive(int Lspeed, int Rspeed, int wt){
  LM.spin(forward, Lspeed, pct);
  RM.spin(forward, Rspeed, pct);
  wait(wt, msec );
}

void driveBrake(){
  LM.stop(brake);
  RM.stop(brake);
}

void inchDrive(float target){
  float x = 0; 
  LM.setPosition(0, rev);
  x = LM.position(rev)*dia*pi*gearRatio;
  while (x > target ) {
    drive(-50,-50, 10);
    x = LM.position(rev)*dia*pi*gearRatio;
    Brain.Screen.printAt(10, 20, "inches = %0.2f", x);
  }
  driveBrake();
}
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/


void pre_auton(void){
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*----------------x=LM.position(rev)*Pi---------------------------------------------------*/

void autonomous(void) {
  inchDrive(-12);
  // drive(100, 100, 800);
  // driveBrake();
  // wait(500, msec);
  // drive(-100,100,500);
  // driveBrake();
  // wait(500, msec);
  // drive(100, 100, 800);
  // driveBrake();
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
