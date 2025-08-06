# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      8/5/2025, 9:10:30 AM                                         #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()
controller=Controller()

brain.screen.print("Hello world")

x_value = 240
y_value = 135

circles = [[240,135]]

t = 0

while True:
    is_pressing = True 
    if is_pressing:
        #brain.screen.clear_screen()
        
        if t < 30:
            t+=0.3
        else:
            t=0
        if controller.buttonUp.pressing():
            y_value-=3
        if controller.buttonDown.pressing():
            y_value+=3
        if controller.buttonRight.pressing():
            x_value+=3
        if controller.buttonLeft.pressing():
            x_value-=3 
        
        
        if(len(circles)>90):
            circles = circles[1:90]
        circles.append([x_value, y_value])


        
        #brain.screen.print_at("Touch at: ",x_value,y_value,x = x_value,y = y_value,sep = " ")
        
        
        


        brain.screen.set_pen_color(Color.BLACK)
        brain.screen.draw_circle(x_value,y_value,t)
        brain.screen.clear_screen()
        #brain.screen.set_cursor(0,100)
        for circle in circles:
            x = circle[0]
            y = circle[1]
            if y < 135 and x < 240:
                brain.screen.set_fill_color(Color.RED)
            elif y <= 135 and x > 240:
                brain.screen.set_fill_color(Color.YELLOW)
            elif y >= 135 and x < 240:
                brain.screen.set_fill_color(Color.BLUE)
            else:
                brain.screen.set_fill_color(Color.GREEN)
            
            
            brain.screen.draw_circle(circle[0], circle[1], 10)
        
        wait(20,MSEC)

        





































































































































































































































































































































































