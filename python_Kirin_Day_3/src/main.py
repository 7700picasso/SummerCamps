# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       Student                                                      #
# 	Created:      6/26/2025, 1:14:44 PM                                        #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

brain = Brain()
LF = Motor(Ports.PORT6, GearSetting.RATIO_18_1, True)
LB = Motor(Ports.PORT9, GearSetting.RATIO_18_1, True)
RF = Motor(Ports.PORT16, GearSetting.RATIO_18_1, False)
RB = Motor(Ports.PORT3, GearSetting.RATIO_18_1, False)
pi_num = 3.14
dia = 4.0
gr = 1.5

def drive(left_speed, right_speed, wt):
    LF.spin(FORWARD, left_speed, PERCENT)
    LB.spin(FORWARD, left_speed, PERCENT)
    RF.spin(FORWARD, right_speed, PERCENT)
    LB.spin(FORWARD, right_speed, PERCENT)
    wait(wt,MSEC)

def robot_brakes():
    LF.stop(BRAKE)
    LB.stop(BRAKE)
    RF.stop(BRAKE)
    RB.stop(BRAKE)

def inch_drive(target):

    x = 0 #internal distence
    LF.set_position(0, TURNS)
    x = LF.position(TURNS) * pi_num * dia * gr

    if target >= 0:
        while x <= target:
            drive(10,10,10)
            x = LF.position(TURNS) * pi_num * dia * gr
    elif target < 0:
        while x <= abs(target):
            drive(-50,-50,10)
            x = -LF.position(TURNS) * pi_num * dia * gr
            # brain.screen.print_at("Forward: inches = ",x, x = 0 , y = 40)
    else:
        robot_brakes()


def autonomous():
    brain.screen.clear_screen()
    brain.screen.print("autonomous code")
    # place automonous code here

    inch_drive(30)
    drive(50,-50, 1000)
    inch_drive(25)
    drive(50,-50, 10003)

    robot_brakes()

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