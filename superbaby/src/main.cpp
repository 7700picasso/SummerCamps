/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      8/5/2025, 9:14:00 AM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
motor RM (PORT3, ratio18_1, true);
motor LM (PORT2, ratio18_1, false);
motor intake (PORT20, ratio18_1, false);
controller Jaquavius;
brain Brain;


// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */

void driveTrain(int rspeed, int lspeed, int waitTime) {

RM.spin(forward, rspeed, pct ); 
LM.spin(forward, lspeed, pct);
wait(waitTime, msec); 

}

void stopRobot(){

  RM.stop(brake);
LM.stop(brake);

}

void inchDrive(float inches) {
LM.setPosition(0, rev);  
float x = LM.position(rev) * M_PI * 4 * 1;
float kP = 4;
float error = inches - x;
float speed = 0.0;

while (fabs(error) > 0.5 ) {
  speed = kP * error;
driveTrain(speed, speed, 30);
x = LM.position(rev) * M_PI * 4 * 1;
error = inches - x;
}
stopRobot();
Brain.Screen.printAt(10, 20, "distance = %0.2f", x);

}




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
  // ..........................................................................
intake.spin(reverse, 35, pct);
  inchDrive(40);
  wait(1000, msec);
  intake.stop();
inchDrive(-30);
driveTrain(-50, 50, 300);
stopRobot();
inchDrive(30);
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
  while (1) {
    
int forwardY = Jaquavius.Axis3.position(pct); 
int sideX = Jaquavius.Axis1.position(pct);
driveTrain(forwardY - sideX, forwardY + sideX, 10);
 

if (Jaquavius.ButtonR1.pressing()){

  intake.spin(forward, 100, pct);
}
else if (Jaquavius.ButtonR2.pressing()){
  intake.spin(reverse, 100, pct);
}
else {intake.stop(brake);
}
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
