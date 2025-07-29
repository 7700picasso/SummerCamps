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
    while(X<target){
        drive(30,30,10);
        X = ((LF.position(rev)+RF.position(rev))/2) * M_PI * 4 * 3.0/2;
    }
    drivestop();
}

void autonomous(){
    inchdrive(53);
    drivestop();
    drive(-30, 30, 500);
    drivestop();
    inchdrive(53);
    drivestop();
    drive(-30, 30, 500);
    drivestop();
    inchdrive(53);
    drivestop();
    drive(-30, 30, 500);
    drivestop();
    inchdrive(53);
    drivestop();
    drive(-30, 30, 3000);
    drivestop();
}

void drivercontrol(){
    int X = 1;
    int Y = 1;
    int t = 0;

    while(1) {
      Brain.Screen.drawCircle(X, Y, t/100, t%360);
      Brain.Screen.setPenColor(t%360);
      
      
      
      
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
    Competition.autonomous(autonomous);
    Competition.drivercontrol(drivercontrol);
    while (true)
    {
        wait(100, msec);
    }
}  



