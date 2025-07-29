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
competition Competititon;
// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
controller Controller1;
// define instances here
motor LF = motor(PORT1, ratio18_1, false);
motor RF = motor(PORT2, ratio18_1, true);
motor LB = motor(PORT5, ratio18_1, false);
motor RB = motor(PORT3, ratio18_1, true);



void drive(int lspeed, int rspeed, int wt) {
    LF.spin(fwd, lspeed, pct);
    RF.spin(fwd, rspeed, pct);
    LB.spin(fwd, lspeed, pct);
    RB.spin(fwd, rspeed, pct);
    wait(wt, msec);
}

void drivestop() {
    LF.stop(brake);
    RF.stop(brake);
    LB.stop(brake);
    RB.stop(brake);
}

void inch_drive(float target) {
    LF.setPosition(0, rev);
    RF.setPosition(0, rev);
    float x = ((LF.position(rev) + RF.position(rev) / 2) * M_PI * 4 * 3/2);
    while (x < target) {
        drive(50, 50, 10);
        x = ((LF.position(rev) + RF.position(rev) / 2) * M_PI * 4 * 3/2);
    }
}


void autonomous() {
    inch_drive(24 * 7);
    drivestop();
    drive(7.5, -7.5, 1000);
    drivestop();
    
}

void drivercontrol() {
     int x = 240;
    int y = 136;
    int size = 15;
    while(true) {
        Brain.Screen.print("BEEP BOOP DRIVE DRIVE");
        
        int lstick = Controller1.Axis3.position();
        int rstick = Controller1.Axis1.position();

        //tank drive
        //drive(lstick, rstick, 10);

        //arcade
        drive(lstick-rstick, lstick+rstick, 10);
        wait(10, msec); 
    }
}

int main() {
   Competititon.autonomous(autonomous);
   Competititon.drivercontrol(drivercontrol);

}

