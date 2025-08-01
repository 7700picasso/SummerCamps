/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/28/2025, 1:28:41 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
using namespace vex;
competition Competititon;
// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;
controller Controller1;
// define instances here
motor LF = motor(PORT1, ratio18_1, false);
motor RF = motor(PORT2, ratio18_1, true);
motor LB = motor(PORT6, ratio18_1, false);
motor RB = motor(PORT3, ratio18_1, true);

// GYRO
inertial gyro1 = inertial(PORT4);

void drive(int lspeed, int rspeed, int wt)
{
    LF.spin(fwd, lspeed, pct);
    RF.spin(fwd, rspeed, pct);
    LB.spin(fwd, lspeed, pct);
    RB.spin(fwd, rspeed, pct);
    wait(wt, msec);
}

void drivestop()
{
    LF.stop(brake);
    RF.stop(brake);
    LB.stop(brake);
    RB.stop(brake);
}

void inch_drive(float target)
{
    LF.setPosition(0, rev);
    RF.setPosition(0, rev);
    float x = ((LF.position(rev) + RF.position(rev) / 2) * M_PI * 4 * 3 / 2);
    float error = target - x;
    float kp = 5;
    while (fabs(error) > 0.5)
    {
        error = target - x;
        float speed = kp * error;
        drive(speed, speed, 10);
        x = ((LF.position(rev) + RF.position(rev) / 2) * M_PI * 4 * 3 / 2);
    }
    Brain.Screen.printAt(0, 120, "Distance: %.2f      ",x );
    drivestop();
}

void turnTo(float angle)
{
    float error = angle - gyro1.rotation();
    float kpn = 0.6;
    while (fabs(error) > 3)
    {
        drive(-error * kpn, error * kpn, 100);
        error = angle - gyro1.rotation();
        while (error > 180)
        {
            error -= 360;
        }
        while (error < -180)
        {
            error += 360;
        }
        Brain.Screen.printAt(10, 100, "error = %.2f", error);
    }
    drivestop();
    Brain.Screen.print("out of loop");
}


void autonomous()
{
    int distance = 48;
    inch_drive(distance);
    turnTo(60);
    inch_drive(distance);
    turnTo(60 * 2);
    inch_drive(distance);
    turnTo(60 * 3);
    inch_drive(distance);
    turnTo(60 * 4);
    inch_drive(distance);
    turnTo(60 * 5);
    inch_drive(distance);
    turnTo(60 * 6);
    
    

    
}

void drivercontrol()
{
    int x = 240;
    int y = 136;
    int size = 15;
    while (true)
    {
        // controller inputs
        int lstick = Controller1.Axis3.position();
        int rstick = Controller1.Axis1.position();

        // print on Controller
        Controller1.Screen.setCursor(1, 1);
        Controller1.Screen.print("angle = %.2f", gyro1.yaw());

        // arcade
        drive(lstick - rstick, lstick + rstick, 10);
        wait(10, msec);
    }
}

int main()
{
    gyro1.calibrate();
    waitUntil(!gyro1.isCalibrating());
    Competititon.autonomous(autonomous);
    Competititon.drivercontrol(drivercontrol);
}
