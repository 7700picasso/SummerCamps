#include "vex.h"
using namespace vex;
vex::brain Brain;
//do not delete above



//DO NOT DELETE
int main() {

    Brain.Screen.setFillColor(yellow);
    Brain.Screen.setPenColor(black);
    Brain.Screen.setPenWidth(2);
    Brain.Screen.drawRectangle(20, 20, 80, 80);
    Brain.Screen.printAt (30, 50, "Press!");

    Brain.Screen.setFillColor(blue);
    Brain.Screen.setPenColor(black);
    Brain.Screen.setPenWidth(2);
    Brain.Screen.drawRectangle(120, 20, 80, 80);
    Brain.Screen.printAt(130, 50, "press!");
   
    Brain.Screen.setFillColor(black);
    Brain.Screen.setPenColor(white);
    Brain.Screen.yPosition();

    Brain.Screen.setFillColor(green);
    Brain.Screen.setPenColor(black);
    Brain.Screen.setPenWidth(2);
    Brain.Screen.drawRectangle(220, 20, 80, 80);
    Brain.Screen.printAt(230, 50, "press!");


    while(true){
        Brain.Screen.printAt(20, 140, "                                                                                                                     ");
         if (Brain.Screen.xPosition()){
            int x = Brain.Screen.xPosition();
            int y = Brain.Screen.yPosition();
            if (x >= 20 && x <= 100 && y >= 20 && y <= 100){
                Brain.Screen.printAt(20, 140, "You Clicked Yellow!");
            }
            else if (x >= 120 && x <= 200 && y >= 20 && y <= 100){
                Brain.Screen.printAt(120, 140, "You Cliked Blue!");
            }
            else if (x >= 220 && x <= 300 && y >= 20 && y <= 100){
                 Brain.Screen.printAt(120, 140, "You Cliked Green!");
            }






        }
        wait(20,msec);
    }







}
//DO NOT DELETE