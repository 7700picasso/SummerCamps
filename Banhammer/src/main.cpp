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

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
controller Controller;
// define your global instances of motors and other devices here

    

//int X = 1;
int main() {
    int X = 1;
    int Y = 1;
    int t = 0;
    
    while(1) {
      Brain.Screen.drawCircle(X, Y, t/100, t%360);
      Brain.Screen.setPenColor(t%360);
      
      
      
      
     t++;
     X+=Controller.Axis4.position()/20;
     Y-=Controller.Axis3.position()/20;   
     X=fmax(0,X);   
     X=fmin(480,X);
     Y=fmax(0,Y);
     Y=fmin(272,Y);

    
    
        this_thread::sleep_for(10);
    }
   while(1) {
      Brain.Screen.drawCircle(X, Y, t/100, t%360);
      Brain.Screen.setPenColor(t%360);
      
      
      
      
     t++;
     X+=Controller.Axis1.position()/20;
     Y-=Controller.Axis2.position()/20;   
     X=fmax(0,X);   
     X=fmin(480,X);
     Y=fmax(0,Y);
     Y=fmin(272,Y);

    
    
        this_thread::sleep_for(10);
    }
    









        // Allow other tasks to run
        this_thread::sleep_for(10);
    }




