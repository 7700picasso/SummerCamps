/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      8/11/2025, 1:33:46 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;
competition Competition;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;
controller controller1;
motor LF = motor(PORT2,ratio18_1,false);
motor RF = motor(PORT3,ratio18_1,true);
// define your global instances of motors and other devices here
void drive(int left, int right, int wt){
    LF.spin(fwd,left,pct);
    RF.spin(fwd,right,pct);
    wait(wt,msec);

}
void drivestop(){
    LF.stop(brake);
    RF.stop(brake);}
int clamp(int x,int lower, int upper){
    return fmin(fmax(x, lower),upper);



}
void auton(){
    drive(50,50,5650);
    drivestop();
    drive(-50,50,450);
    drivestop();
    drive(50,50,3600);
    drivestop();
    drive(-50,50,550);
    drivestop();
    drive(50,50,3700);
    drivestop();
    drive(-50,50,470);
    drivestop();
    drive(50,50,3600);
    drivestop();
    
    
   

}
void drivercontrol(){


  //  Brain.Screen.printAt(10, 50, "Hello V5");
    Brain.Screen.drawCircle(200, 200, 50);
    int x = 100;
    int y = 100;
    //for no outline
    Brain.Screen.setPenColor(transparent);
    Brain.Screen.print("sigma");
    while (1)
    {

        if(controller1.ButtonB.pressing()){
            Brain.Screen.clearScreen();
        }
        x+=controller1.Axis1.position()/20;
        y-=controller1.Axis2.position()/20;
        if(controller1.ButtonUp.pressing()){
            y-=1;

        }
        if(controller1.ButtonDown.pressing()){
            y+=1;
        }
        if(controller1.ButtonLeft.pressing()){
            x-=1;
        }
        if(controller1.ButtonRight.pressing()){
            x+=1;
        }
        x=clamp(x,0,480);
        y=clamp(y,0,240);

        
        if(x > 240 and y < 135)
        {
            Brain.Screen.setFillColor(green);
            Brain.Screen.setPenColor(green);
        }
        else if (x < 240 and y < 135){
            Brain.Screen.setFillColor(red);
            Brain.Screen.setPenColor(red);
        }
        else if (x < 240 and y > 135){
            Brain.Screen.setFillColor(yellow);
            Brain.Screen.setPenColor(yellow);
        }
        else{
            Brain.Screen.setFillColor(blue);
            Brain.Screen.setPenColor(blue);
        }
        // Brain.Screen.setFillColor(yellow);
       // Brain.Screen.printAt(x, y, "pressed at %d, %d", x, y);
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