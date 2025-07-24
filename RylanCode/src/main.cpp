/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/21/2025, 1:31:37 PM                                     */
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
motor LM (PORT10,ratio18_1, false);
motor RM (PORT1,ratio18_1, true);
motor intake (PORT8, ratio18_1, false );
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
void drive(int Lspeed, int Rspeed, int waitTime){
  LM.spin(forward,Lspeed, pct);
  RM.spin(forward,Rspeed, pct);
  wait(waitTime, msec);

}
void driveStop(){
  LM.stop(brake);
  RM.stop(brake);
}


void inchdrive( float inches) 
{
  LM.setPosition(0,rev);
  float x = LM.position(rev) * 3.1415 * 4;
  float error = inches - x;
  float accuracy = 0.2;
  float kp = 5;
  while (fabs(error)>accuracy)
  {
    float speed = kp*error;
    drive(speed, speed, 10); 
    x = LM.position(rev) * 3.1415 * 4;
    error = inches - x;
    Brain.Screen.printAt(10, 50,"inches = %.2f",x);
  }
  Brain.Screen.printAt(10, 70,"done");
  driveStop();
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

void autonomous(void) 
{




  //inchdrive(30);
//intake.spin(forward, 100, pct);
//wait(1.1, sec);
////intake.stop();
//inchdrive(-20);
//drive(-50, 50, 460);
//nchdrive(20);
//driveStop();


//inchdrive(27);
//wait(1, sec);
//drive(-50,50, 530);
//inchdrive(23);
//intake.spin(forward, 100, pct);
//wait(5, sec);
//intake.stop();
//driveStop();


inchdrive(33);
wait(1, sec);
drive(50,-50, 500);
inchdrive(23);
intake.spin(forward, 100, pct);
wait(5, sec);
intake.stop();
driveStop();

//Brain.Screen.printAt(10,20, "Hello");
//Brain.Screen.setPenColor(red);
//Brain.Screen.setFillColor(blue);
//Brain.Screen.drawCircle(240, 120, 125);
//Brain.Screen.setPenColor(purple);
//Brain.Screen.setFillColor(green);
//Brain.Screen.drawRectangle(200, 120, 50, 50);
// drive(50,50, 4600);
// drive(-50, 50, 460);
// drive(50, 50, 2000);
// drive(-50, 50, 240);
// drive(50, 50, 2400);
// drive(-50, 50, 250);
// drive(50, 50, 2550);
// drive(-50, 50, 550);
 //drive(50, 50, 3000);

//driveStop();
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
      intake.spin(forward, -100, pct );
    }
    else {
      intake.stop();
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
