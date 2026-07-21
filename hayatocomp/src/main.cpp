/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/21/2026, 3:07:40 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// Define your global instances of motors and controller here
controller Controller1 = controller(primary);
motor LM = motor(PORT18, ratio18_1, false);
motor RM = motor(PORT17, ratio18_1, true);

// Movement functions
void drive(int Lspeed, int Rspeed, int wt) {
  LM.spin(forward, Lspeed, pct);
  RM.spin(forward, Rspeed, pct);
  wait(wt, msec);
}

void driveBrake() {
  LM.stop(brake);
  RM.stop(brake);
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // All activities that occur before the competition starts
}

/*---------------------------------------------------------------------------*/
/*                              Autonomous Task                              */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
while(true){
  drive(50, 50, 2000);
  driveBrake();
  drive(-50, -50, 2000);
  driveBrake();
}
}

/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  while (true) {
    int forwardSpeed = Controller1.Axis3.position();
    int turnSpeed = Controller1.Axis3.position();
    
    int leftSpeed = forwardSpeed + turnSpeed;
    int rightSpeed = forwardSpeed - turnSpeed;

    LM.spin(forward, leftSpeed, pct);
    RM.spin(forward, rightSpeed, pct);

    wait(20, msec); 
  }
}

/*---------------------------------------------------------------------------*/
/*                                Main Task                                  */
/*---------------------------------------------------------------------------*/

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