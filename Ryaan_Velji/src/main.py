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
    x = pi * wheel_diameter * gear_ratio * LF.position(TURNS)
    while x < inches:
        drive(50,50,10)
        x = pi * wheel_diameter * gear_ratio * LF.position(TURNS)
        brain.screen.print_at("inches = ", x, x = 0, y = 40)
    driveStop

inchDrive(24)

while True:
    is_pressing = True 
    if is_pressing:
        #brain.screen.clear_screen()
        

        if controller.buttonUp.pressing():
            y_value-=3
        if controller.buttonDown.pressing():
            y_value+=3
        if controller.buttonRight.pressing():
            x_value+=3
        if controller.buttonLeft.pressing():
            x_value-=3 
        
        
        if(len(circles)>90):
            circles = circles[1:90]
        circles.append([x_value, y_value])


        
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

        

































































































































































































































































































