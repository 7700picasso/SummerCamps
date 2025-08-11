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

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;
controller controller1;
    // define your global instances of motors and other devices here

int main()
{

    Brain.Screen.printAt(10, 50, "Reeeeheheheheheheheheheheheheheheheheheheheheheheheheheheheheheh Viraj is suppppperrerererer sigggmmma");
    int x = 100;
    int y = 100;
    while (1)
    {
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
        if (x > 240 and y < 135)
            Brain.Screen.setFillColor(green);
        else if (x < 240 and y < 135)
            Brain.Screen.setFillColor(red);
        else if (x < 240 and y > 135)
            Brain.Screen.setFillColor(yellow);
        else
            Brain.Screen.setFillColor(blue);

        //Brain.Screen.printAt(x, y, "pressed at %d, %d", x, y);

        Brain.Screen.drawCircle(x, y, 5);

        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}