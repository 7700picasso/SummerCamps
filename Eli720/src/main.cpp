/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       student01                                                  */
/*    Created:      07/21/2O26, 01:19:57 PM                                     */
/*    Description:  V05 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V05 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here


int add (int a, int b){ 
    return  a + b;
}
    
bool isEqual (int a, int b){
     return a==b;
     }

    int num1 = 1;
    int num2 = 1;


    int main() {
        Brain.Screen.printAt(20, 20, "%d + %d = %d", num1, num2, add(num1, num2));


        if (isEqual(num1, num2)){
            Brain.Screen.printAt(20, 60, "%d is equal to %d", num1, num2);
        }else{
           Brain.Screen.printAt(20, 60, "%d is not equal to %d", num1, num2);
           
           

        }
    }