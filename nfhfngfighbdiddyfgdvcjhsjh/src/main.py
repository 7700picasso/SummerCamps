

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()
controller = Controller()

LB = Motor(Ports.PORT5,GearSetting.RATIO_18_1,True)
RB = Motor(Ports.PORT10,GearSetting.RATIO_18_1,False)
LF = Motor(Ports.PORT2,GearSetting.RATIO_18_1,True)
RF = Motor(Ports.PORT7,GearSetting.RATIO_18_1,False)
        
def drive(left,right,wt):
    LB.spin(FORWARD,left,PERCENT)
    RB.spin(FORWARD,right,PERCENT)
    LF.spin(FORWARD,left,PERCENT)
    RF.spin(FORWARD,right,PERCENT)
    gyro = Inertial(Ports.PORT4)

def driveStop():
    LF.stop(BRAKE)
    RF.stop(BRAKE)
    LB.stop(BRAKE)
    RB.stop(BRAKE)


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

def turnTo(angle):
    error  = angle - gyro.rotation # type: ignore
    kp = 5
    while abs(error)>2:
        error = angle - gyro.rotation() # type: ignore
        if error>180:
            error = 360 - error
        if error<-180:
            error = 360 + error
        drive(kp*error,-kp*error,20)
    brain.screen.print_at("error = ",error,x=0,y=40)
    drive(kp*error,-kp*error,20)
    brain.screen.print_at("done.                       ",x=0,y=40)
    driveStop()

def autonomous():
   gyro.calibrate()
   while gyro.is_calibrating():
        wait(20,MSEC)
   inchDrive(24)
   drive(-50,50,500)

x_value = 240
y_value = 135


x_value = 240
y_value = 135
def drivercontrol():
    while True:
       #brain.screen.clear_sccreen()
       if controller.buttonUp.pressing():
        y_value-=5
       if controller.buttonDown.pressing():
        y_value+=5
       if controller.buttonLeft.pressing():
        x_value-=5
       if controller.buttonRight.pressing():
        x_value+=5
    #brain.screen.print_at("Touch at:", x_value,y_value,x=x_value,sep = " ")

        brain.screen.clear_screen()
        x_value = brain.screen.x_position()
        y_value = brain.screen.y_position()

        brain.screen.draw_circle(x_value,y_value,20)
        
        left_stick = controller.axis3.position() # type: ignore
        right_stick = controller.axis2.position() # type: ignore
        drive(left_stick,right_stick, 10)
        

        wait(20,MSEC)][=]
comp = Competition(drivercontrol, autonomous)