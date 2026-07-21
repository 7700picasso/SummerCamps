 #include "vex.h"

 using namespace vex;

 vex::brain       Brain;

 float number1 = 1.23456; 
 int loopNumbr = 0;

 int add (int a, int b) {
    return a + b;
 }

 bool isEqual (int a, int b){
  return a == b;
 }
int num1 = 5;
int num2 = 5;

int main() {
    Brain.Screen.printAt(20, 20, "%d + %d = %d", num1, num2, add( num1,  num2));

    if (isEqual( num1, num2)){
        Brain.Screen.printAt(20, 60,"%d is equal to %d", num1, num2);
    } else {
        Brain.Screen.printAt(20, 60, "%d is not equal %d", num1, num2);
    }
}