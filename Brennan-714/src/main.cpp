/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/14/2025, 1:15:41 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include <iostream>

using namespace vex;

// A global instance of competition
competition Competition;
controller Controller1;

brain Brain;

// define your global instances of motors and other devices here
motor LF(PORT6, ratio18_1, true);
motor LB(PORT9, ratio18_1, true);
motor RF(PORT16, ratio18_1, false);
motor RB(PORT3, ratio18_1, false);

inertial gyro1 = inertial(PORT19);

void drivestop()
{
  LF.stop(brake);
  RF.stop(brake);
  LB.stop(brake);
  RB.stop(brake);
}
void drive(int lspeed, int rspeed, int wt)
{
  LF.spin(fwd, lspeed, pct);
  LB.spin(fwd, lspeed, pct);
  RF.spin(fwd, rspeed, pct);
  RB.spin(fwd, rspeed, pct);

  wait(wt, msec);
}
int sign(float a)
{
  if (a > 0)
  {
    return 1;
  }
  else
  {
    return -1;
  }
}

float pi = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899;
float dia = 4;
float gearRatio = 1.5;

void inchDrive(float target, float speed = 50)
{
  RF.setPosition(0, rev);
  LF.setPosition(0, rev);
  float x = LF.position(rev) * dia * pi * gearRatio;
  float error = target - x;
  float kp = 2.000000000000;
  float kt = 0.01;
  float initialAngle = gyro1.rotation();
  while (fabs(x) < fabs(target))
  {

    float avgrev = (LF.position(rev) + RF.position(rev)) / 2;
    x = avgrev * dia * pi * gearRatio;
    error = target - x;
    float turnError = initialAngle - gyro1.rotation();
    float speed = kp * error + 5 * sign(error);
    drive(speed * (1 + turnError * kt), speed * (1 - turnError * kt), 10);
  }
  drivestop();
}

void turn(float target)
{
  gyro1.resetRotation();
  while (fabs(gyro1.rotation()) < fabs(target))
  {
    drive(10 * sign(target), -10 * sign(target), 10);
  }
  drivestop();
}

void turnTo(float target)
{
  float error = target - gyro1.yaw();
  float prevError = error;
  float kp = 0.75;
  float kd = 9;
  std::cout << "[";
  float t = 0;
  while (fabs(error) > 1)
  {
    error = target - gyro1.yaw();
    if (fabs(error) > 180)
    {
      error = error - sign(error) * 360;
    }
    float speed = kp * error + 5 * sign(error) + kd * (error - prevError);
    prevError = error;
    drive(speed, -speed, 10);
    t += 0.01;
    std::cout << ",(" << t << ", " << error << ")";
  }
  std::cout << "]";
  drivestop();
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

void pre_auton(void)
{
  gyro1.calibrate();
  waitUntil(!gyro1.isCalibrating());
  // Brain.Screen.print("hi");
  // Brain.Screen.drawRectangle(0,0,50,50);
  //  All activities that occur before the competition starts
  //  Example: clearing encoders, setting servo positions, ...
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

void autonomous(void)
{
  waitUntil(!gyro1.isCalibrating());
  inchDrive(75);
  inchDrive(-9);
  turnTo(90);
  wait(1, sec);
  inchDrive(25);
  turnTo(0);
  inchDrive(60);
  turnTo(270);
  wait(1, sec);
  inchDrive(30);
  turnTo(180);
  wait(1, sec);
  inchDrive(20);
  inchDrive(-24);
  turnTo(45);
  wait(1, sec);
  inchDrive(42);
  inchDrive(-30);
  turnTo(135);
  wait(1, sec);
  inchDrive(23);
  turnTo(45);
  wait(1, sec);
  drive(100, 100, 750);
  drivestop();

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
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

void usercontrol(void)
{

  int cx = 0;
  int cy = 0;

  // User control code here, inside the loop
  while (1)
  {
    if (Brain.Screen.pressing())
    {
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();
      Brain.Screen.clearScreen();
      Brain.Screen.printAt(10, 50, "brain pressed at %d,%d", x, y);

      // We press inside the rectangle
      if (x > 240 && x < 290 && y > 130 && y < 180)
      {
        Brain.Screen.setFillColor(green);
      }
      // otherwise
      else
      {
        Brain.Screen.setFillColor(red);
      }
      Brain.Screen.drawRectangle(240, 130, 50, 50);
      Brain.Screen.drawCircle(x, y, 10);
    }

    cx += Controller1.Axis4.position() / 20;
    cy -= Controller1.Axis3.position() / 20;

    Brain.Screen.drawCircle(cx, cy, 10);
    cx = fmax(0, cx);
    cx = fmin(480, cx);
    cy = fmax(0, cy);
    cy = fmin(272, cy);

    if (Controller1.ButtonA.pressing())
    {
      Brain.Screen.setFillColor(green);
    }
    else
    {
      Brain.Screen.setFillColor(black);
    }
    int lstick = Controller1.Axis3.position();
    int rstick = Controller1.Axis2.position();
    drive(lstick*0.5, rstick*0.5,10);

    Controller1.Screen.setCursor(0, 0);
    // gyro1.rotation();
    // fyro1.heading();
    Controller1.Screen.print("angle = %.2f     ", gyro1.rotation());

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
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}
