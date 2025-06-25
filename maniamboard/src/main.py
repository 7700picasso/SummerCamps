# ---------------------------------------------------------------------------- #
#                                                                              #
# 	Module:       main.py                                                      #
# 	Author:       Student                                                      #
# 	Created:      6/24/2025, 1:14:15 PM                                        #
# 	Description:  V5 project                                                   #
#                                                                              #
# ---------------------------------------------------------------------------- #

# Library imports
from vex import *

# Brain should be defined by default
brain=Brain()



#Conditional Statments
#they help our code make decisions based on conditions
'''
logical Conditions
x > y : lesss then 
x<y :grater than 
x<= y :less than or equal
x >= y grater than or equal
x== y equle to
x !=y not equal
'''


# IF statement

'''
if condtition:
    do this code
'''


x =12
y=8

if x > y:
        brain.screen.print('x is grater than y me tierd')

    # ELSE
    #extension of if statments
#only checks 1 condition
a=100
b=200
sum = a +b
if sum > 100:
    brain.screen.print('aa is grater than 200')
else:
    brain.screen.print('bb is soming els')

#divsion b/a




# ELIF
#applies more conditions
# to check withinthe if statment
# if the previous condition is met
#than it will skip all other elifs

weather = 'sunny'

if weather == 'cloudy':
    brain.screen.print
elif weather=="raniny":
    brain.screen.print("its raining")
#elif condition:
else:
    brain.screen.print("good wether")

# loops
'''
While - runs repeadetly only while the codition is true

While conditon:
    do this code

'''
brain.screen.new_line()
i = 0
while i < 10:
    brain.screen.print(i)
    i += 1  #i= i+1

'''
FUNCTION
def function_name(arguments):
    code to do
'''


def add(a, b):
    sum = a +b
    return sum
#def - defines the start of the function
#function_name - unique name that represents the function
#arguemens - input values needed for the function to work
#return - used to throw out a value from the function



#call the function with its name
c = add(10000123,98438947)
brain.screen.print(c)

brain.screen.new_line()


def pressingOnscreen():
    while True:
        brain.screen.clear_screen()
        is_pressing = brain.screen.pressing

        if is_pressing:
            c

            brain.screen.print_at('touch at', x_value, y_value,x=x_value, y= y_value, sep='')
            wait(20, MSEC)

pressingOnscreen()


def screen_shape():
x_value = brain.screen.x_position()
y_value = brain.screen.y_position()
brain.screen













































































































































































































































































































































































































































































































