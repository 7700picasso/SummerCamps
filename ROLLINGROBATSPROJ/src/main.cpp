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

pneumatics claw = pneumatics(Brain.ThreeWirePort.A);

motor leftMotor(PORT1, ratio18_1, false);
motor rightMotor(PORT10,ratio18_1, true);
<<<<<<< HEAD
motor arm = motor(PORT2, ratio18_1, false);
=======
motor arm(PORT2, ratio18_1, false);
>>>>>>> 83df468303011140af6040080aebef524eb69d5d
controller Controller1 = controller(primary);

void drive(int lspeed, int rspeed, int wt){
  leftMotor.spin(forward, lspeed, pct);
  rightMotor.spin(forward, rspeed, pct);
  wait(wt, msec);
}

void armMove(int speed, int waittime){
  arm.spin(forward, speed, percent);
  wait(waittime, msec);
}

void brakeMotor (){
  leftMotor.stop(brake);
  rightMotor.stop(brake);
}

void inchDrivePID(double inches, int maxSpeed, int minSpeed) {

  leftMotor.setPosition(0, degrees);

  double wheelDiameter = 3.25;
  double pi = 3.14159;
  double gearRatio = 1.0 / 1.0;

  double circumference = wheelDiameter * pi;
  double wheelRotations = inches / circumference;
  double motorRotations = wheelRotations * gearRatio;
  double targetDegrees = motorRotations * 360.0;

  double kP = 0.1;
  double error = targetDegrees - leftMotor.position(degrees);

  while (fabs(error) > 5) {
    error = targetDegrees - leftMotor.position(degrees);

    double speed = fabs(error) * kP;

    if (speed > maxSpeed) {
      speed = maxSpeed;
    }

    if (speed < minSpeed) {
      speed = minSpeed;
    }

    if(error > 0){
      drive(speed, speed, 10);
    } else{
      drive(-speed, -speed, 10);
    }
    }
    brakeMotor();
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

  
  claw.set(true);
  drive(50,50,150);
  armMove(50,500);
  drive(-50,50,700);
  arm.stop(brake);
  drive(-50,-50,400);
  armMove(-50,400);
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

    if(Controller1.ButtonL1.pressing()){
      armMove(50, 10);
    }
    else if(Controller1.ButtonL2.pressing()){
      armMove (-50, 10);
    }

    else{
      arm.stop(brake);
    }


    if(Controller1.ButtonR1.pressing()){
      claw.open();
    }
    else if(Controller1.ButtonR2.pressing()){
      claw.close();
    }
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
