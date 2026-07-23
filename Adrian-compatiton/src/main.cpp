/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      7/21/2026, 3:07:57 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
vex::brain Brain;

vex::motor LM = motor(PORT2, ratio18_1, false);
vex::motor RM = motor(PORT3, ratio18_1, true);
controller C1 = controller(primary);

float pi = 3.14159;
float dia = 4.0;
float gearRaitio = 60.0/48.0;

void drive(int lspeed, int rspeed, int wt){
  LM.spin(forward, lspeed, pct);
  RM.spin(forward, rspeed, pct);
  wait(wt, msec);

}

void driveBrake(){
  LM.stop(brake);
  RM.stop(brake);
}


void inchDrive(float target){

float x = 0; //loacal variable
  LM.setPosition(0, rev);
  x = LM.position(rev)*dia*pi*gearRaitio;
  
  if (target >= 0 ) {
    while (x <= target ) {
      drive(50, 50, 10);  
      x = LM.position(rev)*dia*pi*gearRaitio;
      Brain.Screen.printAt(10, 20, "inches = %0.2f", x);

    }
  }
  else if (target <0){
    while (x <=fabs(target)){
      drive(-50, -50, 10);
      x = LM.position(rev)*dia*pi*gearRaitio;
      Brain.Screen.printAt(10, 20, "inches = %0.2f", x);
    }
  }
  drive(0, 0, 0);
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
    inchDrive(22);
    wait(500, msec);
    drive(-50, 50, 550);
    driveBrake();
    wait(500, msec);
    inchDrive(21);
    wait(500, msec);
    drive(-50, 50, 600);
    driveBrake();


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
  while (1) {
    int leftSpeed = C1.Axis2.position();
    int rightSpeed = C1.Axis3.position();

    drive(leftSpeed, rightSpeed, 10);

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




