# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      6/26/2025, 1:07:42 PM                                        #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Define Brain
brain = Brain()

# Define Motor
LF_motor = Motor(Ports.PORT1, GearSetting.RATIO_18_1, True)
RF_motor = Motor(Ports.PORT6, GearSetting.RATIO_18_1, False)
LB_motor = Motor(Ports.PORT11, GearSetting.RATIO_18_1, True)
RB_motor = Motor(Ports.PORT2, GearSetting.RATIO_18_1, False)

# PI
pi = 3.14
d = 4.0
gr = 0.67

# Speed
SPEED = 10

def drive(left_speed, right_speed, wt):
    LF_motor.spin(FORWARD, left_speed, PERCENT)
    RF_motor.spin(FORWARD, right_speed, PERCENT)
    LB_motor.spin(FORWARD, left_speed, PERCENT)
    RB_motor.spin(FORWARD, right_speed, PERCENT)
    wait(wt, MSEC)

def brake():
    LF_motor.stop(BRAKE)
    RF_motor.stop(BRAKE)
    LB_motor.stop(BRAKE)
    RB_motor.stop(BRAKE)

def inch_drive(target):
    # inch drive uses the distance instead of time GEOMETRY YO
    # x = Encoder(turns) *  Pi * WheelDiameter * GearRatio
    x = 0.0 # initial distance
    LF_motor.set_position(0, TURNS)
    x = LF_motor.position(TURNS) * pi * d * gr
    if target >= 0:
        # will move robot forward
        while x <= target:
             brain.screen.clear_screen()
             drive(SPEED, SPEED, 10)
             x = LF_motor.position(TURNS) * pi * d * gr
             brain.screen.print_at("forward inches: ", x, x = 0, y = 0)
    elif target <= 0:
        # will move robot backward
        while x <= abs(target):
            brain.screen.clear_screen()
            drive(-SPEED, -SPEED, 10)
            x = -LF_motor.position(TURNS) * pi * d * gr   
            brain.screen.print_at("backward inches: ", x, x = 0, y = 0)
    else:
        brake()
        

def autonomous():
    brain.screen.clear_screen()
    brain.screen.print("autonomous code")
    # place automonous code here
    # drive(15, -15, 1000)
    inch_drive(8)
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