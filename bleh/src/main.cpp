/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/28/2025, 1:27:49 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

competition Competition;
// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;
controller Controller;
motor LF = motor(PORT2, ratio18_1, true);
motor RF = motor(PORT1, ratio18_1, false);
motor LB = motor(PORT4, ratio18_1, true);
motor RB = motor(PORT3, ratio18_1, false);
inertial gyro1 = inertial(PORT10);

void drive(int lspeed, int rspeed, int wt)
{
    LB.spin(fwd, lspeed, pct);
    RB.spin(fwd, rspeed, pct);
    LF.spin(fwd, lspeed, pct);
    RF.spin(fwd, rspeed, pct);
    wait(wt, msec);
}

void drivestop(brakeType mode = brake)
{
    LF.stop(mode);
    RF.stop(mode);
    LB.stop(mode);
    RB.stop(mode);
}

void inchdrive(float target)
{
    LF.setPosition(0, rev);
    RF.setPosition(0, rev);
    float x = ((LF.position(rev) + RF.position(rev)) / 2) * M_PI * 4 * 3.0 / 2;
    while (x < target)
    {
        drive(50, 50, 10);
        x = ((LF.position(rev) + RF.position(rev)) / 2) * M_PI * 4 * 3.0 / 2;
    }
    drivestop();
}
#include <iostream>
void turnTo(float angle)
{
    float error = angle - gyro1.rotation();
    float kp = 0.75;
    while (fabs(error) > 1)
    {
        drive(error * kp, -error * kp, 10);
        error = angle - gyro1.rotation();

        while (error > 180)
        {
            error -= 360;
        }
        while (error < -180)
        {
            error += 360;
        }
        std::cout << error << std::endl;
    }
    Brain.Screen.printAt(10, 100, "angle = %.2f", gyro1.rotation());
    drivestop();
}

void autonomous()
{
    int x = 30;
    while (true)
    {
        turnTo(x);
        wait(500, msec);
        x += 30;
    }
    // turnTo(0);
    // inchdrive(100);
    // drive(-40,40,400);
    // drivestop();
    // inchdrive(24);
    // drive(-40,40,500);
    // drivestop();
}

void drivercontrol()
{
    int X = 9;
    Brain.Screen.printAt(10, 50, "Hebhjhghllosvfsvsvs V5");
    Brain.Screen.drawCircle(100, 100, 50);
    Brain.Screen.drawRectangle(100, 100, 100, 100);

    int x = 100;
    int y = 100;
    drivestop(hold);
    while (1)
    {

        // if (Controller.ButtonLeft.pressing()){
        //     x--;
        // }else if  (Controller.ButtonRight.pressing()){
        //     x++;
        // }else if (Controller.ButtonDown.pressing()){
        //     y++;
        // }else if (Controller.ButtonUp.pressing()){
        //     y--;
        // }

        x += Controller.Axis1.position() / 20;
        y -= Controller.Axis2.position() / 20;
        Brain.Screen.drawCircle(x, y, 10);
        Brain.Screen.drawCircle(y, x, 10);
        Brain.Screen.printAt(10, 70, "pos = (%d, %d)", x, y);
        x = fmax(0, x);
        x = fmin(480, x);

        int lstick = Controller.Axis3.position();
        int rstick = Controller.Axis2.position();

        // tank
        drive(lstick, rstick, 10);
        /*
        yaw()
        rotation()
        heading()
        */
        Controller.Screen.setCursor(1, 1);
        Controller.Screen.print("angle = %.2f", gyro1.rotation());

        wait(10, msec);
        // arcade
        //  drive(lstick+rstick, lstick-rstick,10);

        // if(x <= 240 && y > 136){
        //     Brain.Screen.setFillColor(yellow);
        // }else if(x <= 240 && y < 137){
        //     Brain.Screen.setFillColor(red);
        // }else if(x > 240 && y <= 136){
        //     Brain.Screen.setFillColor(green);
        // }else{
        //     Brain.Screen.setFillColor(blue);
        // }

        Brain.Screen.drawCircle(x, y, 10);
        this_thread::sleep_for(8);
    }

    // Allow other tasks to run
}
// define your global instances of motors and other devices here

int main()
{
    gyro1.calibrate();
    waitUntil(not gyro1.isCalibrating());

    Competition.autonomous(autonomous);
    Competition.drivercontrol(drivercontrol);
    while (true)
    {
        wait(100, msec);
    }
}
