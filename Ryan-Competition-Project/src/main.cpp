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

// A global instance of competition
competition Competition;

vex::brain Brain;

float dia = 4.0;
float pi = 3.14;
float gearRatio = 60/48;

motor FL = motor(PORT1, ratio18_1, true);
motor FR = motor(PORT9, ratio18_1, false);
motor BL = motor(PORT5, ratio18_1, true);
motor BR = motor(PORT10, ratio18_1, false);

controller Controller1 = controller(primary);
void drive(int Lspeed, int Rspeed, int wt){
  FL.spin(forward, Lspeed, pct);
  FR.spin(forward, Rspeed, pct);
  BL.spin(forward, Lspeed, pct);
  BR.spin(forward, Rspeed, pct);
  wait(wt, msec );
}



void driveBrake(){
FL.stop(brake);
  FR.stop(brake);
  BL.stop(brake);
  BR.stop(brake);
}

void inchDrive(float target){
  float x = 0; 
  FL.setPosition(0, rev);
  x = BL.position(rev)*dia*pi*gearRatio;

  if (target >= 0 ){
  while (x <= target ) {
    drive(50, 50, 10);
    x = FL.position(rev)*dia*pi*gearRatio;
    Brain.Screen.printAt(10, 20, "inches = %0.2f", x);
  }
}
else if (target <0){
  while (x <=fabs(target)){
    drive (-50, -50, 10);
    x = -FL.position(rev)*dia*pi*gearRatio;
Brain.Screen.printAt(10, 20, "inches = %0.2f", x);
  }
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
  //go forward 36 inches
  inchDrive(36);

  //wait a bit before each movement
  wait(300, msec);

  //turn 90 degrees to the left
  drive(-100, 100, 800);
  driveBrake();

  //go foward 36 inches.q
  wait(300, msec);
  inchDrive(36);
  wait(300, msec);

  drive(-100, 100, 800);
  driveBrake();





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
  while (true) {
    int forwardSpeed = Controller1.Axis3.position();
    int turnSpeed = Controller1.Axis1.position();

    drive( forwardSpeed + turnSpeed, forwardSpeed - turnSpeed, 10);

    
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
