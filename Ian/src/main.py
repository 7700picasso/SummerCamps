# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      8/5/2025, 9:02:31 AM                                         #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()
controller = Controller()
LB = Motor(Ports.PORT2,GearSetting.RATIO_18_1,True)
LF = Motor(Ports.PORT3,GearSetting.RATIO_18_1,True)
RB = Motor(Ports.PORT1,GearSetting.RATIO_18_1,False)
RF = Motor(Ports.PORT6,GearSetting.RATIO_18_1,False)






x_value = 240
y_value = 135
circles = [[240,135]]



def drive(left , right,wt):
    LB.spin(FORWARD,left,PERCENT)
    RB.spin(FORWARD,right,PERCENT)
    LF.spin(FORWARD,left,PERCENT)
    RF.spin(FORWARD,left,PERCENT)
    wait(wt,MSEC)

def driveStop():
    LF.stop(BRAKE)
    LB.stop(BRAKE)
    RF.stop(BRAKE)
    RB.stop(BRAKE)

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



def autonomous():
    inchDrive(72)
    drive(-50,50,500)
    inchDrive(72)
    drive(-50,50,500)
    inchDrive(72)


 
def drivercontrol():



 while True:
        #brain.screen.clear_screen()
        if controller.buttonUp.pressing():
            y_value-=5
        if controller.buttonDown.pressing():
            y_value+=5 
        if controller.buttonLeft.pressing():
            x_value-=5
        if controller.buttonRight.pressing():
            x_value+=5

       ###circles.append([x_value,y_value])         

        #brain.screen.print_at("Touch at:",x_value,y_value,x=x_value,y=y_value,sep = "")
        
        # if x_value<240 and y_value<135:
        #     brain.screen.set_fill_color(Color.RED)
        # elif x_value>240 and y_value<135:
        #     brain.screen.set_fill_color(Color.YELLOW)
        # elif x_value<240 and y_value>135:
        #     brain.screen.set_fill_color(Color.BLUE)
        # elif x_value>240 and y_value>135:
        #     brain.screen.set_fill_color(Color.GREEN)    


        left_stick = controller.axis3.position()    
        right_stick = controller.axis2.position()
        drive(left_stick,right_stick,10)
        wait(20,MSEC)


        #brain.screen.set_fill_color(Color.GREEN)
       # brain.screen.set_pen_color(Color.BLUE)
        brain.screen.clear_screen()
        for circle in circles:
            x = circle[0]
            y = circle[1]
            if x<240 and y<135:
                brain.screen.set_fill_color(Color.RED)
            elif x>240 and y<135:
                brain.screen.set_fill_color(Color.YELLOW)
            elif x<240 and y>135:
                brain.screen.set_fill_color(Color.BLUE)
            elif x>240 and y>135:
                brain.screen.set_fill_color(Color.GREEN)
            brain.screen.draw_circle(circle[0],circle[1],10)
        wait(20,MSEC)    



comp = Competition(drivercontrol,autonomous)
        
        #brain.screen.draw_circle(x_value,y_value,20)





        
