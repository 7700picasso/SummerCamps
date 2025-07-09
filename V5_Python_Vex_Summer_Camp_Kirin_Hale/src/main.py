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
left_front_moter = Motor(Ports.PORT6 , GearSetting.RATIO_18_1 , True)
left_back_moter = Motor(Ports.PORT9 , GearSetting.RATIO_18_1 , True)
right_front_moter = Motor(Ports.PORT16 , GearSetting.RATIO_18_1 , False)
right_back_moter = Motor(Ports.PORT3 , GearSetting.RATIO_18_1 , False)
gyro = Inertial(Ports.PORT20)
 
pi_num = 3.14
dia = 4.0
gr = 0.67




def drive( left_speed, right_speed, wt):
    left_front_moter.spin(FORWARD, left_speed, PERCENT)
    left_back_moter.spin(FORWARD, left_speed, PERCENT)
    right_front_moter.spin(FORWARD, right_speed, PERCENT)
    right_back_moter.spin(FORWARD, right_speed, PERCENT)

def driver_brake():
    left_front_moter.stop(BRAKE)
    left_front_moter.stop(BRAKE)
    right_front_moter.stop(BRAKE)
    right_back_moter.stop(BRAKE)

def inch_drive(target):
    x = 0
    left_front_moter.set_position(0, TURNS)
    x = left_front_moter.position(TURNS) * pi_num * dia * gr

    if target >= 0:
        while x <= target:
            brain.screen.clear_screen()
            drive(50,50,10)
            x = left_front_moter.position(TURNS) * pi_num * dia * gr
            brain.screen.print_at("Backward: inches = " , x, x = 0, y = 40)
    elif target < 0:
        while x <= abs(target):
            drive(-50, -50, 10)
            x = left_front_moter.position(TURNS) * pi_num * dia * gr
            brain.screen.print_at("Backward: inches = " , x, x = 0, y = 40)
    else:
        driver_brake()

    
def gyro_print():
    rotation = gyro.rotation(DEGREES)
    brain.screen.print_at("rotations:" ,rotation , x = 0 , y = 80)


def gyro_turn(target):
    rotation = 0.0
    gyro.reset_rotation()
    error = target - rotation
    accuracy = 2.0
    kp = 1.5
    speed = kp * error     
    while abs(error) >= accuracy:
        gyro_print()
        drive(speed,-speed,10)
        rotation = gyro.rotation(DEGREES)
        error = target - rotation
        speed = kp * error     
    driver_brake()


def autonomous():
    brain.screen.clear_screen()
    brain.screen.print("autonomous code")
    # place automonous code here
    gyro.calibrate()
    gyro_turn(-90)
    
   

def user_control():
    brain.screen.clear_screen()
    brain.screen.print("driver control")
    # place driver control in this, while loop
    gyro.calibrate()
    while True:
        gyro_print()
        wait(20, MSEC)

# create competition instance
comp = Competition(user_control, autonomous)

# actions to do when the program starts
brain.screen.clear_screen()