# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      8/5/2025, 9:11:48 AM                                         #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()
controller = Controller()

LF = Motor(Ports.PORT2,GearSetting.RATIO_18_1,True)
RF = Motor(Ports.PORT9,GearSetting.RATIO_18_1,False)
LB = Motor(Ports.PORT3,GearSetting.RATIO_18_1,True)
RB = Motor(Ports.PORT11,GearSetting.RATIO_18_1,False)
SP1 = Motor(Ports.PORT10,GearSetting.RATIO_6_1,False)
gyro = Inertial(Ports.PORT20)

def drive(left, right,wt):
    LF.spin(FORWARD,left,PERCENT)
    LB.spin(FORWARD,left,PERCENT)
    RF.spin(FORWARD,right,PERCENT)
    RB.spin(FORWARD,right,PERCENT)
    wait(wt,MSEC)


def driveStop():
    LF.stop(BRAKE)
    RF.stop(BRAKE)
    LB.stop(BRAKE)
    RB.stop(BRAKE)

pi = 3.14
wheel_diameter = 4
gear_ratio = 3/2
def inchDrive(inches):
    x = 0
    LF.set_position(0,TURNS)
    x = pi * wheel_diameter * gear_ratio * LF.position(TURNS)
    while x < inches:
        drive(30,30,10)
        x = pi * wheel_diameter * gear_ratio * LF.position(TURNS)
        brain.screen.print_at("inches = ",x,x=0,y=40)
    driveStop()

def turnTo(angle):
    error = angle - gyro.rotation()
    kp = 5
    timer = Timer()
    while abs(error)>2 or timer.time(MSEC)>2000:
        error = angle - gyro.rotation()
        if error>180:
            error = 360 -error
        if error<-180:
            error = 360 + error
        brain.screen.print_at("error = ",error,x=0,y=40)
        drive(kp*error,-kp*error,20)
    brain.screen.print_at("done.              ",x=0,y=40)
    driveStop()






def autonomous():
    gyro.calibrate()
    while gyro.is_calibrating():
        wait(20, MSEC)
    inchDrive(24)
    turnTo(90)






















#brain.screen.draw_circle(100,100,10)
brain.screen.print("Hello V5")
brain.screen.print("I AM JOE")
x_value = 240
y_value = 135
t = 0
circles =[[240,135]]

def drivercontrol():
    while True:
        # t+=0.05
        #brain.screen.clear_screen()
        if controller.buttonUp.pressing():
            y_value-=5
        if controller.buttonDown.pressing():
            y_value+=5
        if controller.buttonLeft.pressing():
            x_value-=5
        if controller.buttonRight.pressing():
            x_value+=5
        
        brain.screen.clear_screen()
        for circle in circles:
            x = circle[0]
            y = circle[1]
            if x<241 and y<137:
                brain.screen.set_fill_color(Color.RED)
            elif x>240 and y<137:
                brain.screen.set_fill_color(Color.YELLOW)
            elif x<241 and y>136:
                brain.screen.set_fill_color(Color.BLUE)
            else:
                brain.screen.set_fill_color(Color.GREEN)
            brain.screen.draw_circle(circle[0],circle[1],10)
        
        left_stick = controller.axis3.position()
        right_stick = controller.axis2.position()
        drive(left_stick,right_stick,10)
        wait(20,MSEC)



comp = Competition(drivercontrol,autonomous) 






