/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student                                                   */
/*    Created:      7/28/2025, 1:29:33 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
controller Controller1;
motor LF = motor(PORT1, ratio18_1,false);
motor RF = motor(PORT11, ratio18_1,true);

motor RB = motor(PORT2, ratio18_1,true);
// controller Controller2;
// define your global instances of motors and other devices here


int main() {
    // int x=10;
    int X=9;
    Brain.Screen.printAt( 10, 50, "Hello V5 %d",X );
    Brain.Screen.drawCircle(100,100,50);
 
   
//     for(int i=0; i<480; i+=(i*10)){
//         for(int j=0; j< 240; j+=(j*10)){
//             Brain.Screen.printAt(i,j,"o");
//             if(i%3==0 || j%3==0){
// Brain.Screen.printAt(i,j,"W");
//             }
//         }
//     }

int x=100;
int y=100;
int i=100;
int j=100;
int q=100;
int w=100;
int  g=100;
int h=100;
    while(1) {
q+=Controller1.Axis1.position()/20;
w-=Controller1.Axis2.position()/20;
        Brain.Screen.drawCircle(q,w,30);
        g+=Controller1.Axis4.position()/20;
h-=Controller1.Axis3.position()/20;
        Brain.Screen.drawCircle(g,h,30);
       if(Controller1.ButtonLeft.pressing()){
        x--;
       }
       if(Controller1.ButtonRight.pressing()){
        x++;
       }
       if(Controller1.ButtonUp.pressing()){
        y--;
       }
       if(Controller1.ButtonDown.pressing()){
        y++;
       }
       if(Controller1.ButtonY.pressing()){
        i--;
       }
       if(Controller1.ButtonA.pressing()){
        i++;
       }
       if(Controller1.ButtonX.pressing()){
        j--;
       }
       if(Controller1.ButtonB.pressing()){
        j++;
       }
      
               Brain.Screen.printAt(10,70,"pos=(%d,%d)",x,y);
        // x=Brain.Screen.xPosition();
        // y=Brain.Screen.yPosition();

        

// Brain.Screen.printAt(420,70,"delete");
        if(x>240 && y<120){
            Brain.Screen.setFillColor(green);
        }else if(x>240 && y>120){
            Brain.Screen.setFillColor(blue);
        }else if(x<240 && y<120){
            Brain.Screen.setFillColor(red);
        }else if(x<240 && y>120){
            Brain.Screen.setFillColor(yellow);
        }
        if(i>240 && j<120){
            Brain.Screen.setFillColor(green);
        }else if(i>240 && j>120){
            Brain.Screen.setFillColor(blue);
        }else if(i<240 && j<120){
            Brain.Screen.setFillColor(red);
        }else if(i<240 && j>120){
            Brain.Screen.setFillColor(yellow);
        }
// for(int i=0; i< 480;i++){
//             for(int j=0; j<120; j++){
//                 Brain.Screen.drawCircle(j,i,10);
//             }
//         }
        Brain.Screen.drawCircle(x,y,5);
        Brain.Screen.drawCircle(x+10,y+10,5);
//         if(x>400&&y<100){
//             Brain.Screen.clearScreen();
//         }
        
        
    
        // Allow other tasks to run
        // this_thread::sleep_for(10);
        
       
      
               Brain.Screen.printAt(10,70,"pos=(%d,%d)",i,j);
        // x=Brain.Screen.xPosition();
        // y=Brain.Screen.yPosition();

        

// Brain.Screen.printAt(420,70,"delete");
        
// for(int i=0; i< 480;i++){
//             for(int j=0; j<120; j++){
//                 Brain.Screen.drawCircle(j,i,10);
//             }
//         }
        Brain.Screen.drawCircle(i,j,5);
        Brain.Screen.drawCircle(i+10,j+10,5);
        Brain.Screen.drawCircle(i+20,j+10,5);
        Brain.Screen.drawCircle(i-10,j+10,5);
        Brain.Screen.drawCircle(i+10,j-10,5);
        if(x>400&&y<100){
            Brain.Screen.clearScreen();
        }
        
        
    // x=fmax(0,x);
    // x=fmin(480,x);
    // y=fmax(y,120);
    // x=fmin(y,0);
        // Allow other tasks to run
        this_thread::sleep_for(10);
        
    
    }
    
    
       
}
