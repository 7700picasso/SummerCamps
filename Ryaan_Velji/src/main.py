# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      8/5/2025, 9:10:30 AM                                         #
# 	Description:  V5 project                                                   #.
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()
controller=Controller()


brain.screen.print("Hello world")

x_value = 240
y_value = 135

circles = [[240,135]]

LB = Motor(Ports.PORT12,GearSetting.RATIO_18_1,True)
RB = Motor(Ports.PORT13,GearSetting.RATIO_18_1,False)
LF = Motor(Ports.PORT11,GearSetting.RATIO_18_1,True)
RF = Motor(Ports.PORT14,GearSetting.RATIO_18_1,False)

def drive(left, right, wt):
    LB.spin(FORWARD,left,PERCENT)
    RB.spin(FORWARD,right,PERCENT)
    LF.spin(FORWARD,left,PERCENT)
    RF.spin(FORWARD,right,PERCENT)
    wait(wt)
gyro = Inertial(Ports.PORT17)

def turnTo(angle):
    error = angle - gyro.rotation()
    kp = 0.5
    timer = Timer()
    while abs(error)>2 and timer.time(MSEC) < 2000:
        error = angle - gyro.rotation()
        if error>180:
            error = 360 - error
        if error<-180:
            error = 360 + error
      #  brain.screen.print_at("error = ",error,x = 0,y = 40)
        drive(kp*error,-kp*error,20)
    brain.screen.print_at("done.                                    ",x = 0,y =40)
    driveStop()

def driveStop():
    LF.stop(BRAKE)
    LB.stop(BRAKE)
    RF.stop(BRAKE)
    RB.stop(BRAKE)

pi = 3.141592653589798233
wheel_diameter = 4
gear_ratio = 3/2

def inchDrive(inches):
    x = 0
    LF.set_position(0,TURNS)
    error = inches - x
    x = pi * wheel_diameter * gear_ratio * LF.position(TURNS)
    kp = 7
    while abs(error) > 0.25:
        x = pi * wheel_diameter * gear_ratio * LF.position(TURNS)
        error = inches - x
        speed = error*kp
        drive(speed,speed,10)
        
        #brain.screen.print_at("inches = ", x, x = 0, y = 40)
    driveStop()
    brain.screen.print_at("done",x=0,y=40)




def autonomous():
    gyro.calibrate()
    while gyro.is_calibrating():
        wait(20,MSEC)
    inchDrive(58)
    wait(1,SECONDS)
    turnTo(-90)
    driveStop()
    inchDrive(78)
    wait(1,SECONDS)
    turnTo(180)
    driveStop()
    inchDrive(53)
    inchDrive(-53)
    wait(1,SECONDS)
    turnTo(-90)
    driveStop()
    inchDrive(-78)
    wait(1,SECONDS)
    turnTo(180)
    driveStop()
    inchDrive(58)

def drivercontroll():
    while True:
        #brain.screen.clear_screen()
        if controller.buttonUp.pressing():
            y_value-=3
        if controller.buttonDown.pressing():
            y_value+=3
        if controller.buttonRight.pressing():
            x_value+=3
        if controller.buttonLeft.pressing():
            x_value-=3 
        
        # if(len(circles)>90):
        #     circles = circles[1:90]
        # circles.append([x_value, y_value])

        #brain.screen.print_at("Touch at: ",x_value,y_value,x = x_value,y = y_value,sep = " ")
        
        brain.screen.set_pen_color(Color.BLACK)

        brain.screen.clear_screen()
        #brain.screen.set_cursor(0,100)
        for circle in circles:
            x = circle[0]
            y = circle[1]
            if y < 135 and x < 240:
                brain.screen.set_fill_color(Color.RED)
            elif y <= 135 and x > 240:
                brain.screen.set_fill_color(Color.YELLOW)
            elif y >= 135 and x < 240:
                brain.screen.set_fill_color(Color.BLUE)
            else:
                brain.screen.set_fill_color(Color.GREEN)
            
            brain.screen.draw_circle(circle[0], circle[1], 10)
        
        left_stick = controller.axis3.position()
        right_stick = controller.axis2.position()
        drive(left_stick, right_stick, 10)

        wait(20,MSEC)

comp = Competition(drivercontroll,autonomous)

        

































































































































































































































































































