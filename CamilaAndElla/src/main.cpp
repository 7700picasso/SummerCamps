/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/21/2025, 1:32:03 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain; 
controller Controller;
motor LeftMotor (PORT10, ratio18_1, false);
motor RightMotor (PORT1, ratio18_1, true);
motor intake(PORT2, ratio18_1, true);
motor frontIntake(PORT21, ratio18_1, true);
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/* 

 
                                                                    
/*---------------------------------------------------------------------------*/

void drive(int Lspeed, int Rspeed, int waitTime){
LeftMotor.spin(forward, Lspeed, pct);
RightMotor.spin(forward, Rspeed, pct);
 wait(waitTime, msec); 

}
void DriveStop(){
LeftMotor.stop(brake);
RightMotor.stop(brake);

}

void inchdrive( float inches) {
  LeftMotor.setPosition(0,rev);
  float x = LeftMotor.position(rev) * 3.1415 * 4;
  float error = inches - x;
  float accuracy = 0.5;
  float kp = 4.5;
  while (fabs(error>accuracy))
  
  {
    float speed = kp*error;
    drive(speed, speed, 10);
    x = LeftMotor.position(rev) * 3.1415 * 4;
    error = inches - x;
    Brain.Screen.printAt(10,50,"inches = %.2f",x);
  }
  Brain.Screen.printAt(10,70,"done");
  DriveStop();
}

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
//go straight to the blocks

intake.spin(fwd, 36, pct);
inchdrive(25);
intake.stop();
//intake the blocks


//go backwards
drive(-50, -50, 200);
wait(500,msec);
intake.stop();
//turn 
drive(-50, 50, 530);

//go straight to line up with the goal 
inchdrive(25); 

//turn to the face the goal 
drive(35, -35, 950); //690

//go staright to get close to the goal 
drive(50, 50, 355);

//outtake the block in your robot
intake.spin(fwd, 100, pct); 

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
    int Lspeed = Controller.Axis3.position(pct);
    int Rspeed = Controller.Axis2.position(pct);
    drive(Lspeed, Rspeed, 10);
    if (Controller.ButtonR1.pressing()){
      intake.spin(forward, 100, pct);
    }
    else if (Controller.ButtonR2.pressing()){
      intake.spin(forward, -100, pct);
    }
    else {
      intake.stop();
    }

if (Controller.ButtonL1.pressing()){
     frontIntake.spin(forward, 100, pct);
    }
    else if (Controller.ButtonL2.pressing()){
      frontIntake.spin(forward, -100, pct);
    }
    else {
      frontIntake.stop();   
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
