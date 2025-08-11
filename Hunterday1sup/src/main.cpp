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

vex::brain Brain;
controller controller1;

int main()
{
    int x = 100;
    int y = 100;
    while (1)
    {

        {
            /* code */
        }
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
        


        {
            /* code */
        }
        







        if (x > 240 && y < 135)
        {
            Brain.Screen.setFillColor(green);
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
            Brain.Screen.setFillColor(red);
        }
        /* code */

        Brain.Screen.drawCircle(x, y, 50);
    }
    this_thread::sleep_for(10);
}

// Allow other tasks to run
