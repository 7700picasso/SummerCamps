/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Hunter Rieves                                             */
/*    Created:      8/11/2025, 1:33:29 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;
competition Competition;
vex::brain Brain;
controller controller1;

motor LF = motor(PORT11, ratio18_1,true);
motor RF= motor(PORT13, ratio18_1,false);
motor LB = motor(PORT12, ratio18_1,true);
motor RB = motor(PORT14, ratio18_1,false);

void drive(int left, int right, int wt){
    LF.spin(fwd,left,pct);
    RF.spin(fwd,right,pct);
    LB.spin(fwd,left,pct);
    RB.spin(fwd,right,pct);
    wait(wt,msec);
}

void driveStop(){
    RF.stop(brake);
    LF.stop(brake);
    RB.stop(brake);
    LB.stop(brake);
}
int clamp(int x, int lower, int upper){
    return fmin(fmax(x, lower),upper);
}

void auton(){
    drive(50,50,2750);
    driveStop();
    drive(50,-50,250);
    driveStop();

    drive(50,50,2750);
    driveStop();
    drive(50,-50,250);
    driveStop();

    drive(50,50,1900);
    driveStop();
    drive(50,-50,200);
    driveStop();

    drive(50,50,3150);
    driveStop();
    drive(50,-50,250);
    driveStop();
    

}

void drivercontrol(){

    int x = 100;
    int y = 100;

    Brain.Screen.setPenColor(white);
    //Brain.Screen.printAt(0,80,"hi");
    while (1){
    if(controller1.ButtonB.pressing()){
            Brain.Screen.clearScreen();
        }
        x+=controller1.Axis4.position()/20;
        y-=controller1.Axis3.position()/20;
        if(controller1.ButtonUp.pressing()){
            y-=5;
        }
        if(controller1.ButtonDown.pressing()){
            y+=5;
        }
        if(controller1.ButtonLeft.pressing()){
            x-=5;
        }
        if(controller1.ButtonRight.pressing()){
            x+=5;
        }
        x=clamp(x,0,480);
        y=clamp(y,0, 240);

        if (x >= 240 && y <= 135)
        {
            Brain.Screen.setFillColor(green);
            Brain.Screen.setPenColor(green);
        }
        else if (x >= 240 && y >= 135)
        {
            Brain.Screen.setFillColor(blue);
            Brain.Screen.setPenColor(blue);
        }
        else if (x <= 240 && y >= 135)
        {
            Brain.Screen.setFillColor(yellow);
            Brain.Screen.setPenColor(yellow);
            
        }
        else
        {
            Brain.Screen.setFillColor(red);
            Brain.Screen.setPenColor(red);
        }

        Brain.Screen.drawCircle(x, y, 10);
            this_thread::sleep_for(20);

    }
}

int main(){
    Competition.drivercontrol(drivercontrol);
    Competition.autonomous(auton);
    while(true){
        wait(100,msec);
    }
}