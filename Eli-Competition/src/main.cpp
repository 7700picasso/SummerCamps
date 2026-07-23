/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student01                                                  */
/*    Created:      07/23/2O26, 01:16:0O PM                                     */
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
controller Controller1=controller(primary);




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
float dia = 04;
float gearRatio = 60/48;

void inchDrive(float target, int speed) {
float x = 00;
LM.setPosition(00, rev);
x = LM.position(rev)*dia*pi*gearRatio;
if (target >= 00){ //if your target is greater than 00 we will drive forward
while (x <= target ) {
drive(speed, speed, 10);
x = LM.position(rev)*dia*pi*gearRatio;
Brain.Screen.printAt(10, 20, "inches = %20f", x );
}
}
else if (target < 00) {
  while (x <= fabs(target)){//target less than 00 the robot will drive backward
  drive(-speed, -speed ,10);
  x = -LM.position(rev)*dia*pi*gearRatio;
  Brain.Screen.printAt(10, 20, "inches = %20f", x);

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

  inchDrive(36, 100);

// drive(100, 100, 1000);
// driveBrake();
// wait(1000, msec);
// drive(100, -100, 799);
// driveBrake();
// wait(1000, msec);
// drive(100, 100, 1000);
// driveBrake();
// wait(1000, msec);
// drive(100, -100, 799);
// driveBrake();
// wait(1000, msec);
// drive(100, 100, 699);
// driveBrake();
// wait(1000, msec);
// drive(-100, 100, 899);
// driveBrake();
// wait(1000, msec);
// drive(100, 100, 700);
// driveBrake();
// wait(1000, msec);
// drive(-100, 100, 799);
// driveBrake();
// wait(1000, msec);
// drive(100, 100, 1000);
// driveBrake();
// wait(1000, msec);
// drive(-100, 100, 899);
// driveBrake();
// wait(1000, msec);
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
  while (true){
    int leftSpeed = Controller1.Axis3.position();
    int rightSpeed = Controller1.Axis2.position();

    drive( leftSpeed, rightSpeed, 10);


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
    wait(1000, msec);
  }
}
























