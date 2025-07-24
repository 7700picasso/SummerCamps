/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       rollingrobots                                             */
/*    Created:      7/21/2025, 1:32:03 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "main.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
controller Controller;
motor LM(PORT20, ratio18_1, false);
motor RM(PORT9, ratio18_1, true);
motor intake(PORT13, ratio18_1, false);
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */

void drive(int Lspeed, int Rspeed, int waitTime)
{
  LM.spin(forward, Lspeed, pct);
  RM.spin(forward, Rspeed, pct);
  wait(waitTime, msec);
}
void driveStop()
{
  LM.stop(brake);
  RM.stop(brake);
}

void inchdrive(float inches)
{
  LM.setPosition(0, rev);
  float x = LM.position(rev) * 3.1415 * 4;
  float error = inches - x;
  float accuracy = 0.2;
  float kp = 5;
  while (fabs(error) > accuracy)
  {
    float speed = kp * error;
    drive(speed, speed, 10);
    error = inches - x;
    x = LM.position(rev) * 3.1415 * 4;
    Brain.Screen.printAt(10, 50, "inches = %.2f, error = %2f", x, error);
  }
  Brain.Screen.printAt(10, 70, "done");
  driveStop();
}

void pre_auton(void)
{

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

  // first go straight for  30 inches
  inchdrive(26);

  // turn right to the face the goal (use the drive function to do this)
  drive(50, -50, 998);
  driveStop();
  // go straight to get close the goal
  inchdrive(14);
  // use your intake to score
  intake.spin(fwd, -100, pct);
  wait(5, sec);

  Brain.Screen.printAt(10, 20, "ive been a good boy :)");
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
  while (1)
  {
    int Lspeed = Controller.Axis3.position(pct);
    int Rspeed = Controller.Axis2.position(pct);
    drive(Lspeed, Rspeed, 10);
    if (Controller.ButtonR1.pressing())
    {
      intake.spin(forward, 100, pct);
    }
    else if (Controller.ButtonR2.pressing())
    {
      intake.spin(fwd, -100, pct);
    }

    else
    {
      intake.stop();
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources
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
