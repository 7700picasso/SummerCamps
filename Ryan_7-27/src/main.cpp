/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      7/27/2026, 2:17:32 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
brain Brain;
motor leftMotor(PORT1, ratio18_1, true);
motor rightMotor(PORT2, ratio18_1, false);
motor armMotor(PORT4, ratio18_1, false);
digital_out claw (Brain.ThreeWirePort.A); 
controller Controller1 = controller(primary);

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
void drive(int lspeed, int rspeed, int wt){
  leftMotor.spin(forward,lspeed, pct);
  rightMotor.spin(forward, rspeed, pct);

  wait(wt, msec);
}

void armMove(int speed, int waittime){
  armMotor.spin(forward, speed, percent);
  wait(waittime, msec);
}
void driveBrake(){
  leftMotor.stop(brake);
  rightMotor.stop(brake);
}
void pre_auton(void) {

}

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...


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

    //drive
    int left = Controller1.Axis2.position();
    int right = Controller1.Axis3.position();

    drive(left, right, 10);
    //Arm Movement
    if(Controller1.ButtonL1.pressing()){
    armMove(50, 10);
   }else if(Controller1.ButtonL2.pressing()){
    armMove(-50, 10);
    }
    else{
      armMotor.stop(brake);
    }

      //Claw Movement
      if(Controller1.ButtonR1.pressing()){
    claw.set(true); 
   }else if(Controller1.ButtonR2.pressing()){
    claw.set(false); 
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
