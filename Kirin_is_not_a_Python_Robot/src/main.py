# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      6/23/2025, 2:39:17 PM                                        #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()

brain.screen.set_font(FontType.MONO30)
brain.screen.print("Hope you like this message :D ")
wait(3000, MSEC)
brain.screen.clear_screen(Color.RED)
brain.screen.print_at("Hello, my name is Kirin Hale " , x = 0 , y = 20)
wait(3000)     
brain.screen.clear_screen(Color.ORANGE)
brain.screen.new_line()
brain.screen.print_at("I am sigma" , x = 0 , y = 20)
wait(3000)     
brain.screen.clear_screen(Color.YELLOW)
brain.screen.new_line()
brain.screen.print_at("I like Minecraft,Grow a Garden, and blodx io " , x = 0 , y = 20)
wait(3000)     
brain.screen.clear_screen(Color.GREEN)
brain.screen.new_line()
brain.screen.print_at("Bye" , x = 0 , y = 20)
wait(3000)
brain.screen.clear_screen(Color.BLUE)
brain.screen.new_line()
brain.screen.print_at("I mean GOODBYE" , x = 0 , y = 20)
brain.screen.clear_screen
