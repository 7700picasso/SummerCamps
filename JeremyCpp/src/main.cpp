/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/28/2025, 1:28:41 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
controller Controller1;
// define instances here
motor LF = motor(PORT1, ratio18_1, false);
motor RF = motor(PORT2, ratio18_1, true);
motor LB = motor(PORT5, ratio18_1, false);
motor RB = motor(PORT3, ratio18_1, true);

int main() {
    //double b = 0;
    //int X = 9;
    // Brain.Screen.printAt(10, 50, "Hello V5 %D", X);
    // Brain.Screen.drawCircle(100, 100, 50);
    int x = 240;
    int y = 136;
    int size = 15;
    while(true) {
        x += Controller1.Axis1.position()/20;
        y -= Controller1.Axis2.position()/20;
        Brain.Screen.setFillColor(green);
        Brain.Screen.setPenColor(black);
        Brain.Screen.drawCircle(x,y, size);
        x = fmax(0,x);
        x = fmin(480,x);
        y = fmax(0,y);
        y = fmin(272,y);
        if (Controller1.ButtonX.pressing()) {
            Brain.Screen.clearScreen();
        }
        if (Controller1.ButtonUp.pressing()) {
            size += 1;
        }
        if (Controller1.ButtonDown.pressing()) {
            size -= 1;
        }
        // }
        // Brain.Screen.setFillColor(yellow);
        // Brain.Screen.setPenColor(yellow);
        // Brain.Screen.drawCircle(240, (sin(b * 0.1) * 50) + 100, 50);
        // b += 1;
        // Allow other tasks to run
        wait(10, msec); 
    }
}
