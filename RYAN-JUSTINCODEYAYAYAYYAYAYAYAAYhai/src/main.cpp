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
motor arrrmm(PORT3, ratio18_1, false);
controller something = controller(primary);

pneumatics claw = pneumatics(Brain.ThreeWirePort.A); 

inertial isensor = inertial(PORT10);
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
  isensor.calibrate();
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

void armMove(int ishowspeed, int wt){
  arrrmm.spin(forward, ishowspeed, percent);
  wait(wt, msec);
}

void turnP(double targetdegrees, int maxSpeed, int minSpeed){
  isensor.setRotation(0, degrees);

  double kP = 0.1;
  double error = targetdegrees - isensor.rotation(degrees);

  while (fabs(error) > 1.0) {
    error = targetdegrees - isensor.rotation(degrees);
    double speed = fabs(error) * kP;

    if (speed>maxSpeed){
      speed = maxSpeed;
    }

    if (speed < minSpeed){
      speed = minSpeed;
    }

    if (error > 0){
      drive(speed, -speed, 10);
    }
    else{
      drive(-speed, speed, 10);
    }
     wait(10, msec);
  }
  brakeMotor();
}

void inchDrive(double inches, int maxSpeed, int minSpeed){
  justin.setPosition(0, degrees);

  double wheelDiameter = 3.25;
  double pi = 3.14156;
  double gearratio = 1.0 / 1.0;

  double circumference = wheelDiameter * pi;
  double wheelrotations = inches / circumference;
  double motorrotations = wheelrotations * gearratio;
  double targetdegrees = motorrotations * 360.0;

  double kp = 0.1;
  double error = targetdegrees - justin.position(degrees);

  while(fabs(error) > 5){
    error = targetdegrees - justin.position(degrees);

    double speed = fabs(error) * kp;

    if (speed > maxSpeed){
      speed = maxSpeed;
    }

    if (speed < minSpeed){
      speed = minSpeed;
    }

    if (error > 0){
      drive(speed, speed, 10);
    }
    else{
      drive(-speed, -speed, 10);
    }
  }
  brakeMotor();
}



void turnLeft(int time){
  drive(50, -50, time);
}

void turnRight(int time){
  drive(-50, 50, time);
}

void stopwait(int time){
  wait(time, msec);
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
  // claw.close();
  // armMove(50, 100);
  // inchDrive(18, 80, 30);
  // turnP(85, 50, 20);
  // inchDrive(8, 80, 30);
  // armMove(-30, 100);
  // stopwait(1500);
  // claw.open();

  claw.close();
  armMove(50, 100);
  inchDrive(15, 80, 30);
  turnP(-85, 50, 20);
  inchDrive(8, 80, 30);
  armMove(-30, 100);
  stopwait(1500);
  claw.open();
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

    if (something.ButtonL1.pressing()){
      armMove(50, 10);
    }
    else if (something.ButtonL2.pressing()){
      armMove(-50, 10);
    }
    else{
      arrrmm.stop(brake);
    }

     if (something.ButtonR1.pressing()){
      claw.open();
    }
    else if (something.ButtonR2.pressing()){
      claw.close();
    }



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
