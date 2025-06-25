/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      6/24/2024, 11:23:14 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;



// A global instance of competition
competition Competition;
brain Brain;
// define your global instances of motors and other devices here
controller Controller1= controller(primary);
motor RB = motor (PORT1, ratio18_1, true);
motor LB = motor (PORT10, ratio18_1, false);

bumper Bumper1 = bumper(Brain.ThreeWirePort.A);
int counter = 0;

optical Optical1= optical(PORT3);

inertial Gyro = inertial(PORT2);


float pi = 3.14;
float dia = 4.00;
float gearRatio= 1;

void drive(int rspeed, int lspeed, int wt){
  LB.spin(fwd,lspeed,pct);
  RB.spin(fwd,rspeed,pct);
  wait(wt,msec);
}

void gyroPrint(){
  float heading= Gyro.rotation(deg);
}

void stopRobot(){
  LB.stop(brake);
  RB.stop(brake);
}

void gyroTurnRight(float target){
  float heading=180.0;
  Gyro.setRotation(180.0,degrees);
  while(heading<= target){
    LB.spin(forward,50,pct);
    heading= Gyro.rotation(deg);
  }
  stopRobot();
}

void gyroTurnLeft(float target){
  float heading=180.0;
  Gyro.setRotation(180.0,degrees);
  while(heading>= target){
    RB.spin(forward,50,pct);
    heading= Gyro.rotation(deg);
  }
stopRobot();
}



void checkBumper(){
if(Bumper1.pressing()){
  counter++;
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("counter:%d", counter);
  wait(500,msec);
}
}

void avoidObjects(){
  while(true){
    if(Optical1.isNearObject()){
    drive(50,50,10);
  }
  else{
    stopRobot();
    wait(500,msec);
    drive(-50,50,1000);
    stopRobot();
    wait(500,msec);

  }
  }
}

void inchDrive(float target){
  float x = 0;
  LB.setPosition(0,rev);
  x= LB.position(rev)*dia*pi*gearRatio;

  if(target >= 0){
  while (x<= target){
  drive(50,50,10);
x = LB.position(rev)*dia*pi*gearRatio;
Brain.Screen.printAt(10,20,"inches = %0.2f", x);
}
  }

else if (target < 0){
  while (x <= fabs(target)){
    drive(-50,-50,10);
    x = -LB.position(rev)*dia*pi*gearRatio;
    Brain.Screen.printAt(10,20,"inches = %0.2f", x);
  }
}
stopRobot();
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
inchDrive(45);
gyroTurnRight(280);
wait(1000,msec);

inchDrive(65);
gyroTurnLeft(90);
wait(1000,msec);

/*inchDrive(10);
wait(111,msec);
gyroTurnLeft(90);
wait(650,msec);
inchDrive(60);
gyroTurnRight(270);
wait(600,msec);
inchDrive(10);
gyroTurnRight(270);
wait(600,msec);
inchDrive(45);
gyroTurnLeft(90);
wait(600,msec);
inchDrive(13);
gyroTurnLeft(80);
wait(550,msec);
inchDrive(100);
*/
}
//1-2-3-4-5-6-7-8-9-10-11-12-13-14-15-16-17-18-19-20-21-22-23-24-25-26-27-28-29-30-31-32-33-34-35-36-37-38-39-40-41-42-43-44-45-46-47-48-49-50
// We like to paaaarrrrrtttttayyyyyyy!!!!!
// Blueberry Poptarts
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
    int leftSpeed = Controller1.Axis2.position();
    int rightSpeed = Controller1.Axis3.position();

    drive (leftSpeed, rightSpeed, 10);
    if(Controller1.ButtonX.pressing()){
      stopRobot();
    }
  }
    wait(20, msec); // Sleep the task for a short amount of time to
                  // prevent wasted resources.
  
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