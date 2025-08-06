# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      8/5/2025, 9:11:52 AM                                         #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()
controller = Controller()
brain.screen.print("Hello V5")

x_value = 240   
y_value = 135

LB = Motor(Ports.PORT1,GearSetting.RATIO_18_1,False)
RB = Motor(Ports.PORT2,GearSetting.RATIO_18_1,True)
LF = Motor(Ports.PORT1,GearSetting.RATIO_18_1,True)
RF = Motor(Ports.PORT2,GearSetting.RATIO_18_1,False)

def drive(left,right,wt):
    LB.spin(FORWARD,left,PERCENT)
    RB.spin(FORWARD,right,PERCENT)
    LF.spin(FORWARD,left,PERCENT)
    RF.spin(FORWARD,right,PERCENT)
    wait(wt,MSEC)



def driveStop():
    LF.stop(BRAKE)
    RF.stop(BRAKE)
    LB.stop(BRAKE)
    RB.stop(BRAKE)


while True:
    is_pressing = True
    if is_pressing:
        #brain.screen.clear_screen()
        if controller.buttonUp.pressing():
            y_value-=5
        if controller.buttonDown.pressing():
            y_value+=5
        if controller.buttonLeft.pressing():
            x_value-=5
        if controller.buttonRight.pressing():
            x_value+=5
       #brain.screen.print_at("Touch at:", x_value,y_value,x=x_value,y=y_value,sep = " ")

        if y_value<135 and x_value>240:
            brain.screen.set_fill_color(Color.YELLOW)
        elif y_value>135 and x_value<240:
            brain.screen.set_fill_color(Color.BLUE)
        elif y_value>135 and x_value>240:
            brain.screen.set_fill_color(Color.GREEN)
        else:
            brain.screen.set_fill_color(Color.RED)

        left_stick = controller.axis3.position()
        right_stick = controller.axis2.position()
        drive(left_stick,right_stick,10)

        
        wait(20,MSEC)

        
