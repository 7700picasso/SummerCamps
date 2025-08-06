/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       rollingrobots                                             */
/*    Created:      8/5/2025, 9:13:25 AM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
motor RM (PORT16, ratio18_1, false);
motor LM (PORT11, ratio18_1, true);
motor intake (PORT1, ratio18_1, false);
motor roller (PORT21, ratio18_1, false);
controller Controller;


// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */

void driveTrain(int rsp, int lsp, int wt) {

  RM.spin(forward, rsp, pct);
  LM.spin(forward, lsp, pct);
  wait(wt, msec);

}

void Stop(){

  RM.stop(brake);
  LM.stop(brake);

}



/*-----------------------------------EOF-------------------------------------*/

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

  driveTrain(50, 50, 3500);
  driveTrain(50, -50, 400); 
  driveTrain(50, 50, 2700);
  driveTrain(50, -50, 300); 
  driveTrain(50, 50, 3000);
  driveTrain(50, -50, 300); 
  driveTrain(50, 50, 2700);







  Stop();


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
    
    int lsp = Controller.Axis3.position(pct);
    int rsp = Controller.Axis2.position(pct);

    driveTrain(rsp, lsp, 10);

    if(Controller.ButtonR1.pressing()){
      intake.spin(forward, 100, pct);
    }
    else if (Controller.ButtonR2.pressing()){
      intake.spin(reverse, 100, pct);    
    }
    else if (Controller.ButtonL1.pressing()){
      roller.spin(forward, 100, pct); 
    }
    else if (Controller.ButtonL2.pressing()){
      roller.spin(reverse, 100, pct); 
    }
    else{
      intake.stop(brake);
      roller.stop(brake);
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
