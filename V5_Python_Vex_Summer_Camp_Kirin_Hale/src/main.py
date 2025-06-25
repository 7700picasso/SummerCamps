# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      6/25/2025, 1:23:25 PM                                        #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

brain = Brain()
left_front_moter = Motor(Ports.PORT1 , GearSetting.RATIO_18_1 , True)
left_back_moter = Motor(Ports.PORT11 , GearSetting.RATIO_18_1 , True)
right_front_moter = Motor(Ports.PORT6 , GearSetting.RATIO_18_1 , False)
right_back_moter = Motor(Ports.PORT2 , GearSetting.RATIO_18_1 , False)

def drive( left_speed, right_speed, wt):
    left_front_moter.spin(FORWARD, left_speed, PERCENT)
    left_back_moter.spin(FORWARD, left_speed, PERCENT)
    right_front_moter.spin(FORWARD, right_speed, PERCENT)
    right_back_moter.spin(FORWARD, right_speed, PERCENT)

def driver_brake():
    left_front_moter.stop(BRAKE)
    left_front_moter.stop(BRAKE)
    left_front_moter.stop(BRAKE)
    left_front_moter.stop(BRAKE)

    
    
    

def autonomous():
    brain.screen.clear_screen()
    brain.screen.print("autonomous code")
    # place automonous code here
    drive(-50, -50, 200)
    driver_brake()

def user_control():
    brain.screen.clear_screen()
    brain.screen.print("driver control")
    # place driver control in thismmmmmm           ,,, while loop
    while True:
        wait(20, MSEC)

# create competition instance
comp = Competition(user_control, autonomous)

# actions to do when the program starts
brain.screen.clear_screen()