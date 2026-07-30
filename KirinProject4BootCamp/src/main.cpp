/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      7/27/2026, 1:57:57 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;
brain Brain;
motor leftMotor(PORT10, ratio18_1, false);
motor rightMotor(PORT9, ratio18_1, true);

controller Controller1 = controller(primary);

motor arm = motor(PORT8, ratio18_1, false);

inertial isensor = inertial(PORT4);

// A global instance of competition
competition Competition;

pneumatics claw = pneumatics(Brain.ThreeWirePort.A);

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
  leftMotor.spin(forward, lspeed, pct);
  rightMotor.spin(forward, rspeed, pct);
  wait(wt, msec);
}


void brakeMotor(){
  leftMotor.stop(brake);
  rightMotor.stop(brake);
}


void inchDrive(double inches,int maxSpeed, int minSpeed) {
  leftMotor.setPosition(0, degrees);
  double wheelDiameter = 3.25;
  double pi = 3.14159;
  double gearRatio = 1.0 / 1.0;

  double circumfernce = wheelDiameter * pi;
  double wheelRotations = inches / circumfernce;
  double motorRotations =  wheelRotations * gearRatio;
  double targetDegrees = motorRotations * 360;

  double kP = 0.1;
  double error = targetDegrees - leftMotor.position(degrees);


  while(fabs(error) > 5 ) {
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


}

void turnP(double targetDegrees, int maxSpeed,int minSpeed){
  isensor.setRotation(0, degrees);

  double kP = 0.1;
  double error = targetDegrees - isensor.rotation(degrees);
  
  while (fabs(error) > 1.0){
    error = targetDegrees  - isensor.rotation(degrees);
    double speed = fabs(error) * kP;

    if(speed > maxSpeed){
      speed = maxSpeed;
    }

    if (speed < minSpeed){
      speed = minSpeed;
    }

    if (error > 0){
      drive(speed, - speed, 10);
    } else {
      drive(-speed, speed, 10 );
    }
  wait(10, msec);
    brakeMotor();
  }
  
}

void armMove(int speed, int waittime){
  arm.spin(forward, speed, percent);
  wait(waittime,msec);

}

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
   
 


  brakeMotor();
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


    if (Controller1.ButtonL1.pressing()){
      Brain.Screen.print("moving arm");
      armMove(-20, 10);
    }
    else if (Controller1.ButtonL2.pressing()){
      armMove (20,10);
    }
    else{
      arm.stop(brake);
    }

    if (Controller1.ButtonR1.pressing()){
      claw.open();
    }

    else if(Controller1.ButtonR2.pressing()){
      claw.close();
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

isensor.calibrate();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
