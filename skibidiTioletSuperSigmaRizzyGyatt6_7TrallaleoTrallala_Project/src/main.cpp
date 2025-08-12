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
motor LF= motor(PORT11,ratio18_1,true);
motor RF= motor(PORT16,ratio18_1,false);
// define your global instances of motors and other devices here
void drive (int left, int right, int wt){
LF.spin(fwd,left,pct);
RF.spin(fwd,right,pct);
wait(wt,msec);
}
void driveStop(){
    LF.stop(brake);
    RF.stop(brake);
}




int clamp(int x, int lower, int upper)
{
    return fmin(fmax(x, lower), upper);
}

void auton(){

drive(50,50,2850);
driveStop();

drive(0,50,780);
driveStop();

drive(50,50,2500);
driveStop();

drive(0,50,720);
driveStop();

drive(50,50,2800);
driveStop();

drive(0,50,720);
driveStop();

drive(50,50,2400);
driveStop();


}



void drivercontrol()
{

    Brain.Screen.printAt(10, 50, "Dom is super sigma");
    int x = 100;
    int y = 100;
    while (1)
       { 
        if(controller1.ButtonB.pressing()){
            Brain.Screen.clearScreen();
        }
           if(controller1.ButtonA.pressing()){
            Brain.Screen.print("Dommy is the best teacher  ");
        }
        x+=controller1.Axis4.position()/20;
        y-=controller1.Axis3.position()/20;
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

        // Allow other tasks to run
        this_thread::sleep_for(5);
    }
}
int main(){
Compertition.drivercontrol(drivercontrol);
Compertition.autonomous(auton);
while(true){
    wait(100,msec);
}
}