/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      8/11/2025, 1:45:10 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;
competition Competition;
// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;
vex::controller controller1;

motor LF = motor(PORT14,ratio18_1,false);
motor RF = motor(PORT2,ratio18_1,true);
    
    

// define your global instances of motors and other devices here

void drive(int left,int right,int wt){
    LF.spin(fwd,left,pct);
    RF.spin(fwd,right,pct);
        wait(wt,msec);
}
void driveStop(){
    LF.stop(brake);
    RF.stop(brake);
}

int clamp(int x,int lower ,int upper){
    return fmin(fmax(x,lower), upper);
} 
void auton(){
    drive(500,500,2000);
    driveStop();
    drive(-50,95,700);
    driveStop();
    drive(500,500,1700);
    driveStop();
    drive(-45,90,700);
    driveStop();
    drive(500,500,2000);
    driveStop();
    drive(-45,93,1000);
    driveStop();
}

void drivercontrol(){
    int x = 100;
    int y = 100;
    Brain.Screen.setPenColor(transparent);

   
    
    while (1){
        if(controller1.ButtonB.pressing()){
            Brain.Screen.clearScreen();
        }
        x+=controller1.Axis4.position()/20;
        y-=controller1.Axis3.position()/20;
        if (controller1.ButtonUp.pressing() ){
         
            y-=3;
        }
        if (controller1.ButtonDown.pressing() ){
                 y+=3;
        }
        if (controller1.ButtonLeft.pressing() ){
                 x-=3;
        }
        if (controller1.ButtonRight.pressing() ){
                  x+=3;
        }
        x=clamp(x,0,480);
        y=clamp(y,0,240);
        
        
       
        if (x < 240 && y < 135)
        {
            Brain.Screen.setFillColor(red);
            Brain.Screen.setPenColor(red);
        }
        else if (x > 240 && y > 135)
        {
            Brain.Screen.setFillColor(blue);
            Brain.Screen.setPenColor(blue);
        }
        else if (x < 240 && y > 135)
        {
            Brain.Screen.setFillColor(yellow);
            Brain.Screen.setPenColor(yellow);
        }
        else
        {
            Brain.Screen.setFillColor(green);
            Brain.Screen.setPenColor(green);
        }
        // Brain.Screen.printAt(x,y, "pressed at Brain.Screen.rawCircle xPosition ,yPosition
        Brain.Screen.drawCircle(x, y, 10);

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

