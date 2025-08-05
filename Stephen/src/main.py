# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       Student                                                      #
# 	Created:      8/5/2025, 9:12:03 AM                                         #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()
controller=Controller()
brain.screen.print("Hello V5")
x_value = 240
y_value = 135


while True:
    is_pressing = True
    if is_pressing:
        #brain.screen.clear_screen
        if controller.buttonUp.pressing():
            y_value-=5
        if controller.buttonDown.pressing():
            y_value+=5
        if controller.buttonRight.pressing():
            x_value+=5
        if controller.buttonLeft.pressing():
            x_value-=5

        if(len(circles)>9)
            circles = circles[1:9]
        circles.append[[x_value,y_value]]
        brain.screen.draw_circle()

       

        #brain.screen.print_at("Touch at: ",x_value,y_value,x=x_value,y=y_value,sep=" ")
       
        # if y_value<135 and x_value<240:
        #     brain.screen.set_fill_color(Color.RED)
        # elif y_value<135 and x_value>240:
        #     brain.screen.set_fill_color(Color.YELLOW)
        # elif y_value>135 and x_value<240:
        #     brain.screen.set_fill_color(Color.BLUE)
        # else:
        #     brain.screen.set_fill_color(Color.GREEN)
        # brain.screen.set_fill_color(Color.GREEN)
        
        brain.screen.set_pen_color(Color.BLUE)
        brain.screen.clear_sscree
        brain.screen.draw_circle(x_value,y_value,20)
        
        
        wait(20,MSEC)
