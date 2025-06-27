# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student2                                                     #
# 	Created:      6/26/2025, 1:07:14 PM                                        #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *


brain = Brain()
controller = Controller()
LF = Motor(Ports.PORT13, GearSetting.RATIO_18_1, True)
LB = Motor(Ports.PORT14, GearSetting.RATIO_18_1, True)
RF = Motor(Ports.PORT20, GearSetting.RATIO_18_1, False)
RB = Motor(Ports.PORT18, GearSetting.RATIO_18_1, False)
pi = 3.14
dia = 4.0
gr = 1.5

def drive(left_speed, right_speed, wt):
    LF.spin(FORWARD,left_speed,PERCENT)
    LB.spin(FORWARD,left_speed,PERCENT)
    RF.spin(FORWARD,right_speed,PERCENT)
    RB.spin(FORWARD,right_speed,PERCENT)
    wait(wt, MSEC)

def brake():
    LF.stop(BRAKE)
    LB.stop(BRAKE)
    RF.stop(BRAKE)
    RB.stop(BRAKE)

def idrive(target):
  #  motor_position = LF.position(TURNS)
    x = 0
    LF.set_position(0, TURNS)
    x = LF.position(TURNS) * pi * dia * gr

    if target >= 0:
        while x <= target:
            brain.screen.clear_screen
            drive(50,50,10)
            x = LF.position(TURNS) * pi * dia * gr
            brain.screen.print_at("Forward: inches = ", x, x = 0, y = 40)
    elif target < 0:
        while x <= abs(target):
            brain.screen.clear_screen()
            drive(-50,-50,10)
            x = -LF.position(TURNS) * pi * dia * gr
            brain.screen.print_at("Backward: inches = ", x, x = 0, y = 40)

    else:
        brake()






def autonomous():
    brain.screen.clear_screen()
    brain.screen.print("autonomous code")
    # place automonous code here
    idrive(25)
    brake()
    drive(25,-25,600)
    brake()
    idrive(22)
    brake()
    drive(25,-25,500)
    brake()
    idrive(16)
    brake()
    drive(-25,25,650)
    brake()
    
def user_control():
    brain.screen.clear_screen()
    brain.screen.print("driver control")
    # place driver control in this while loop
    while True:
        leftspeed = controller.axis3.position()
        rightspeed = controller.axis2.position()
        drive(leftspeed , rightspeed, 5)
        wait(20, MSEC)

# create competition instance
comp = Competition(user_control, autonomous)

# actions to do when the program starts
brain.screen.clear_screen()