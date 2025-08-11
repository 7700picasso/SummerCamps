# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       Student                                                      #
# 	Created:      8/5/2025, 9:12:03 AM                                         #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()
controller=Controller()

LB = Motor(Ports.PORT2,GearSetting.RATIO_18_1,True)
RB = Motor(Ports.PORT1,GearSetting.RATIO_18_1,False)
LF = Motor(Ports.PORT4,GearSetting.RATIO_18_1,True)
RF = Motor(Ports.PORT3,GearSetting.RATIO_18_1,False)
gyro = Inertial(Ports.PORT10)

def drive(left , right,wt):
    LB.spin(FORWARD,left,PERCENT)
    RB.spin(FORWARD,right,PERCENT)
    LF.spin(FORWARD,left,PERCENT)
    RF.spin(FORWARD,right,PERCENT)
    wait(wt,MSEC)

def driveStop():
    LF.stop(BRAKE)
    RF.stop(BRAKE)
    RB.stop(BRAKE)
    LB.stop(BRAKE)

pi = 3.14
wheel_diameter = 4
gear_ratio = 3/2
def inchDrive(inches):
    x = 0
    LF.set_position(0,TURNS)
    x = pi * wheel_diameter * gear_ratio * LF.position(TURNS)
    while x < inches:
        drive(50,50,10)
        x = pi * wheel_diameter * gear_ratio * LF.position(TURNS)
        brain.screen.print_at("inches = ",x,x=0,y=40)
    driveStop()





x_value = 240
y_value = 134
def turnTO(angle):
    error = angle - gyro.rotation()
    kp = 5
    timer = TImer()
    while abs(error)>2 or timer.time(MSEC)>2000:
        error = angle - gyro.rotation()
        if error>180:
            error= 360 - error
        if error<-180:
            error = 360 + error
        brain.screen.print_at("error =  ",error,x=0,y=40)
        drive(kp*error,-kp*error,20)
    brain.screen.print_at("done.                     ",x=0,y=40)
    driveStop()


def autonomous():
    gyro.calibrate()
    while gyro.is_calibrating():
        wait(20, MSEC)
    inchDrive(24)
    turnTo(-90)

def drivercontrol():
    while True:
        #brain.screen.clear_screen
        if controller.buttonUp.pressing():
            y_value-=5
        if controller.buttonDown.pressing():
            y_value+=5W 
        if controller.buttonRight.pressing():
            x_value+=5
        if controller.buttonLeft.pressing():
            x_value-=5

        # if(len(circles)>9)
        #     circles = circles[1:9]
        # circles.append[[x_value,y_value]]
        # brain.screen.draw_circle()

       

        #brain.screen.print_at("Touch at: ",x_value,y_value,x=x_value,y=y_value,sep=" ")
       
        # if y_value<135 and x_value<240:
        #     brain.screen.set_fill_color(Color.RED)
        # elif y_value<135 and x_value>240:
        #     brain.screen.set_fill_color(Color.YELLOW)
        # elif y_value>135 and x_value<240:
        #     brain.screen.set_fill_color(Color.BLUE)
        # else:
        #     brain.screen.set_fill_color(Color.GREEN)
        # brain.screen.set_fill_color(Color.GREEN)
        
        left_stick = controller.axis3.position()
        right_stick = controller.axis2.position()
        drive(left_stick,right_stick,10)
        
        wait(20,MSEC)


comp = Competition(drivercontrol,autonomous)                                                                                                                                                                                