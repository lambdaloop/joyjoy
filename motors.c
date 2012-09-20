#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     rightW,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     leftW,         tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     belt,          tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     hammer,        tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#include "JoystickDriver.c" 
#include "JoystickRecorder.c" //this already includes JoystickDriver

void runWheels()
{
  int left, right;

  left  = joystick.joy1_y1;
  right = joystick.joy1_y2;

  motor[leftW] = left;
  motor[rightW] = right;
}

void controlMotors()
{
 if (joy1Btn(2))
 {
   motor[belt] = 30;
 }
 else
 {
   motor[belt] = 0;
 }

 if (joy1Btn(3))
 {
   motor[hammer] = 30;
 }
 else
 {
   motor[hammer] = 0;
 }
}


task main()
{
  nVolume = 0;
  waitForStart();
  bMotorReflected[leftW] = true;
  bMotorReflected[belt]  = true;

  while (true)
  {
     getJoystickSettings(joystick); //same as usual
     runWheels();
     controlMotors();

     addJoystickSettings(); //add the current moment to array
     //printJoy(joystick);
     if(joy1Btn(7))
       break;
   }

   //must use storeData or finalStore at the end to actually write to file
   //they both write the data, but finalStore also displays the size of the
   // file onto the screen for n msecs after it's done
   finalStore("joy-data.dat", 10000);
}
