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

pneumatics claw = pneumatics(Brain.ThreeWirePort.A);

inertial isensor = inertial(PORT4);

motor justin(PORT11, ratio18_1, false);
motor ryan(PORT20, ratio18_1, true);
motor arm(PORT3, ratio18_1, false);
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

void armMove(int ishowspeed, int waittime){
  arm.spin(forward, ishowspeed, percent);
  wait(waittime, msec);
}

void brakeMotor(){
  justin.stop(brake);
  ryan.stop(brake);
}

void inchDrive(double inches, int maxSpeed, int minSpeed){
  justin.setPosition(0, degrees);

  double wheelDiameter = 3.25;
  double pi = 3.14159;
  double gearRatio = 1.0/1.0;

  double circumference = wheelDiameter * pi;
  double wheelRotations = inches / circumference;
  double motorRotations = wheelRotations * gearRatio;
  double targetDegrees = motorRotations * 360.0;

  double kP = 0.1;
  double error = targetDegrees - justin.position(degrees);


  while (fabs(error) > 5){
    error = targetDegrees - justin.position(degrees);

    double speed = fabs(error) * kP;

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
  claw.close();
  armMove(50, 100);
  inchDrive(14, 80, 30);
  drive(50,-50,850);
  inchDrive(7.5, 80, 30);
  armMove(-50, 1000);
  claw.open();
  inchdrive(-7.5,80,30);
  armmove(-50,100);
  claw.close();
  drive(-50,50,850);


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
    else if(something.ButtonL2.pressing()){
      armMove(-50, 10);
    }
    else{
      arm.stop(brake);
    }

    if(something.ButtonR1.pressing()){
      claw.open();
    }
    else if(something.ButtonR2.pressing()){
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
