# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      6/25/2025, 1:23:49 PM                                        #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

brain = Brain()

# Motor and Controller labels
lf = Motor( Ports.PORT2, GearSetting.RATIO_18_1, True)
lb = Motor( Ports.PORT1, GearSetting.RATIO_18_1, True)
rf = Motor( Ports.PORT4, GearSetting.RATIO_18_1, False)
rb = Motor( Ports.PORT3, GearSetting.RATIO_18_1, False)
cotroller = Controller()

# False = motor spins in opposite direction, while True = spin in normal direction

# Forward Drive code
def drive( left_speed, right_speed, wt):
    lf.spin(FORWARD, left_speed, PERCENT)
    lb.spin(FORWARD, left_speed, PERCENT)
    rf.spin(FORWARD, right_speed, PERCENT)
    rb.spin(FORWARD, right_speed, PERCENT)
    wait(wt, MSEC)


# Brakes
def driver_brake():
    lf.stop(BRAKE)
    lb.stop(BRAKE)
    rf.stop(BRAKE)
    rb.stop(BRAKE)




def autonomous():
    brain.screen.clear_screen()
    brain.screen.print("autonomous code")
    # place automonous code here
    drive(25, 25, 2000)
    driver_brake()
    drive(50, 40, 3000)
    driver_brake()

def user_control():
    brain.screen.clear_screen()
    brain.screen.print("driver control")
    # place driver control in this while loop
    while True:
       left_speed = controller.axis3.position()
       right_speed = controller.axis2.position()

       drive(left_speed, right_speed, 10)

       if controller.buttonX.pressing():
          driver_brake()


        wait(20, MSEC)

# create competition instance
comp = Competition(user_control, autonomous)

# actions to do when the program starts
brain.screen.clear_screen()