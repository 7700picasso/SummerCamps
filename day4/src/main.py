# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       Student                                                      #
# 	Created:      6/26/2025, 1:13:27 PM                                        #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

brain = Brain()
LF = Motor(Ports.PORT2, GearSetting.RATIO_18_1,True)
LB = Motor(Ports.PORT1, GearSetting.RATIO_18_1, True)
RF = Motor(Ports.PORT9, GearSetting.RATIO_18_1, False)
RB = Motor(Ports.PORT7, GearSetting.RATIO_18_1, False)
gyro = Inertial(Ports.PORT13)

pi_num =3.14
dia = 3.25
gr = 1.5

def drive(left_speed, right_speed,wt):
    LF.spin(FORWARD, left_speed, PERCENT)
    LB.spin(FORWARD, left_speed, PERCENT)
    RF.spin(FORWARD, right_speed, PERCENT)
    RB.spin(FORWARD, right_speed, PERCENT)

def robot_brake():
    LF.stop(BRAKE)
    LB.stop(BRAKE)
    RF.stop(BRAKE)
    RB.stop(BRAKE)

def inch_drive(target):
    x = 0 #inital distance
    LF.set_position(0,TURNS)
    drive
    if target >= 0:
        #forward
        while x<= target:
            brain.screen.clear_screen()
            drive(50,50,10)
            x = LF.position(TURNS) * pi_num * dia * gr
            # brain.screen.print_at("Forward: inches = ", x , x=0 y=40)
    elif target < 0:
       # backwards
        while x <= abs(target):
            drive(-50, -50, 10)
            x = -LF.position(TURNS) * PI_num * dia* gr
            # brain.screen.print_at("Backwards: inches =",x, x=0 y=40)
    else:
       #stop 
       robot_brake()

def gryo_print():
    rotation = gyro.rotation(DEGREES)
    brain.screen.print_at("rotations:", rotation , x=0 , y=80)

def gyro_turn(target):
    rotation = 0.0
    gyro.reset_rotation()
    error = target - rotation
    accuracy = 25.0
    kp = 3.0
    speed = kp * error

    while abs(error) >= accuracy:
        gryo_print()
        drive(speed, -speed , 10)
        rotation = gyro.rotation(DEGREES)
        error = target - rotation
        speed = kp * error
           
    robot_brake()

def user_control():
    brain.screen.clear_screen()
    brain.screen.print("auto control")
    # place driver control in this while loop
    gyro.calibrate()
    while True:
        gryo_print()
        wait(20, MSEC)
    
def autonomous():
    brain.screen.print("autonomous code")
    # place automonous code here
    gyro.calibrate()
    gyro_turn(-90)
    robot_brake()
   
# create competition instance
comp = Competition(user_control, autonomous)

# actions to do when the program starts
brain.screen.clear_screen()