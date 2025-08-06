# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      8/5/2025, 9:13:05 AM                                         #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()

brain.screen.print("Hello V5")

while True:
    is_pressing = brain.screen.is_pressing
    if is_pressing:
        brain.screen.clear_screen()
        x_value = brain.screen.x_position()
        y_value = brain.screen.y_position()

        brain.screen.print_at("Touch at",x_value,y_value,x=x_value)

        brain.screen.set_fill_color(Color.GREEN)
        brain.screen.set_pen_color(Color.BLUE)

        brain.screen.draw_circle(x_value,y_value,20)
        wait(20,MSEC)
    