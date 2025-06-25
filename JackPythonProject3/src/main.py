# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      6/24/2025, 1:06:54 PM                                        #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()

# Conditional Statements
# they help our code make descisions based on conditions
new_line = brain.screen.new_line
clear = brain.screen.clear_screen
"""
Logical Conditions
x < y : less Than
x > y : Greater Than
x <= y : Less Than or Equal to
x >= y : Greater Than or Equal to
x == y : Equal To
x != y : NOT Equal
"""

# IF Statement
"""
SYNTAX

if condition:
    do this code
"""

"""
x = 12
y = 8

if x > y:
    brain.screen.print("x is greater than y")
"""

# ELSE
# extension of an IF statement
# ONLY checks 1 condition

"""
My own version of IF and ELSE statements
"""

"""
a = 250
b = 250
qoutient = a/b
if qoutient = 1:
    print("qoutient is equal to 1")
else:
    print("qoutient is somethig other than 1")
"""

# ELIF
# applies more conditions
# to check within the If statement
# if the previous condition is met
# then it will skip all other elifs
"""
weather = "b"

if weather == "cloudy":
    brain.screen.print("its cloudy outside")
elif weather == "rainy":
    brain.screen.print("it's raining outside")
else:
    brain.screen.print("Good weather")
"""


# LOOPS
"""
While - runs repeadetely only while the condition is true

While condition:
    do this code
"""

"""
i = 0
while i < 29:
    brain.screen.print(i)
    i += 1  #i = i+1

new_line()

i = 29
while i < 56:
    brain.screen.print(i)
    i += 1

i = 56
"""

"""
FUNCTION
def function_name(arguments):
    code to do
"""

# multiplication
"""
def mult(a, b):
    product = a * b
    return product

# def - defines the start of the function
# function_name - unique name that represents the function
# arguments - input values needed for the function to work
# return - used to throw out a value for the function

# Call the function with its name
c = mult(67, 57)
brain.screen.print(c)
"""

# division
"""
def div(a, b):
    qoutient = a/b
    return qoutient

c = div(12, 3)
brain.screen.print(c)
"""

# Subtraction
"""
def sub(a, b):
    qoutient = a/b
"""

# Touch brain and see coordinates by activationg this code
"""
brain.screen.clear_screen()
brain.screen.new_line()

def pressingonscreen():
    while True:
        clear()
        is_pressing = brain.screen.pressing()

        if is_pressing:
            x_value = brain.screen.x_position()
            y_value = brain.screen.y_position()
            brain.screen.print_at("Touch at:", x_value, y_value, x = x_value, y = y_value, sep=" ")
            wait(20, MSEC)

pressingonscreen()
"""

def screen_shape():
    x_value = brain.screen.x_position()
    y_value = brain.screen.y_position()

    brain.screen.set_pen_color(Color.BLUE)
    brain.screen.set_fill_color(Color.GREEN)
    brain.screen.draw_rectangle(0, 0, 200, 200)

screen_shape()