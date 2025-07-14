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

brain Brain;

// define your global instances of motors and other devices here
motor LB(PORT1,ratio18_1,true);
motor LF(PORT2,ratio18_1,true);
motor RB(PORT7,ratio18_1,false);
motor RF(PORT9,ratio18_1,false);

void drive(int lspeed,int rspeed,int wt){
  LF.spin(fwd,lspeed,pct);
  LB.spin(fwd,lspeed,pct);
  RF.spin(fwd,rspeed,pct);
  RB.spin(fwd,rspeed,pct);
  wait(wt,msec);
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

void autonomous(void) {
  drive(100,100,500);
  drive(100,-100,800);
  drive(100,100,500);
  drive(0,0,0);

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

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    if (Brain.Screen.pressing()); {
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();
     // Brain.Screen.clearScreen();
      Brain.Screen.printAt(10,50, "brain pressed at %d,%d",x,y);

      if(x > 90 && x < 230 && y > 60 && y < 160){
      Brain.Screen.setFillColor(green);
      }else{
        Brain.Screen.setFillColor(red);
      }

      Brain.Screen.drawRectangle(90, 60, 140, 100);
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
