# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      6/25/2025, 1:10:22 PM                                        #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

brain = Brain()
left_front_motor = Motor( Ports.PORT1 , GearSetting.RATIO_18_1 , False )
left_back_motor = Motor( Ports.PORT2 , GearSetting.RATIO_18_1 , False )
right_front_motor = Motor( Ports.PORT3 , GearSetting.RATIO_18_1 , True )
right_back_motor = Motor( Ports.PORT4 , GearSetting.RATIO_18_1 , True )

def drive( left_speed, right_speed, wt)
    left_front_motor.spin(FORWARD, left_speed, PERCENT)
    left_back_motor.spin(FORWARD, left_speed, PERCENT)
    right_front_motor.spin(FORWARD, right_speed, PERCENT)
    right_back_motor.spin(FORWARD, right_speed, PERCENT)

def driver_brake():
    left_front_motor.stop(BREAK)  
    left_back_motor.stop(BREAK)
    right_front_motor.stop(BREAK)
    right_back_motor.stop(BREAK)  



def autonomous():
    brain.screen.clear_screen()
    brain.screen.print("autonomous code")
    # place automonous code here
    drive(50, 50, 500)
    drive_brake()




def user_control():
    brain.screen.clear_screen()
    brain.screen.print("driver control")
    # place driver control in this while loop
    while True:
        wait(20, MSEC)

# create competition instance
comp = Competition(user_control, autonomous)

# actions to do when the program starts
brain.screen.clear_screen()