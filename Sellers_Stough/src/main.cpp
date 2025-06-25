/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      6/24/2024, 9:04:20 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;
brain Brain;
  int add( int a, int b){
    return a+b;
  }

  int main(){
    int myiq = 200;
    int youriq = 0;
    int sum = add(myiq, youriq);
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("The sum of my IQ:%d and your IQ:%d is:%d", myiq, youriq, sum);
    Brain.Screen.newLine();
  }
/*
  
  brain Brain;
  while(true){
    if(Brain.Screen.pressing()){
      int x = Brain.Screen.xPosition();
      int y = Brain.Screen.yPosition();

      if(y<120){
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1,1);
        Brain.Screen.setPenColor(red);
        Brain.Screen.print("hands off");
        wait(2000,msec);
        Brain.Screen.clearScreen();

      }
      else{
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1,1);
        Brain.Screen.setPenColor(red);
        Brain.Screen.print("hands off");
        wait(2000,msec);
        Brain.Screen.clearScreen();
      }
    }
  }

  Brain.Screen.setFillColor(orange);
  Brain.Screen.setPenColor(red);
  Brain.Screen.setPenWidth(100);
  Brain.Screen.drawCircle(240,240,240);
  wait(1000,msec);
  
  //IIIIIIII AMMMMMMMM  THHHHHEEEEEEEE BBBBEEEEESSSSSSTTTTTTTTTTTTTT!!!!!!!!!!!!!!!!!

Brain.Screen.print("Aloha King Sellers ;D");
wait(2000,msec);
Brain.Screen.newLine();
Brain.Screen.print("You are the best!");
//Its true...
wait(2000,msec);
Brain.Screen.newLine();
Brain.Screen.print("I am at your command");
Brain.Screen.printAt(120,110,"Welcome to vex robotics");

//a;lskfjals;dkgh;ldsakgh;lakggalh;kfjklhd;lhjdfs;hldfs;hdjfsg;jhdfak;hjfads;hjdflhjldfahghjdgf;s;jhdgkslahgkdsjlhkgdhjklsgakljkadfsjhkfdsjhkaglkhjgdljkhagsjhhgajksjkhasdghljakwghjkasglkjaghjfkdljagfgjsakljalkrulhreuihreqtueqrtiouyeqrtouertyiyuiorteoyiuertituyoqiytuuiqwytytuiourwyquywyuieqtwyiuqweqiyuweiuyetn,v,nbcnczxnzbznv,,bnmxv,bn,bnmzvxbnmzcvxmbnzvxnmbxzcnbzxbnz,cbvbmncx

while(true){
  if(Brain.Screen.pressing()){
    int x = Brain.Screen.xPosition();
    int y = Brain.Screen.yPosition();
    Brain.Screen.printAt(x,y, "touch at (%d,%d)",x,y);
    wait(1000,msec);
  }
}*/
  
