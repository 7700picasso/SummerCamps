/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      7/20/2026, 1:19:21 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here


// add function
// int add (int a, int b){
//     return a + b;
// }

bool isEqual(int a, int b){
    return a==b;
}

int num1 = 5;
int num2 = 3;


int main() {
    // Brain.Screen.printAt(20, 20, "%d + %d = %d", num1, num2, add(num1, num2));


    if (isEqual(num1, num2)){
        Brain.Screen.printAt(20, 60, "%d is equal to %d", num1, num2);
    } else {
        Brain.Screen.printAt(20, 60, "%d is not equal to %d", num1, num2);
    }
}


// float number1 = 1.234567;
// int loopNumber = 0;

// int main() {
//     Brain.Screen.setFillColor(black);
//     Brain.Screen.setPenColor(red);
//     Brain.Screen.setPenWidth(2);
//     Brain.Screen.drawRectangle(20, 20, 80, 80);
//     Brain.Screen.printAt(30, 50, "Press!");

//     Brain.Screen.setFillColor(black);
//     Brain.Screen.setPenColor(blue);
//     Brain.Screen.setPenWidth(2);
//     Brain.Screen.drawRectangle(120, 20, 80, 80);
//     Brain.Screen.printAt(130, 50, "Press!");

//     Brain.Screen.setFillColor(black);
//     Brain.Screen.setPenColor(green);
//     Brain.Screen.setPenWidth(2);
//     Brain.Screen.drawRectangle(220, 20, 80, 80);
//     Brain.Screen.printAt(230, 50, "Press!");

//     while(true){
//         //Brain.Screen.clearLine(140);
//         Brain.Screen.printAt(20, 140, "                                         ");
//         Brain.Screen.printAt(130, 140, "                                        ");
//         Brain.Screen.printAt(230, 140, "                                        ");
//         loopNumber++;
//         if (Brain.Screen.pressing()){
//             int x = Brain.Screen.xPosition();
//             int y = Brain.Screen.yPosition();
//             Brain.Screen.setPenColor(red);
//             if (x >= 20 && x <= 100 && y >= 20 && y <= 100){
//                 Brain.Screen.printAt(20, 140, "You Clicked Me!");
//             }
//             else if (Brain.Screen.pressing()){
//                 int x = Brain.Screen.xPosition();
//                 int y = Brain.Screen.yPosition();
//                 Brain.Screen.setPenColor(blue);
//                 if (x >= 130 && x <= 210 && y >= 20 && y <= 100){
//                     Brain.Screen.printAt(130, 140, "You Clicked Me!");
//                 }
//             }
//             else if (Brain.Screen.pressing()){
//                 int x = Brain.Screen.xPosition();
//                 int y = Brain.Screen.yPosition();
//                 Brain.Screen.setPenColor(green);
//                 if (x >= 230 && x <= 310 && y >= 20 && y <= 100){
//                     Brain.Screen.printAt(230, 140, "You Clicked Me!");
//                 }
//             }
//         }
//         wait(20, msec);
//     }
// }

// int main() {

// //Loop to continuously monitor touch events
// while(true){
//     //Clear screen
//     Brain.Screen.clearScreen();
//         //Check if the screen is being pressed
//         if(Brain.Screen.pressing()) {
//             // Get the X and Y coordinates of the touch
//             int x = Brain.Screen.xPosition();
//             int y = Brain.Screen.yPosition();

//             //Print the coordinates of the touch
//             Brain.Screen.printAt(x, y, "Touch at (%d, %d)", x, y);

//             //Wait for a short time to avoid repeated prints during a single touch event
//             wait(500, msec);
//         }
//     }
// }


    // Brain.Screen.printAt(1,1, "This value is %.5f", number1);

    // wait(3000, msec);
//while (loopNumber < 10){
    // Brain.Screen.clearScreen();
    // Brain.Screen.printAt(240, 135, "hola");
    // wait(1000, msec);
    // Brain.Screen.clearScreen();
    // wait(1000, msec);
    // loopNumber = loopNumber + 1;