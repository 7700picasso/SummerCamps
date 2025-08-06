# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      8/5/2025, 9:11:48 AM                                         #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()
controller = Controller()

#brain.screen.draw_circle(100,100,10)
brain.screen.print("Hello V5")
brain.screen.print("I AM JOE")
x_value = 240
y_value = 135
t = 0
circles =[[240,135]]
while True: 
    t+=0.05
     #brain.screen.clear_screen()
    if controller.buttonUp.pressing():
        y_value-=5
    if controller.buttonDown.pressing():
        y_value+=5
    if controller.buttonLeft.pressing():
        x_value-=5
    if controller.buttonRight.pressing():
        x_value+=5
     
     #brain.screen.print_at("Touch at: ",x_value,y_value,x=x_value,y=y_value,sep = " ")

    if(len(circles)>9):
        circles =circles[1:9]
    circles.append([x_value,y_value])


    brain.screen.clear_screen()
    for circle in circles:
        x = circle[0]
        y = circle[1]
        if x<241 and y<137:
            brain.screen.set_fill_color(Color.RED)
        elif x>240 and y<137:
            brain.screen.set_fill_color(Color.YELLOW)
        elif x<241 and y>136:
            brain.screen.set_fill_color(Color.BLUE)
        else:
            brain.screen.set_fill_color(Color.GREEN)
        brain.screen.draw_circle(circle[0],circle[1],10) 
    wait(20,MSEC)










