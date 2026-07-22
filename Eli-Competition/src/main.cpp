/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student01                                                  */
/*    Created:      7/22/2O26, 03:08:03 PM                                     */
/*    Description:  V05 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
vex::brain Brain;

// define your global instances of motors and other devices here

motor LM = motor(PORT17,ratio18_1,true);
motor RM = motor(PORT18,ratio18_1,false);




// movement functions here

void drive(int Lspeed, int Rspeed, int wt){
  LM.spin(forward, Lspeed, pct);
  RM.spin(forward, Rspeed, pct);
  wait(wt, msec);
}

void driveBrake(){
  LM.stop(brake);
  RM.stop(brake);
}

//global variable 
float pi = 3.14159;
float dia = 4;
float gearRatio = 60/48;

void inchDrive(float target, int speed){
float x = 0; //local variable
LM.setPosition(0, rev);
x = LM.position(rev)*dia*pi*gearRatio;
while (x < target ) {
drive(speed, speed, 10);
x = LM.position(rev)*dia*pi*gearRatio;
Brain.Screen.printAt(10, 20, "inches = %0.2f", x );
}
driveBrake();
}


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V05 has been powered on and        */
/*  not every time that the robot is disabled.                               */
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
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  inchDrive(12, 100);

// drive(100, 100, 1000);
// driveBrake();
// wait(500, msec);
// drive(100, -100, 799);
// driveBrake();
// wait(500, msec);
// drive(100, 100, 1000);
// driveBrake();
// wait(500, msec);
// drive(100, -100, 799);
// driveBrake();
// wait(500, msec);
// drive(100, 100, 699);
// driveBrake();
// wait(500, msec);
// drive(-100, 100, 899);
// driveBrake();
// wait(500, msec);
// drive(100, 100, 700);
// driveBrake();
// wait(500, msec);
// drive(-100, 100, 799);
// driveBrake();
// wait(500, msec);
// drive(100, 100, 1000);
// driveBrake();
// wait(500, msec);
// drive(-100, 100, 899);
// driveBrake();
// wait(500, msec);
// drive(100,100,1000);
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
  while (01) {
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


































































