/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      7/21/2026, 3:07:26 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

vex::brain Brain;
motor LM = motor(PORT1, ratio18_1, true);
motor RM = motor(PORT19, ratio18_1, false);
motor BLM = motor(PORT17, ratio18_1, true);
motor BRM = motor(PORT20, ratio18_1, false);
controller Potato = controller(primary);
double pi = 3.14159265;
float dia = 4.0;
float gearRatio = 60.0/48.0;
//movement functions here

void drive(int Lspeed, int Rspeed, int wt){
  LM.spin(forward, Lspeed, pct);
  RM.spin(forward, Rspeed, pct);
  BLM.spin(forward, Lspeed, pct);
  BRM.spin(forward, Rspeed, pct);
  wait(wt, msec);
}

void driveBrake(){
  LM.stop(brake);
  RM.stop(brake);
  BLM.stop(brake);
  BRM.stop(brake);
}


void inchDrive(float target, int speed){
  float x = 0;
  LM.setPosition(0, rev);
  x = LM.position(rev)*dia*pi*gearRatio;
  if (target >= 0){
    while(x < fabs(target)){
      drive(speed, speed, 10);
      x = LM.position(rev)*dia*pi*gearRatio;
      Brain.Screen.printAt(10, 20, "inches = %0.2f", x);
    }
  }
  else if(target < 0){
    while(x < fabs(target)){
      drive(-speed, -speed, 10);
      x = -LM.position(rev)*dia*pi*gearRatio;
      Brain.Screen.printAt(10, 20, "inches = %0.2f", x);
    }
  
  }
  driveBrake();

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
  inchDrive(25, 25);
  wait(300, msec);
  drive(-25, 25, 780);
  driveBrake();
  wait(300, msec);
  inchDrive(20, 25);
  wait(300, msec);
  drive(-25, 25, 760);
  driveBrake();
  wait(300, msec);
  inchDrive(25, 25);
  wait(300, msec);
  drive(27, -25, 760);
  driveBrake();
  wait(300, msec);
  inchDrive(19, 25);
  wait(300, msec);
  drive(-25, 25, 740);
  driveBrake();
  wait(300, msec);
  inchDrive(-21, 25);
  driveBrake();
}
  // drive(50, 50, 1000);
  // driveBrake();
  // wait(500, msec);
  // drive(50, -50, 710);
  // driveBrake();
  // wait(500, msec);
  // drive(-50, -50, 1100);
  // driveBrake();
  // wait(500, msec);
  // drive(-50, 50, 670);
  // driveBrake();
  // wait(500, msec);
  // drive(-50, -50, 1300);
  // driveBrake();
  // wait(500, msec);
  // drive(50, -50, 710);
  // driveBrake();
  // wait(500, msec);
  // drive(-50, -50, 1000);
  // driveBrake();
  // wait(500, msec);
  // drive(50, -50, 710);
  // driveBrake();
  // wait(500, msec);
  // drive(-50, -50, 900);
  // //Halfway
  // driveBrake();
  // wait(500, msec);
  // drive(50, 50, 900);
  // driveBrake();
  // wait(500, msec);
  // drive(50, -50, 710);
  // driveBrake();
  // wait(500, msec);
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

void usercontrol(void) {
  // User control code here, inside the loop
  float speedCap = 1;
  while (true) {
    int leftSpeed = Potato.Axis3.position();
    int rightSpeed = Potato.Axis2.position();

    drive(static_cast<int>(leftSpeed*speedCap), static_cast<int>(rightSpeed*speedCap), 10);

    if(Potato.ButtonL1.pressing()){
      speedCap = 0.25;
    }
    else if(Potato.ButtonL2.pressing()){
      speedCap = 0.5;
    }
    else if(Potato.ButtonR1.pressing()){
      speedCap = 0.75;
    }
    else if(Potato.ButtonR2.pressing()){
      speedCap = 1;
    }




    if(Potato.ButtonB.pressing()){
      Brain.Screen.clearScreen();
      Brain.Screen.printAt(135, 60, " __         __");
      Brain.Screen.printAt(135, 80, "/  \\.-\"\"\"-./  \\");
      Brain.Screen.printAt(135, 100, "\\    -   -    /");
      Brain.Screen.printAt(135, 120, " |   o   o   |");
      Brain.Screen.printAt(135, 140, " \\  .-'''-.  /");
      Brain.Screen.printAt(135, 160, "  '-\\__Y__/-'");
      Brain.Screen.printAt(135, 180, "     `---`");
    }
    else if(Potato.ButtonA.pressing()){
      Brain.Screen.clearScreen();
      Brain.Screen.printAt(135, 60, " __         __");
      Brain.Screen.printAt(135, 80, "/  \\.-\"\"\"-./  \\");
      Brain.Screen.printAt(135, 100, "\\    \\   /    /");
      Brain.Screen.printAt(135, 120, " |   o   o   |");
      Brain.Screen.printAt(135, 140, " \\  .-'''-.  /");
      Brain.Screen.printAt(135, 160, "  '-\\__Y__/-'");
      Brain.Screen.printAt(135, 180, "     `---`");
    }
    else if(Potato.ButtonX.pressing()){
      Brain.Screen.clearScreen();
      Brain.Screen.printAt(135, 0, "          .=     ,        =.");
      Brain.Screen.printAt(135, 20, "  _  _   /'/    )\\,/,/(_   \\ \\");
      Brain.Screen.printAt(135, 40, "   `//-.|  (  ,\\)\\//\\)\\/_  ) |");
      Brain.Screen.printAt(135, 60, "   //___\\   `\\\\/\\/\\/\\///'  /");
      Brain.Screen.printAt(135, 80, ",-\"~`-._ `\"--'_   `\"\"\"`  _ \\`'\"~-,_");
      Brain.Screen.printAt(135, 100, "\\       `-.  '_`.      .'_` \\ ,-\"~`/");
      Brain.Screen.printAt(135, 120, " `.__.-'`/   (-\\        /-) |-.__,'");
      Brain.Screen.printAt(135, 140, "   ||   |     \\O)  /^\\ (O/  |");
      Brain.Screen.printAt(135, 160, "   `\\  |         /   `\\    /");
      Brain.Screen.printAt(135, 180, "     \\  \\       /      `\\ /");
      Brain.Screen.printAt(135, 200, "      `\\\\ `-.  /' .---.--.\\");
      Brain.Screen.printAt(135, 220, "        `\\\\/`~(, '()      ('");
      Brain.Screen.printAt(135, 240, "         /(O) \\\\   _,.-.,_)");
      Brain.Screen.printAt(135, 260, "        //  \\\\ `\\\'`      /");
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
