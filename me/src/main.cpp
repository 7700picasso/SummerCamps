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

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;
controller controller1;
// define your global instances of motors and other devices here

int main()
{
    int x = 100;
    int y = 100;
    while (1)
    {
        if(controller1.ButtonUp.pressing() && y>0){
            y-=5;
        }
        if(controller1.ButtonDown.pressing() && y<240){
            y+=5;
        }
        if(controller1.ButtonRight.pressing() && x<480){
            x+=5;
        }
        if(controller1.ButtonLeft.pressing() && x>0){
            x-=5;
        }
        // Brain.Screen.printAt(x, y, "u suck, get a life", x, y);
        if (x < 240 && y < 135)
        {
            Brain.Screen.setFillColor(red);
        }
        else if (x < 240 && y > 134)
        {
            Brain.Screen.setFillColor(yellow);
        }
        else if (x > 239 && y < 135)
        {
            Brain.Screen.setFillColor(green);
        }
        else
        {
            Brain.Screen.setFillColor(blue);
        }
        // Brain.Screen.printAt(x,y,"pressed at %d, %d",x,y);
        Brain.Screen.drawCircle(x, y, 5);
        this_thread::sleep_for(10);
    }
    // Allow other tasks to run
    
}