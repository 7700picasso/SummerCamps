# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      6/25/2025, 1:17:51 PM                                        #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

brain = Brain()
LF = Motor(Ports.PORT14, GearSetting.RATIO_18_1, True)
LB = Motor(Ports.PORT12, GearSetting.RATIO_18_1, True)
RF = Motor(Ports.PORT8, GearSetting.RATIO_18_1, False)
RB = Motor(Ports.PORT16, GearSetting.RATIO_18_1, False)
controller = Controller()

def drive( left_speed, right_speed, wt):
    LF.spin(FORWARD, left_speed, PERCENT)
    LB.spin(FORWARD, left_speed, PERCENT)
    RF.spin(FORWARD, right_speed, PERCENT)
    RB.spin(FORWARD, right_speed, PERCENT)
    wait(wt, MSEC)

def brake():
    LF.stop(BRAKE)
    LB.stop(BRAKE)
    RF.stop(BRAKE)
    RB.stop(BRAKE)

def autonomous():
    brain.screen.clear_screen(Color.RED)
    brain.screen.print("autonomous code in progress... =)")
    # place automonous code here
    
    drive(25, 25, 2000)
    brake()
    wait(100, MSEC)
    drive(22,-22,670)
    brake()
    drive(25,25,1300)
    brake()
    drive(17,-17,670)
    brake()
    drive(25,25,1000)
    brake()
    drive(-17,17,670)
    brake()
    drive(25,25,900)
    brake()
    drive(-10,10,670)
    brake()
    drive(25,25,1250)
    brake()
    drive(22,-22,670)
    brake()
    drive(25,25,1000)
    brake()
    drive(-11,11,670)
    brake()
    drive(25,25,1800)
    brake()
    drive(-15,15,670)
    brake()
    drive(25,25,1900)
    brake()
    drive(25,-25,1000)
    brake()
    drive(25,25,2100)
    brake()
"""
    brain.screen.clear_screen(Color.RED)
    drive(-50,50,10000)
    brake()
    brain.screen.clear_screen(Color.ORANGE)
    drive(-50,50,10000)
    brake()
    brain.screen.clear_screen(Color.YELLOW)
    drive(-50,50,10000)
    brake()
    brain.screen.clear_screen(Color.GREEN)
    drive(-50,50,10000)
    brake()
"""



def user_control():
    brain.screen.clear_screen(Color.GREEN)
    brain.screen.print("driver control in progress... =)")
    # place driver control in this while loop
    while True:
        left_speed = controller.axis3.position()
        right_speed = controller.axis3.position()
       
        
        drive(left_speed, right_speed, 10 )

        if controller.buttonA.pressing():
            drive(60,-60,100)
        
        if controller.buttonY.pressing():
            drive(-60,60,100)
            

# create competition instance
comp = Competition(user_control, autonomous)

# actions to do when the program starts
brain.screen.clear_screen(Color.BLUE)

