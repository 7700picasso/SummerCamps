/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/27/2026, 1:57:38 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

competition Competition;

brain Brain;
motor leftMotor(PORT1, ratio18_1, false);
motor rightMotor(PORT10,ratio18_1, true);
motor arm = motor(PORT2, ratio18_1, false);
controller Controller1 = controller(primary);

void drive(int lspeed, int rspeed, int wt){
  leftMotor.spin(forward, lspeed, pct);
  rightMotor.spin(forward, rspeed, pct);
  wait(wt, msec);
}

void brakeMotor (){
  leftMotor.stop(brake);
  rightMotor.stop(brake);
}

void pre_auton(){

}

void armMove(int speed, int waittime){
  arm.spin(forward, speed, percent);
  wait(waittime, msec);
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

  drive(50,50,2200);
  drive(50,-50,600);
  drive(50,50,1650);
  drive(-50,50,500);
  drive(50,50,1700);
  drive(-50,50,600);
  drive(50,50,2000);
  drive(50,-50,600);
  drive(32,32, 1700);
  brakeMotor();
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

    int left = Controller1.Axis3.position();
    int right = Controller1.Axis2.position();
    
    drive(left, right, 10);

    if(Controller1.ButtonL1.pressing()){
      armMove(50, 10);
    }
    else if(Controller1.ButtonL2.pressing()){
      armMove(-50, 10);

    }

    else{
      arm.stop(brake);
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
