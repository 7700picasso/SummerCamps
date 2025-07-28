/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/28/2025, 1:26:47 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
controller Controller1;
motor LF = motor(PORT11,ratio18_1,true);
motor RF = motor(PORT13,ratio18_1,false);
motor LB = motor(PORT12,ratio18_1,true);
motor RB = motor(PORT14,ratio18_1,false);
// define your global instances of motors and other devices here


int main() {

    /*bool smt= false;
    int X;
    X=0;
    while(true){
        if(Brain.Screen.pressing()){
            smt = !smt; 
            wait(200,msec) ; 
        }
        if(smt){
                X++;
                Brain.Screen.printAt(10, 30, "%d          ", X);
                wait(1,msec);
        }else{
                X--;
                Brain.Screen.printAt(10, 30, "%d          ", X);
                wait(1,msec);
        }
    }*/


    /*while(1){
        int x= Brain.Screen.xPosition();
        int y= Brain.Screen.yPosition();
        Brain.Screen.drawCircle(x, y, 15);
        if(x<241 && y<137){
            Brain.Screen.setFillColor(red);
        }else if(x<241 && y>136){
            Brain.Screen.setFillColor(orange);
        }else if(x>240 && y>136){
            Brain.Screen.setFillColor(blue);
        }else{
            Brain.Screen.setFillColor(green);
        }
        
    }*/

    int x = 100;
    int y = 100;
    int t = 0;
    int R = 1;
    while(1){
        t++;
        R+=Controller1.Axis3.position()/100;
        x+=Controller1.Axis1.position()/20;
        y-=Controller1.Axis2.position()/20;
        Brain.Screen.drawCircle(x,y,R,t%360);
        Brain.Screen.setPenColor(t%360);
        x=fmax(0,x);
        x=fmin(480,x);
        y=fmax(0,y);
        y=fmin(250,y);
        wait(10,msec);
    }
};


