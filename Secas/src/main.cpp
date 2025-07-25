/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/21/2025, 1:32:38 PM                                     */
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
motor LM (PORT1,ratio18_1, false); 
motor RM (PORT10,ratio18_1, true);
motor intake (PORT12, ratio18_1, false );
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
void drive(int Lspeed, int Rspeed, int waitTime){
  LM.spin(forward,Lspeed, pct );
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
  float x= LM.position(rev) * 3.1415 * 4;
  float error = inches - x;
  float accuracy = 0.2;
  float kp = 5;
  while(fabs(error)>accuracy)
  {
    float speed = kp*error;
    error = inches - x;
    drive(speed, speed, 10);
    x = LM.position(rev) *3.1415 * 4;
    //Brain.Screen.printAt(10,50, "inches = %.2f", "error = %.2f", x,error);
  }
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
 intake.spin(fwd, 43, pct); 
 
 inchdrive  (24);
  
 intake.stop();
 
 drive (-50, 50, 340);
 driveStop();

 inchdrive (float (13.99));


 intake.spin(reverse, 55, pct);
 wait(2,sec);
intake.stop();

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
 int Lspeed=Controller.Axis3.position(pct)*.75; 
 int Rspeed=Controller.Axis2.position(pct)*.75;
 drive(Lspeed, Rspeed,10);


 if (Controller.ButtonR1.pressing()){
  intake.spin(forward, 100, pct);
 }
else if (Controller.ButtonR2.pressing()){
  intake.spin(forward ,-100, pct );
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
