# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student2                                                     #
# 	Created:      6/24/2025, 1:07:23 PM                                        #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()

       
#hibyewhywhowhenwherewhatidklalalatadisol
#Conditional Statements
# they help our code make desicions based on conditions
"""
Logical Conditions
x < y : Less Than
x > y : Greater Than
x <= y : Less Than or Equal to
x >= y : Greater Than or Equal to
x == y : Equal To
x != y : NOT equal
"""

# IF Statement
"""
SYNTAX

if condition:
    do this code
"""
hi = brain.screen.print
yo = brain.screen.clear_screen
la = brain.screen.new_line

"""
x = 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1
y = 2
if x > y:
    yo(Color.YELLOW)
    hi("lalalalallalalalalalalalalalalalalala")
else:
    yo(Color.RED)
wait(2000, MSEC)
yo()
la()
#ELSE
#extension of IF statements
# ONLY checks 1 condition
a = 100
b = 200
sum = a + b
if sum > 100:
    hi("i don't know....")
else:
    hi("whyyy....")

wait(5000, MSEC)
yo()
la()

a = 2
b = 5
sum = a * b
if sum == 10:
    hi("Yes")
else:
    hi("no")

wait(5000, MSEC)
yo()
la()


# ELIF
# applies more conditions
# to check within the IF statement
# if the previous condition is met 
# then it will skip all other elifs
weather = "sunny"

if weather == "cloudy":
    hi("It is not sunny, it is cloudy =(")
elif weather == "rainy":
    hi("It is not sunny, it is rainy =(")
elif weather == "sunny":
    yo(Color.YELLOW)
    hi("IT IS SUNNYYYY!!!!")
else:
    hi("I don't know")

# LOOPS
"""
"""
While - runs repeadetly only while the condition is true

While condition:
    do this code
"""
"""

wait(5000, MSEC)
yo()
la()

"""
"""
i = 0
while i < 29:
    hi(i)
    i += 1
la()
while i < 53:
    hi(i)
    i += 1
la()
while i < 77:
    hi(i)
    i += 1
la()
while i < 101:
    hi(i)
    i += 1
la()
while i < 117:
    hi(i)
    i += 1
la()
while i < 133:
    hi(i)
    i += 1
la()
while i < 149:
    hi(i)
    i += 1
la()
while i < 165:
    hi(i)
    i += 1
la()
while i < 181:
    hi(i)
    i += 1
la()
while i < 197:
    hi(i)
    i += 1
la()
while i < 213:
    hi(i)
    i += 1
la()
while i < 229:
    hi(i)
    i += 1
"""

"""
"""
"""
FUNCTION
def funtion_name(arguments):
    code to do


def add(a, b):
    sum = a + b
    return sum

#def - defines the start of the function
# function_name - unique name that represents the function
# arguments - input values needed for the function to work
# return - used to throw out a value from the function


#CALL THE FUNCTION WITH ITS NAME
c = add(67,57)
hi(c)


def mult(a, b):
    sum = a * b
    return sum

c = mult(2,2)
hi(c)
"""
"""
"""
"""
def press():
    while True:
        yo()
        is_pressing = brain.screen.pressing()

        if is_pressing:
            x_value = brain.screen.x_position()
            y_value = brain.screen.y_position()

            brain.screen.print_at("Touch at:", x_value, y_value,x = x_value, y = y_value, sep=" ")
            wait(20, MSEC)

press()
"""

a = 0
while True:
    brain.screen.print_at(a, x = 240, y = 135)
    a += 1
    wait(.000000005, MSEC)
    la()



"""

def sshape():
    x_value = brain.screen.x_position()
    y_value = brain.screen.y_position()

    brain.screen.set_pen_color(Color.BLUE)
    brain.screen.set_fill_color(Color.GREEN)
    brain.screen.draw_circle(240,137,50)

sshape()
    """