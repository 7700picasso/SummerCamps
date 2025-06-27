# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      6/26/2025, 1:06:58 PM                                        #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

brain = Brain()

#Mortor labels
lf = Motor(Ports.PORT14, GearSetting.RATIO_18_1, True)
lb = Motor(Ports.PORT12, GearSetting.RATIO_18_1, True)
rf = Motor(Ports.PORT8, GearSetting.RATIO_18_1, False)
rb = Motor(Ports.PORT16, GearSetting.RATIO_18_1, False)

pi_num = 3.14
dia = 4.0
gr = 1.5

def drive(left_speed, right_speed, wt):
    lf.spin(FORWARD, left_speed, PERCENT)
    lb.spin(FORWARD, left_speed, PERCENT)
    rf.spin(FORWARD, right_speed, PERCENT)
    rb.spin(FORWARD, right_speed, PERCENT)
    wait(wt, MSEC)

def brake():
    lf.stop(BRAKE)
    lb.stop(BRAKE)
    rf.stop(BRAKE)
    rb.stop(BRAKE) 

def inch_drive(target):
    # x = Encoder(turns)*pi*WheelDiameter*GearRatio
    x = 0 # initial starting postition
    lf.set_position(0, TURNS)
    x = lf.position(TURNS) * pi_num * dia * gr

    if target >= 0:
        #forward
        while x <= target:
            drive(25, 25, 10)
            x = lf.position(TURNS) * pi_num * dia * gr
            brain.screen.print_at("Foward: inches = ", x, x = 0, y = 40)
    elif target < 0:
        #backwards
       while x <= abs(target):
            brain.screen.clear_screen()
            drive(-50, -50, 10)
            x = -lf.position(TURNS) * pi_num * dia * gr
            brain.screen.print("Backwards: inches ", x, x = 0, y = 0)
    else:
        #stop
        brake()

def autonomous():
    brain.screen.clear_screen()
    brain.screen.print("autonomous code")
    # # place automonous code here
    inch_drive(24)
    brake()
    drive(25,-25, 600)
    brake()
    inch_drive(20)
    brake()
    drive(25, -25,450)
    brake()
    inch_drive(10)
    brake()
    drive(-25, 25, 450)
    brake()
    inch_drive(15)
    brake()
    drive(-25, 25, 350)
    brake()

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