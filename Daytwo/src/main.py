# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       Student                                                      #
# 	Created:      6/24/2025, 1:38:00 PM                                        #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()

brain.screen.print("Hello V5")


x = 12

y =  8

if x > y:
    brain.screen.print ("x is greater than y") 
    
# ELSE
# extension of IF statements
# ONLY checks 1 condition
a = 100
b = 200
sum = a +b
if sum > 10:
    brain.screen.print(" sum greater than 100")
else:
    brain.screen.print(" sum is something else  ")   
    
#ELIF
# applies more conditions 
# to check withinthe IF statement
#if previous condition is met 
#then it will skip all other elifs
weather = "sunny"

if weather == "cloudy":
    brain.screen.print("its cloudy outside")
elif weather =="rainy":
    brain.screen.print("its cloudyoutside")
# elif condition: sunny
else:
    brain.screen.print("Good weather")

# LOOPS
"""
while -runs repeadetly only while the codition is true

while condition:
    do this code
    """

# brain.screen.new_line()
# i = 9
# while:y =10
#     brain.screen.print(i)
#     i += 1 #i= i+1
#     brain.screen.new_line()
    
'''
FUNCTION
def function_name(arguments):
    code to do
'''

def subtract(a,b):
    sum = a +b

    return sum

    # def -defines the start of the function
    # function_name -unique name that represents the function
    #arguments -input values needed for function to work
    #return -used to throw out a value from the function

    # call  the function with its name
    c = add(67,57)
    brain.screen.print(c)
    brain.screen.clear_screen()
    brain.screeen.new_line


def presssingOnscreen():
    while True:
        brain.screen.clear_screen()
        is_pressing =brain.screen.pressing()

        if is_pressing:
            x_value = brain.screen.x_position()
            y_value = brain.screen.y_position()
            brain.screen.print_at("Touch at:", x_valaue, y_value,x= x_value, y =y_value, sep="" )
            wait (20,MSEC)

#pressingOnscreen

def screen_shape():
    x_value = brain.screen.x_position()
    y_value = brain.screen.y_position()

    brain.screen.set_pen_color(Color.BLUE)
    brain.screen.set_fill_color(Color.PURPLE)
    brain.screen.draw_circlescreen_shape()