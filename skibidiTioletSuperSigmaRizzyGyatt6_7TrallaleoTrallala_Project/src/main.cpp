/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      8/11/2025, 1:34:11 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;
competition Compertition;
// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;
controller controller1;
motor LF = motor(PORT11, ratio18_1, true);
motor RF = motor(PORT16, ratio18_1, false);


inertial gyro1=inertial(PORT8);
// define your global instances of motors and other devices here
void drive(int left, int right, int wt)
{
    LF.spin(fwd, left, pct);
    RF.spin(fwd, right, pct);
    wait(wt, msec);
}
void driveStop()
{
    LF.stop(brake);
    RF.stop(brake);
}
void inchDrive(float target)
{

    LF.setPosition(0,turns);
    float x=0;
    float error= target;
    float kp=5;
    while(fabs(error)>0.5){
        float speed=kp*error;

        drive(speed,speed,10);
        x=LF.position(turns)*M_PI*3.25* 5.0/3;
        error=target-x;
    }
    driveStop();
}
void turnTo(float target){
float error=target -gyro1.rotation();
float kp=1;
while(fabs(error)>2){
error=target-gyro1.rotation();
while(error>180){
    error=error-360;
}
while(error<-180){
    error=error+360;
}
float speed=error*kp;
drive(speed,-speed,10);
}
driveStop();

}

int clamp(int x, int lower, int upper)
{
    return fmin(fmax(x, lower), upper);
}

void auton()
{
    inchDrive(48);
    turnTo(-45);
     inchDrive(48);
    turnTo(-90);
     inchDrive(48);
    turnTo(-135);
     inchDrive(48);
    turnTo(-180);
     inchDrive(48);
    turnTo(-225);
     inchDrive(48);
    turnTo(-270);
     
}

void drivercontrol()
{

    Brain.Screen.printAt(10, 50, "Dom is super sigma");
    int x = 100;
    int y = 100;
    while (1)
    {
        int lstick = controller1.Axis3.position();
        int rstick = controller1.Axis1.position();
        //          drive(lstick,rstick,10);
        drive(lstick + rstick, lstick - rstick, 10);

        if (controller1.ButtonB.pressing())
        {
            Brain.Screen.clearScreen();
        }
        if (controller1.ButtonA.pressing())
        {
            Brain.Screen.print("Dommy is the best teacher  ");
        }

        if (controller1.ButtonUp.pressing())
        {
            y -= 5;
        }
        if (controller1.ButtonDown.pressing())
        {
            y += 5;
        }
        if (controller1.ButtonLeft.pressing())
        {
            x -= 5;
        }
        if (controller1.ButtonRight.pressing())
        {
            x += 5;
        }
        x = clamp(x, 0, 480);
        y = clamp(y, 0, 240);
        if (x >= 240 and y <= 135)
            Brain.Screen.setFillColor(red);
        else if (x <= 240 and y <= 135)
            Brain.Screen.setFillColor(yellow);
        else if (x <= 240 and y >= 135)
            Brain.Screen.setFillColor(green);
        else
            Brain.Screen.setFillColor(blue);

        // Brain.Screen.printAt(x, y, "pressed at %d, %d", x, y);

        Brain.Screen.drawCircle(x, y, 5);


        //float angle =gyro1.heading();
        controller1.Screen.setCursor(1,1);
        controller1.Screen.print("heading = %.2f.      ",gyro1.heading());
        controller1.Screen.setCursor(2,1);
        controller1.Screen.print("yaw=%.2f.   ", gyro1.yaw());
        controller1.Screen.setCursor(3,1);
        controller1.Screen.print("rot=%.2f.   ", gyro1.rotation());
        

        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
int main()
{
    gyro1.calibrate();
    waitUntil(!gyro1.isCalibrating());
    Compertition.drivercontrol(drivercontrol);
    Compertition.autonomous(auton);
    while (true)
    {
        wait(100, msec);
    }
}