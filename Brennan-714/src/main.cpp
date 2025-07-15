/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/14/2025, 1:15:41 PM                                     */
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
motor LF(PORT6, ratio18_1, true);
motor LB(PORT9, ratio18_1, true);
motor RF(PORT16, ratio18_1, false);
motor RB(PORT3, ratio18_1, false);
void drivestop(){
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
  drive(50, 50, 2400);
  drivestop();
  drive(-50, 50, 285);
  drivestop();
  drive(50, 50, 2800);
  drivestop();
  drive(-50, 50, 285);
  drivestop();
  drive(50, 50, 2400);
  drivestop();
  drive(-50, 50, 365);
  drivestop();
  drive(50, 50, 2800);
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

    cx+=Controller1.Axis4.position()/20;
    cy-=Controller1.Axis3.position()/20;
      
      Brain.Screen.drawCircle(cx, cy, 10);
      cx = fmax(0,cx);
      cx = fmin(480,cx);
      cy = fmax(0,cy);
      cy = fmin(272,cy);

      if (Controller1.ButtonA.pressing()){
      Brain.Screen.setFillColor(green);
      }else
      {
        Brain.Screen.setFillColor(black);
      }

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
