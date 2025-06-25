# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      6/25/2025, 1:23:16 PM                                        #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Define Brain & Controller
brain = Brain()
controller = Controller()

# Define Motors
left_front_motor = Motor(Ports.PORT13, GearSetting.RATIO_18_1, True)
right_front_motor = Motor(Ports.PORT20, GearSetting.RATIO_18_1, False)
left_back_motor = Motor(Ports.PORT14, GearSetting.RATIO_18_1, True)
right_back_motor = Motor(Ports.PORT18, GearSetting.RATIO_18_1, False)

def drive(left_speed, right_speed, wt):
    left_front_motor.spin(FORWARD, left_speed, PERCENT)
    right_front_motor.spin(FORWARD, right_speed, PERCENT)
    left_back_motor.spin(FORWARD, left_speed, PERCENT)
    right_back_motor.spin(FORWARD, right_speed, PERCENT)
    wait(wt, MSEC)

def drive_brake():
    left_front_motor.stop(BRAKE)
    right_front_motor.stop(BRAKE) 
    left_back_motor.stop(BRAKE)
    right_back_motor.stop(BRAKE) 

def autonomous():
    brain.screen.clear_screen()
    brain.screen.print("autonomous code")
    # place automonous code here
    drive(50, 50, 1000)
    drive_brake()

def user_control():
    brain.screen.clear_screen()
    brain.screen.print("driver control")
    # place driver control in this while loop
    while True:
        left_speed = controller.axis3.position()
        right_speed = controller.axis2.position()
        
        drive(left_speed, right_speed, 10)

        if controller.buttonX.pressing():
            drive_brake()


# create competition instance
comp = Competition(user_control, autonomous)

# actions to do when the program starts
brain.screen.clear_screen()