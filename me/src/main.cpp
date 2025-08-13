/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      8/11/2025, 1:40:17 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;
competition Competition;
// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;
controller controller1;

motor LF = motor(PORT6,ratio18_1,false);
motor RF = motor(PORT2,ratio18_1,true);
// define your global instances of motors and other devices here

void drive(int left, int right, int wt){
    LF.spin(fwd,left,pct);
    RF.spin(fwd,right,pct);
    wait(wt,msec);
}
void driveStop(){
    LF.stop(brake);
    RF.stop(brake);
}
void inchDrive(float target){
    LF.setPosition(0,turns);
    float x = 0;
    float error = target;
    float kp = 8;
    while(fabs(error)>0.3){
        float speed = kp*error;
        drive(speed,speed,10);
        x = LF.position(turns)*M_PI*4;
        error = target - x;
    }
    driveStop();
}


int clamp(int x, int lower, int upper){
    
    // ANOTHER WAY TO UNDERSTAND BELOW STATEMENT
    // if (x<lower){
    //     return lower;
    // }
    // else if (x>upper){
    //     return upper;
    // }
    // else {
    //     return x;
    // }
    return fmin(fmax(x, lower),upper);
}
void auton(){
    // int a = 0;
    // while(a<100) {
    //     drive(100,100,150);
    //     driveStop();
    //     drive(-100,-100,150);
    //     driveStop();
    //     a+=1;
    inchDrive(24);
    wait(200,msec);
    inchDrive(-24); q

    // drive(50,50,3500);
    // driveStop();
    // drive(35,50,1350);
    // driveStop();
    // drive(50,50,3000);
    // driveStop();
    // drive(-50,50,650);
    // driveStop();
    // drive(50,50,3500);
    // driveStop();
    // drive(-50,50,650);
    // driveStop();
    // drive(50,50,4000);
    // driveStop();
}
void drivercontrol()
{
    int x = 100;
    int y = 100;
    while (1)
    {
        
        int lstick = controller1.Axis3.position();
        int rstick = controller1.Axis2.position();
        drive(lstick,rstick,10);

        
        if (controller1.ButtonB.pressing()){
            Brain.Screen.clearScreen();
        }
        if (controller1.ButtonA.pressing()){
            Brain.Screen.setPenColor(transparent);
            Brain.Screen.printAt(x,y,"I LOVE DIDDY",x,y);
        }
        // TWO WAYS TO ADD BOUNDERIES
        
        //1.
        // if(controller1.ButtonUp.pressing() && y>0){
        //     y-=2;
        // }
        // /if(controller1.ButtonDown.pressing() && y<240){
        //     y+=2;
        // }
        // if(controller1.ButtonRight.pressing() && x<480){
        //     x+=2;
        // }
        // if(controller1.ButtonLeft.pressing() && x>0){
        //     x-=2;
        // }
        
        // 2.
        // x = fmax[0,x];
        // x = fmin(480,x); 
        // y = fmax(0,y);
        // y = fmin(240,y);
        
        x+=controller1.Axis4.position()/20;
        y-=controller1.Axis3.position()/20;

        if(controller1.ButtonUp.pressing()){
             y-=2;
        }
        if(controller1.ButtonDown.pressing()){
             y+=2;
        }
        if(controller1.ButtonRight.pressing()){
             x+=2;
        }
        if(controller1.ButtonLeft.pressing()){
             x-=2;
        }
        x=clamp(x,0,480);
        y=clamp(y,0,240);
        // Brain.Screen.printAt(x, y, "u suck, get a life", x, y);
        if (x < 240 && y < 135)
        {
            Brain.Screen.setFillColor(red);
            Brain.Screen.setPenColor(red);
        }
        else if (x < 240 && y > 134) 
        {
            Brain.Screen.setFillColor(yellow);
            Brain.Screen.setPenColor(yellow);
        }
        else if (x > 239 && y < 135)
        {
            Brain.Screen.setFillColor(green);
            Brain.Screen.setPenColor(green);
        }
        else
        {
            Brain.Screen.setFillColor(blue);
            Brain.Screen.setPenColor(blue);
        }
        // Brain.Screen.printAt(x,y,"pressed at %d, %d",x,y);
        Brain.Screen.drawCircle(x, y, 5);
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}


int main(){
    Competition.drivercontrol(drivercontrol);
    Competition.autonomous(auton);
    while(true){
        wait(100,msec);
    }
}