# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Created:      4/17/2025, 2:56:43 PM                                        #
# 	Description:  V5 project w/ 2 motors                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

brain = Brain()
left_motor = Motor( Ports.PORT1 , GearSetting.RATIO_18_1 , False)
right_motor = Motor( Ports.PORT2 , GearSetting.RATIO_18_1 , True)

def drive( left_speed, right_speed, wt):
    left_motor.spin(FORWARD, left_speed, PERCENT)
    right_motor.spin(FORWARD, right_speed, PERCENT)
    wait(wt, MSEC)

def drive_brake():
    left_motor.stop(BRAKE)
    right_motor.stop(BRAKE)

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