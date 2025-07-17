/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/14/2025, 1:15:35 PM                                     */
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
motor LB(PORT1, ratio18_1, true);
motor LF(PORT2, ratio18_1, true);
motor RB(PORT7, ratio18_1, false);
motor RF(PORT9, ratio18_1, false);
inertial gyro1 = inertial(PORT13);

void drive(int lspeed, int rspeed, int wt)
{
  LF.spin(fwd, lspeed, pct);
  LB.spin(fwd, lspeed, pct);
  RF.spin(fwd, rspeed, pct);
  RB.spin(fwd, rspeed, pct);
  wait(wt, msec);
}
void drivestop()
{
  LF.stop(brake);
  LB.stop(brake);
  RF.stop(brake);
  RB.stop(brake);
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

float pi = 3.14;
float dia = 3.25;
float gearRatio = 0.75;

/* void inchDrive(float target, float speed = 100)
{
  LF.setPosition(0, rev);
  float x = LF.position(rev) * dia * pi * gearRatio;
  while (fabs(x) < fabs(target))
  {
    drive(speed * sign(target), speed * sign(target), 10);
    x = LF.position(rev) * dia * pi * gearRatio;
  }
  drivestop();
} */

void inchDrive(float target, float speed = 100){  
  LF.setPosition(0, rev);
  float x = LF.position(rev) * dia * pi * gearRatio;
  float error = target - x;
  float kp = 10;
  while (fabs(x) < fabs(target)){
    x = LF.position(rev) * dia * pi * gearRatio;
    error = target - x;
    drive(kp*error + 10*sign(error),kp*error + 10*sign(error),10);
  }
  drivestop();
}





// realative turn
void turn(float target)
{
  gyro1.resetRotation();
  while (fabs(gyro1.rotation()) < fabs(target))
  {
    drive(50 * sign(target), -50 * sign(target), 10);
  }
  drivestop();
}

void turnTo(float target)
{
  float error = target - gyro1.yaw();
  float kp = 2;
  while (fabs(error) > 1){
    error = target - gyro1.yaw();
    if (error > 180){
      error = error - 360;
    }
    if (error < -180){
      error = error + 360;
    }
    drive(kp*(error),-kp*(error),10);
  }
  drivestop();
}

//if (|error| > 180){
//  error = error - sign(error) * 360;
//}
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
  // gyro1.calibrate(); //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

  inchDrive(75);
  turnTo(-45);
  inchDrive(36);
  turnTo(-90);
  inchDrive(70);
  turnTo(180);


  /*
  inchDrive(96);*/
  
  

  

  // 800 is full turn
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
  // User control code here, inside the loop

  int cx = 0;
  int cy = 0;

  while (1)
  {
    if (Brain.Screen.pressing())
    {
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();
      Brain.Screen.clearScreen();
      Brain.Screen.printAt(10, 50, "brain pressed at %d,%d", x, y);

      if (x > 90 && x < 230 && y > 60 && y < 160)
      {
        Brain.Screen.setFillColor(green);
      }
      else
      {
        Brain.Screen.setFillColor(red);
      }
    }
    Brain.Screen.clearScreen();
    if (Controller1.ButtonA.pressing())
    {
      Brain.Screen.setFillColor(purple);
    }
    else
    {
      Brain.Screen.setFillColor(orange);
    }
    Brain.Screen.drawCircle(cx, cy, 10);
    cx += Controller1.Axis1.position() / 20;
    cy -= Controller1.Axis2.position() / 20;

    cx = fmax(0, cx);
    cx = fmin(480, cx);

    cy = fmax(0, cy);
    cy = fmin(272, cy);

    Controller1.Screen.setCursor(0, 0);
    // gyro1.rotation();
    // gyro1.heading();
    Controller1.Screen.print("angle = %.2f   ", gyro1.heading());

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.

    int lstick = Controller1.Axis3.position();
    int rstick = Controller1.Axis1.position();
    if (fabs(lstick) < 10)
    {
      lstick = 0;
    }
    if (fabs(rstick) < 10)
    {
      rstick = 0;
    }

    drive(lstick + rstick, lstick - rstick, 10);
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
