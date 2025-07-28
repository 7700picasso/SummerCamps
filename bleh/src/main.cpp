/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/28/2025, 1:27:49 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
controller Controller;
motor LF = motor(PORT2, ratio18_1, true);
motor RF = motor(PORT1, ratio18_1, false);
motor LB = motor(PORT4, ratio18_1, true);
motor RB = motor(PORT3, ratio18_1, false);
// define your global instances of motors and other devices here


int main() {

    int X = 9;
    Brain.Screen.printAt( 10, 50, "Hebhjhghllosvfsvsvs V5");
    Brain.Screen.drawCircle(100, 100, 50);
    Brain.Screen.drawRectangle(100, 100, 100, 100);

    int x = 100;
    int y = 100;
    while(1) {
            
            if (Controller.ButtonLeft.pressing()){
                x--;
            }else if  (Controller.ButtonRight.pressing()){
                x++;
            }else if (Controller.ButtonDown.pressing()){
                y++;
            }else if (Controller.ButtonUp.pressing()){
                y--;
            }
        
            // x+=Controller.Axis1.position()/20;
            // y-=Controller.Axis2.position()/20;
            Brain.Screen.drawCircle(x,y,10);
            Brain.Screen.drawCircle(y,x,10);
            Brain.Screen.printAt(10, 70 ,"pos = (%d, %d)",x,y);
            x= fmax(0,x);
            x= fmin(480,x);
            if(x <= 240 && y > 136){
                Brain.Screen.setFillColor(yellow);
            }else if(x <= 240 && y < 137){
                Brain.Screen.setFillColor(red);
            }else if(x > 240 && y <= 136){
                Brain.Screen.setFillColor(green);
            }else{
                Brain.Screen.setFillColor(blue);
            }
            

            Brain.Screen.drawCircle(x, y, 10);
            this_thread::sleep_for(10);
        }

        
        // Allow other tasks to run
       
    }

