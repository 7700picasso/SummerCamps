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

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;
vex::controller controller1;
// define your global instances of motors and other devices here

int main()
{
    int x = 100;
    int y = 100;

   
    Brain.Screen.printAt(10, 50, "Hello V5");
    Brain.Screen.drawCircle(200, 200, 50);
    while (1)
    {
        if (controller1.ButtonUp.pressing() && y>0){
               y-=5;
        }
        if (controller1.ButtonDown.pressing() && y<240){
                 y+=5;
        }
        if (controller1.ButtonLeft.pressing() && x<480){
                 x-=5;
        }
        if (controller1.ButtonRight.pressing() && x>0){
                  x+=5;
        }
        if (x < 240 && y < 135)
        {
            Brain.Screen.setFillColor(red);
        }
        else if (x > 240 && y > 135)
        {
            Brain.Screen.setFillColor(blue);
        }
        else if (x < 240 && y > 135)
        {
            Brain.Screen.setFillColor(yellow);
        }
        else
        {
            Brain.Screen.setFillColor(green);
        }
        // Brain.Screen.printAt(x,y, "pressed at Brain.Screen.rawCircle xPosition ,yPosition
        Brain.Screen.drawCircle(x, y, 10);

        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
