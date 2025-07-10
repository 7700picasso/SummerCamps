/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
motor LM =motor(PORT13,ratio18_1,true);
motor RM =motor (PORT20,ratio18_1,false);
motor intake = motor(PORT7,ratio18_1, true);
motor LM2=motor(PORT14,ratio18_1,true);
motor RM2=motor(PORT18, ratio18_1, false);
controller Controller1;

float dia=4.00;
float pi=3.14;



void drive (int lspeed, int rspeed, int wt){ 
  LM.spin(fwd,lspeed,pct);
  RM.spin(fwd,rspeed,pct);
  LM2.spin(fwd,lspeed,pct);
  RM2.spin(fwd, rspeed,pct);
  wait(wt,msec);
}

void stop(){
LM.stop(brake);
RM.stop(brake);
LM2.stop(brake);
RM2.stop(brake);
}


void inchdrive(float inches){
  float x=0;
  LM.resetPosition();
  x=LM.position(rev)*dia*pi;
  if (inches>0){

  
while (x <= inches){
 drive(50,50,20);
 x=LM.position(rev)*dia*pi*1.5;

 Brain.Screen.printAt(50,10, "Distance=%0.2f",x);
}}

else if (inches <0){

  
while (x <= fabs(inches)){
 drive(-50,-50,20);
 x=-LM.position(rev)*dia*pi*1.5;

 Brain.Screen.printAt(50,10, "Distance=%0.2f",x);
}}


 stop();

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
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

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
inchdrive(30);
intake.spin(fwd, 100, pct);
//intake.stop(); 

// wait(1,sec);
// intake.spin(fwd,100,pct);
}









  
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) 
{
  // User control code here, inside the loop
while (1) {
int lstick= (Controller1.Axis3.position()) ;
int rstick= (Controller1.Axis2.position() );
drive(lstick,rstick,10);
if(Controller1.ButtonR1.pressing())
{
  intake.spin(fwd,100,pct);
}
else if(Controller1.ButtonR2.pressing())
{
  intake.spin(reverse, 100, pct);
}
else{
  intake.stop();
}
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based o5n feedback from the joysticks.

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