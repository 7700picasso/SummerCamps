# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      8/5/2025, 9:11:52 AM                                         #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()
controller = Controller()
brain.screen.print("Hello V5")

x_value = 240
y_value = 135

while True:
    is_pressing = True
    if is_pressing:
        #brain.screen.clear_screen()
        if controller.buttonUp.pressing():
            y_value-=5
        if controller.buttonDown.pressing():
            y_value+=5
        if controller.buttonLeft.pressing():
            x_value-=5
        if controller.buttonRight.pressing():
            x_value+=5
       #brain.screen.print_at("Touch at:", x_value,y_value,x=x_value,y=y_value,sep = " ")

        if y_value<135 and x_value>240:
            brain.screen.set_fill_color(Color.YELLOW)
        elif y_value>135 and x_value<240:
            brain.screen.set_fill_color(Color.BLUE)
        elif y_value>135 and x_value>240:
            brain.screen.set_fill_color(Color.GREEN)
        else:
            brain.screen.set_fill_color(Color.RED)

        

        # brain.screen.set_fill_color(Color.GREEN)
        # brain.screen.set_fill_color(Color.BLUE)
        # brain.screen.set_fill_color(Color.RED)        # brain.screen.set_fill_color(Color.YELLOW)

        for circle in circles:
            x = circle[0]
            y = circle[1]
        brain.screen.draw_circle(x_value,y_value,5)
        wait(20,MSEC)

        
