/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/28/2025, 1:27:08 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;
competition Competition;
// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
controller Controller;
inertial gyro1 = inertial(PORT12);





// define your global instances of motors and other devices here
motor LF = motor(PORT1, ratio18_1, true);
motor RF = motor(PORT6, ratio18_1, false);
motor LB = motor(PORT11, ratio18_1, true);
motor RB = motor(PORT2, ratio18_1, false);

void drive(int lspeed,int rspeed, int wt){
    LF.spin(fwd,lspeed,pct);
    RF.spin(fwd,rspeed,pct);
    LB.spin(fwd,lspeed,pct);
    RB.spin(fwd,rspeed,pct);
    wait(wt,msec);
}

void drivestop(brakeType mode = brake){
    LF.stop(mode);
    RF.stop(mode);
    LB.stop(mode);
    RB.stop(mode);
}

void inchdrive(float target){
    LF.setPosition(0, rev);
    RF.setPosition(0, rev);
    float X = ((LF.position(rev)+RF.position(rev))/2) * M_PI*4 * 3.0/2;
    float error = target - X;
    float kp = 5;
    while(fabs(error)>0.5){
        error = target - X;
        float speed = kp*error;
        drive(speed,speed,10);
        X = ((LF.position(rev)+RF.position(rev))/2) * M_PI * 4 * 3.0/2;
    }
    Brain.Screen.printAt(0,120,"dist = %.2f     ",X);
    drivestop();
}

int sign(float a){return (a<0?-1:1);}

void turnTo(float angle){
    float error = angle - gyro1.rotation();
    float kp = 0.75;
    float maxSpeed = 25;
    while(fabs(error) >3){
        float speed = error*kp;
        if(fabs(speed)>maxSpeed){
            speed = maxSpeed*sign(speed);
        }
        
        drive(speed,-speed,10);
        error = angle - gyro1.rotation();
        while(fabs(error)>180){
            error-=360 * sign(error);
        }
    }
    Brain.Screen.printAt(10,100,"angle  = %2f  ",gyro1.rotation());
    drivestop();
}    

void autonomous(){
    inchdrive(24);
    inchdrive(-24);
}

void drivercontrol(){
    int X = 1;
    int Y = 1;
    int t = 0;

    while(1) {
      
      int f = ((LF.temperature()+ RF.temperature()+ LB.temperature()+ RB.temperature())/4.0);
      Brain.Screen.printAt(10,30,"avg motor temp = %d", f);
      Brain.Screen.drawCircle(X, Y, t/100, t%360);
      Brain.Screen.setPenColor(t%360);
      Controller.Screen.setCursor(1,1);
      /*
      yaw
      rotation
      heading
      */
      Controller.Screen.print("angle = %.2f      ", gyro1.rotation());
     t++;
     X+=Controller.ButtonRight.pressing()*2;
     Y+=Controller.ButtonDown.pressing()*2;
     X-=Controller.ButtonLeft.pressing()*2;
     Y-=Controller.ButtonUp.pressing()*2;
     X=fmax(0,X);   
     X=fmin(480,X);
     Y=fmax(0,Y);
     Y=fmin(272,Y);
     int lstick = Controller.Axis3.position();
     int rstick = Controller.Axis2.position();
     
     drive(lstick,rstick,10);
     
     
     this_thread::sleep_for(10);
    }
   
}

int main() {
    gyro1.calibrate();
    waitUntil(!gyro1.isCalibrating());
    Competition.autonomous(autonomous);
    Competition.drivercontrol(drivercontrol);
    while (true)
    {
        wait(100, msec);
    }
}  



