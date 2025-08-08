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
competition Competition;
// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
controller Controller1;
motor LF = motor(PORT1, ratio18_1,true);
motor RF = motor(PORT15, ratio18_1,false);
motor LB = motor (PORT14, ratio18_1,true);
motor RB = motor(PORT2, ratio18_1,false);
inertial gyro1 = inertial(PORT10);

void drive(int lspeed,int rspeed,int wt){
LF.spin(fwd,lspeed,pct);
LB.spin(fwd,lspeed,pct);
RF.spin(fwd,rspeed,pct);
RB.spin(fwd,rspeed,pct);
wait(wt,msec);
}

void drivestop(){
    LF.stop(brake);
    RF.stop(brake);
    LB.stop(brake);
    RB.stop(brake);
    }
    void inchdrive(float target){
        LF.setPosition(0,rev);
        RF.setPosition(0,rev);
        
        float x = ((LF.position(rev)+RF.position(rev))/2) * M_PI*4 * 3.0/2;
            float error = target-x;
            float kp = 5;
        while(fabs(error)>0.5){
            error = target-x;
            float speed = kp*error;
            drive(speed,speed,10);
             x = ((LF.position(rev)+RF.position(rev))/2) * M_PI*4 * 3.0/2;
        }
        Brain.Screen.printAt(0,120, "dist = %.2f    ",x);
        drivestop();
    }
    int sign(float a){return (a<0? - 1:1);}
    void turnTo(float angle){
        float error = angle- gyro1.rotation();
        float kp=0.58;
        float ki = 0.0015;
        float kd =0.87;
        float totalerror=0;
        float preverror=error;
        while(fabs(error)>3){
            
             error = angle- gyro1.rotation();
             while(fabs(error)>180){
error-=360*sign(error);
             }
             float speed = error*kp+totalerror*ki+(error-preverror)*kd;
             totalerror += error;
             preverror = error;
            drive(speed,-speed,10) ;         
        }
        Brain.Screen.printAt(10,100,"angle= %.2f", gyro1.rotation());
        drivestop();
    }
    void autonomous(){
           inchdrive(48);
            wait(100,msec);
            turnTo(45);
            wait(100,msec);
            inchdrive(13);   
            wait(100,msec);
            turnTo(315);
            wait(100,msec);
            turnTo(45);   
            wait(100,msec);
            inchdrive(13);  
            wait(100,msec); 
            turnTo(315);
            wait(100,msec);
            inchdrive(50);
             wait(100,msec);
            turnTo(225);
            wait(180,msec);
            turnTo(45);
            wait(100,msec);
            inchdrive(-40);
            wait(100,msec);
             turnTo(315);
            wait(100,msec);
            inchdrive(-50);

    }

    void drivercontrol(){
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
        
        
    // x<=480;
    // x>=0;
    // y<=0;
    // y>=-240;
    x=fmax(0,x);
    x=fmin(480,x);
    y=fmax(y,20);
    y=fmin(y,-240);
    int lstick = Controller1.Axis3.position();
    int rstick = Controller1.Axis2.position();
    drive(lstick,rstick,10);
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("Angle = %.2f",gyro1.yaw());
        // Allow other tasks to run
        this_thread::sleep_for(10);
        
    
    }
    }
// controller Controller2;
// define your global instances of motors and other devices here


int main() {
    gyro1.calibrate();
    waitUntil(! gyro1.isCalibrating());
    Competition.autonomous(autonomous);
    Competition.drivercontrol(drivercontrol);
    while(true){
        wait(100, msec);
    }
    
    }
    
    
       

