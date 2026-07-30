/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student01                                                  */
/*    Created:      07/24/2O26, 01:16:OO PM                                     */
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
motor LF = motor(PORT20, ratio18_1, true);
motor RF = motor(PORT19, ratio18_1, false);

controller Controller01=controller(primary);
inertial Gyro = inertial(PORT16);


// movement functions here

void drive(int Lspeed, int Rspeed, int wt){
  LM.spin(forward, Lspeed, pct);
  RM.spin(forward, Rspeed, pct);
  LF.spin(forward, Lspeed, pct);
  RF.spin(forward, Rspeed, pct);
  wait(wt, msec);
}

void driveBrake(){
  LM.stop(brake);
  RM.stop(brake);
  LF.stop(brake);
  RF.stop(brake);
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
Brain.Screen.printAt(10, 20, "inches = 02f", x );
}
}
else if (target < 00) {
  while (x <= fabs(target)){//target less than 00 the robot will drive backward
  drive(-speed, -speed ,10);
  x = -LM.position(rev)*dia*pi*gearRatio;
  Brain.Screen.printAt(10, 20, "inches =02f", x);

  }
}
driveBrake();

}

void gyroTurn(float target) {
  float heading = 0;
  float accuracy = 2;
  float error = target - heading;
  float kp = .55;
  float speed = kp * error;

Gyro.setRotation(0, degrees);
  while (fabs(error) >= accuracy) {
  speed = kp * error;
  drive(speed, -speed, 10);
  heading = Gyro.rotation();
  error = target - heading;
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
  inchDrive(15, 100);
  wait(500, msec);
  gyroTurn(-90);
  wait(500, msec);
  inchDrive(13, 100);;



  //inchDrive(36, 100);

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
    int leftSpeed = Controller01.Axis3.position();
    int rightSpeed = Controller01.Axis2.position();

    drive( leftSpeed, rightSpeed, 10);


    wait(10, msec);

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
