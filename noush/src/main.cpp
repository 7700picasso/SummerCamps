/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      8/5/2025, 9:13:27 AM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
motor RM (PORT2, ratio18_1, true);
motor LM (PORT6, ratio18_1, false);
motor intake (PORT15, ratio18_1, false);

motor leftintake (PORT5, ratio18_1,false);
motor rightintake(PORT1, ratio18_1, true);
controller Controller;
brain Brain;
// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */


void driveTrain(int rspeed, int lspeed, int waitTime) {
RM.spin(forward, rspeed, pct);
LM.spin(forward, lspeed, pct);
wait(waitTime, msec);
}

void stopRobot() {
  RM.stop(brake);
  LM.stop(brake);
}

void inchDrive(float inches) {
  LM.setPosition(0, rev);
  float x = LM.position(rev) * M_PI * 4 * 1 ;
  float kP = 5;
  float error = inches - x;
  float speed = 0.0;


  while( error > 0.5 ) {
    speed = kP * error;
    driveTrain(speed, speed, 30);
    x = LM.position(rev) * M_PI * 4 * 1;
    error = inches - x;
  }
  stopRobot();
  Brain.Screen.printAt(200, 135, "distance = %0.2f", x );
}
/*---------------------------------EOF---------------------------------------*/

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
  intake.spin(reverse, 100, pct);
  inchDrive(36);
  driveTrain(50, -50, 300);
  inchDrive(5);
  driveTrain(50, -50, 340);
  intake.stop();
  inchDrive(25);
  driveTrain(-50, 50, 340);
  inchDrive(10);
  driveTrain(-50, 50, 340);
  stopRobot();

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
  Brain.Screen.print("usercontrol is working");
  while (1) {

    // int lspeed = Controller.Axis3.position(pct);
    // int rspeed = Controller.Axis2.position(pct);

    // driveTrain(rspeed, lspeed, 10);

    int forwardY = Controller.Axis3.position(pct);
    int sideX = Controller.Axis1.position(pct);
    driveTrain(forwardY - sideX, forwardY + sideX, 10);

    if (Controller.ButtonR1.pressing()){
      intake.spin(forward, 100, pct);

    }

    else if (Controller.ButtonR2.pressing()){
      intake.spin(reverse, 100, pct);
    }

    else {
      intake.stop(brake);
    }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.


   if(Controller.ButtonL1.pressing()){
    leftintake.spin(forward,100, pct);
    rightintake.spin(forward,100,pct);
    intake.spin(forward, 15, pct);
  }else if(Controller.ButtonL2.pressing()){
     leftintake.spin(reverse,100, pct);
      rightintake.spin(reverse,100,pct);
      intake.spin(reverse, 75, pct);

  }else{
    leftintake.stop(brake);
    rightintake.stop(brake);
   

    
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
