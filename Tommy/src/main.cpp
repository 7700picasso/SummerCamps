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

competition Competition;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
controller Controller1;
motor LF = motor(PORT11,ratio18_1,true);
motor RF = motor(PORT13,ratio18_1,false);
motor LB = motor(PORT12,ratio18_1,true);
motor RB = motor(PORT14,ratio18_1,false);
motor intake = motor(PORT15,ratio18_1,false);
inertial gyro1 = inertial(PORT17);

void drive(int lspeed,int rspeed, int wt){
    LF.spin(fwd, lspeed, pct);
    LB.spin(fwd, lspeed, pct);
    RF.spin(fwd, rspeed, pct);
    RB.spin(fwd, rspeed, pct);
    wait(wt, msec);
}

void drivestop(brakeType mode = brake){
    LF.stop(mode);
    LB.stop(mode);
    RF.stop(mode);
    RB.stop(mode);
}

int sign(float a){return (a<0?-1:1);}

void stopintake(brakeType mode = brake){
    intake.stop(mode);
}

void intakefwd(int ispeed){
    intake.spin(fwd,ispeed,pct);
}

void intakerev(int ispeed){
    intake.spin(reverse,ispeed,pct);
}

void inchdrive(double target){
    LF.setPosition(0,rev);
    RF.setPosition(0,rev);
    double x = ((LF.position(rev)+RF.position(rev))/2) * M_PI * 4 * 3.0/2;
    double error = target - x;
    double kp = 3;
    double minSpeed = 10;
    double maxSpeed = 50;
    while(fabs(error)>0.2){
        x = ((LF.position(rev)+RF.position(rev))/2) * M_PI * 4 * 3.0/2;
        error = target - x;
        double speed = kp*error;
        if(fabs(speed)<minSpeed){
            speed = minSpeed*sign(speed);
        }
        if(fabs(speed)>maxSpeed){
            speed = maxSpeed*sign(speed);
        }
        drive(speed,speed,10);
    }
    Brain.Screen.printAt(0,120,"dist = %.2f      ",x);
    drivestop();
}

void turnTo(double angle){
    double error = angle - gyro1.rotation();
    double kp = 0.7;
    double maxSpeed = 35;
    while(fabs(error)>1){
        double speed = error*kp;
        if(fabs(speed)>maxSpeed){
            speed = maxSpeed*sign(speed);
        }
        drive(speed,-speed,10);
        error = angle - gyro1.rotation();
        while(fabs(error)>180){
            error-=360 * sign(error);
        }
    }
    Brain.Screen.printAt(10,100,"angle = %.2f   ", gyro1.rotation());
    drivestop();
}

void autonomous(){
    inchdrive(12);
    wait(500,msec);
    turnTo(-45);
    wait(500,msec);
    inchdrive(36*sqrt(2));
    wait(500,msec);
    turnTo(-135);
    wait(500,msec);
    inchdrive(36*sqrt(2));
    wait(500,msec);
    turnTo(-180);
    wait(500,msec);
    inchdrive(24);
    wait(500,msec);
    turnTo(-225);
    inchdrive(36*sqrt(2));
    turnTo(-315);
    inchdrive(36*sqrt(2));
    turnTo(0);
    inchdrive(12);
}

void drivercontrol(){
    while(true){
        /*double f = ((LF.temperature(temperatureUnits::celsius)+RF.temperature(temperatureUnits::celsius)+LB.temperature(temperatureUnits::celsius)+RB.temperature(temperatureUnits::celsius))/4.0);
        Brain.Screen.printAt(10,30,"avg drivebase motor temp = %.2f        ", f);*/
        double lbtemp = LB.temperature(temperatureUnits::celsius);
        double rbtemp = RB.temperature(temperatureUnits::celsius);
        double lftemp = LF.temperature(temperatureUnits::celsius);
        double rftemp = RF.temperature(temperatureUnits::celsius);
        Brain.Screen.printAt(10,30,"Left Front Motor Temp = %.2f   ",lftemp);
        Brain.Screen.printAt(10,50,"Right Front Motor Temp = %.2f   ",rftemp);
        Brain.Screen.printAt(10,70,"Left Back Motor Temp = %.2f   ",lbtemp);
        Brain.Screen.printAt(10,90,"Right Back Motor Temp = %.2f   ",rbtemp);
        //Controller1.Screen.print("angle = %.2f       ", gyro1.heading());
        if(Controller1.ButtonR1.pressing()){
            intakefwd(100);
        }else if(Controller1.ButtonR2.pressing()){
            intakerev(100);
        }else{
            stopintake();
        }
        int lstick = Controller1.Axis1.position();
        int rstick = Controller1.Axis3.position();
        drive(rstick+lstick, rstick-lstick, 10);
        wait(10, msec);
    }
}
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

    /*int x = 100;
    int y = 100;
    int t = 0;
    int r = 1;
    int c = 10;
    while(1){
        t++;
        if (Controller1.ButtonUp.pressing()){
            c++;
        }
        r+=Controller1.Axis3.position()/100;
        x+=Controller1.Axis1.position()/20;
        y-=Controller1.Axis2.position()/20;
        Brain.Screen.drawCircle(x,y,r,c%360);
        Brain.Screen.setPenColor(c%360);
        x=fmax(0,x);
        x=fmin(480,x);
        y=fmax(0,y);
        y=fmin(250,y);
        wait(10,msec);
    }*/
    
    gyro1.calibrate();
    waitUntil(!gyro1.isCalibrating());
    Competition.autonomous(autonomous);
    Competition.drivercontrol(drivercontrol);
    while (true){
        wait(100, msec);
    }
};


