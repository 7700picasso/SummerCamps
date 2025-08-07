

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()
controller = Controller()
brain.screen.print("Hai")

LB = Motor(Ports.PORT5,GearSetting.RATIO_18_1,True)
RB = Motor(Ports.PORT10,GearSetting.RATIO_18_1,False)
LF = Motor(Ports.PORT1,GearSetting.RATIO_18_1,True)
RF = Motor(Ports.PORT7,GearSetting.RATIO_18_1,False)
        
def drive(left,right,wt):
    LB.spin(FORWARD,left,PERCENT)
    RB.spin(FORWARD,right,PERCENT)
    LF.spin(FORWARD,left,PERCENT)
    RF.spin(FORWARD,right,PERCENT)
    wait(wt,MSEC)

def driveStop():
    LF.stop(BRAKE)
    RF.stop(BRAKE)
    LB.stop(BRAKE)
    RB.stop(BRAKE)


 def inchDrive(inches):
    x = 0
    LF.set_position(0,TURNS)

pi = 3.14
wheel_diameter = 3.25
gear_ratio = 3/4
def inchDrive(inches):
    x = 0
    LF.set_position(0,TURNS)
    x = pi * wheel_diameter * gear_ratio * LF.position(TURNS)
    while x<inches:
        drive(50,50,50)
    x = pi * wheel_diameter * gear_ratio * LF.position(TURNS)
    brain.screen.print_at("inches =",x,x=0,y=40)
driveStop()


inchDrive(24)
x_value = 240
y_value = 135


x_value = 240
y_value = 135
while True:
  

    brain.screen.clear_screen()
    x_value = brain.screen.x_position()
    y_value = brain.screen.y_position()

    #brain.screen.print_at("Touch at",x_value,y_value,x=x_value)

    brain.screen.set_fill_color(Color.GREEN)
    brain.screen.set_pen_color(Color.BLUE)

    brain.screen.draw_circle(x_value,y_value,20)
    
    left_stick = controller.axis3.position() # type: ignore
    right_stick = controller.axis2.position() # type: ignore
    drive(left_stick,right_stick, 10)
    wait(20,MSEC)
    wait(20,MSEC)
    