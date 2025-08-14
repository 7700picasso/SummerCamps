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

inertial gyro1 = inertial(PORT18);


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

void inchDrive(float target)
{
    LF.setPosition(0,turns);
    float x = 0;
    float error = target;
    float kp = 10;

    while(fabs(error)>0.5){
        float speed = kp*error;
        drive(speed,speed,10);
        x = LF.position(turns)*M_PI*4*1.5;
        error = target - x;
    }
    driveStop();
    
}

void turnTo(float target){
    float error = target - gyro1.rotation();
    float kp = 0.5;
    while(fabs(error)>2){
        error  = target - gyro1.rotation();
        while(error > 180){
            error  = error - 360;
            
        }
        
        while(error > 180){
            error  = error + 360;
        }
        float speed  = error * kp;
        drive(speed,-speed ,5);
    }
    driveStop();
}
int clamp(int x, int lower, int upper){
    return fmin(fmax(x, lower),upper);
}

void auton(){
    
    turnTo(90);
    turnTo(-135);
    turnTo(0);

    
    
    

}

void drivercontrol(){

    int x = 100;
    int y = 100;

    Brain.Screen.setPenColor(white);
    //Brain.Screen.printAt(0,80,"hi");
    while (1){
        int lstick = controller1.Axis3.position();
        int rstick = controller1.Axis2.position();
        drive(lstick,rstick,10);

        
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

        //float angle = gyro1.heading();

        controller1.Screen.setCursor(1,1);
        controller1.Screen.print("heading = %.2f    ",gyro1.heading());
        controller1.Screen.setCursor(2,1);
        controller1.Screen.print("yaw = %.2f    ",gyro1.yaw());
        controller1.Screen.setCursor(3,1);
        controller1.Screen.print("rot = %.2f    ",gyro1.rotation());
            this_thread::sleep_for(20);

    }
}
int main(){

    gyro1.calibrate();
    waitUntil(!gyro1.isCalibrating());

    Competition.drivercontrol(drivercontrol);
    Competition.autonomous(auton);
    while(true){
        wait(100,msec);
    }
}