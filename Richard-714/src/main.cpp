/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/14/2025, 1:15:40 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
controller Controller1;
brain Brain;
// define your global instances of motors and other devices here
motor LF = motor(PORT7, ratio18_1, true);
motor LB= motor(PORT8, ratio18_1, true);
motor RT = motor(PORT4, ratio18_1, false);
motor RB(PORT19, ratio18_1, false);
inertial gyro1 = inertial(PORT5);

void drivestop()
{
  LF.stop(brake);
  LB.stop(brake);
  RT.stop(brake);
  RB.stop(brake);
}
void drive(int lspeed, int rspeed, int wt)
{
  LF.spin(fwd, lspeed, pct);
  RT.spin(fwd, rspeed, pct);
  LF.spin(fwd, lspeed, pct);
  RB.spin(fwd, rspeed, pct);
  wait(wt, msec);
}
int sign(float a)
{
  if (a < 0)
  {
    return -1;
  }
  return 1;
}

float pi = 3.141592653589;
float dia = 4;
float gearRatio = 1.5;

void inchDrive(float target, float speed = 50)
{
  LF.setPosition(0, rev);
  float x = LF.position(rev) * dia * pi * gearRatio;
  float error = target - x;
  float kp = 4;
  while (fabs(error) > 0.25)
  {

    x = LF.position(rev) * dia * pi * gearRatio;

    error = target - x;
    float speed = kp * error + 10 * sign(error);

    drive(speed, speed, 10);
  }
  drivestop();
}

void turnTo(float target)
{
  float error = target - gyro1.yaw();
  while (fabs(error) > 1)
  {
    error = target - gyro1.yaw();
    float kp = 0.5;

    if (error > 180)
    {
      error = error - 360;
    }
    if (error < -180)
    {
      error = error + 360;
    }

    drive(kp * error, -kp * error, 10);
  }
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

  // Brain.Screen.print("hi");
  // Brain.Screen.drawRectangle(0,0,50,50);
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

void autonomous(void)
{
  inchDrive(72);
  turnTo(-45);
  inchDrive(60);
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

  Brain.Screen.drawCircle(240, 130, 50, 50);
  // User control code here, inside the loop
  while (1)
  {
    cx += Controller1.Axis4.position() / 20;
    cy -= Controller1.Axis3.position() / 20;
    if (Brain.Screen.pressing())
    {

      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();
      Brain.Screen.printAt(10, 50, "Brain pressed at %d,%d", x, y);
      // we press inside the rectangle
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
    }
    if (Controller1.ButtonA.pressing())
    {
      Brain.Screen.setFillColor(green);
    }
    else
    {
      Brain.Screen.setFillColor(transparent);
    }

    Brain.Screen.drawCircle(cx, cy, 10);

int lstick = Controller1.Axis3.position();
int rstick = Controller1.Axis2.position();
drive(lstick,rstick,10);


Controller1.Screen.setCursor(0,0);
Controller1.Screen.print("angle = %.2f    ", gyro1.yaw());
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
  // usercontrol();
  //  Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}

