# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       student                                                      #
# 	Created:      6/24/2025, 1:08:45 PM                                        #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()

#brain.screen.print ("Hello V5")

# Conditional statements
# the help our code make decisions based on condisions

'''
Lodical Condistions
x < y : Less Than
x > y : Greater Than
x <= y : Less Than or Equal to
x >= y : Greater Than or Equal to
x == y : Equal to 
x != y : NOT equal

'''

#IF Statement

'''
snytax

If condition: 
    do this
'''


x = 2
y = 1

if x > y:
    brain.screen.print("x is greater than y ")


# ELSE
# extention of 
# OLNY checks 1 condition
a = 100 
b = 200
sum = a + b
# if sum > 100:
#     brain.screen.print("YES SIR")
#     brain.screen.clear_screen()
# else:
#     brain.screen.print("NOPE")
#     brain.screen.clear_screen()



# My own version
c = 3
d = 2
hi = d * c 
# if hi > 100:
#     brain.screen.print("6 is greater than 100")
# else:
#     brain.screen.print("100 is greater than 6")


# Weather variable
# ELIF applies more conditions 
# to check withen IF statement
# if the first codition is meet
# then it will skip all of the other elifs

# weather = "stormy"

# if weather == "cloudy":
#         brain.screen.print("Its cloudy outside")
# elif weather == "rainy":
#     brain.screen.print("Its cloudy outside")
# elif weather == "stormy":
#     brain.screen.print("It is stormy outside")
# #eli condition
# else:
#      brain.screen.print("Good weather")


#----------------------------------------------------------------------------------------------------------------#
#                                                                                                                #
#                                                                                                                #
#                                                                                                                #
#                                                                                                                #
#----------------------------------------------------------------------------------------------------------------#


#LOOPS
'''
While - runs repedtly olny while the conditions is true

Whille condition
    do this code

'''



i = 0
while i < 10:
    brain.screen.print(i)
    i +=1 #i= i+1


brain.screen.new_line()

'''
FUNTION
def funtion_name:(arguments)
    code to do
'''

brain.screen.clear_screen()
brain.screen.new_line()

def multipy(a, b):
    sum = a * b
    return sum

# def - defines the start of a fucntion
# function_name - unique name that repersents the function
# arguments - input values needed for the funtion to work 
# return - used tho throw out a value from the funtion

# CALL THE FUNCTION WITH ITS NAME
c = multipy(427 ,576)
brain.screen.print(c)

brain.screen.clear_screen()
brain.screen.new_line()

# #while True:
#         ##is_pressing = brain.screen.pressing()
    
#         #if is_pressing:
#             ##y_value = brain.screen.y_position()
            

#             brain.screen.print_at("Touch at :", x_value, y_value, x = x_value, y = y_value , sep=" ")
#             wait(20, MSEC)

# pressingOnScreen()



def screen_shape():
    x_value = brain.screen.x_position()
    y_value = brain.screen.y_position()

    brain.screen.set_pen_color(Color.BLUE)
    brain.screen.set_fill_color(Color.GREEN)
    brain.screen.draw_circle(240,137,50)

screen_shape()

