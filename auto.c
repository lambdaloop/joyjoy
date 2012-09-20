#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     rightW,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     leftW,         tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     belt,          tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     hammer,        tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#include "JoystickDriver.c"
#include "JoystickReader.c"

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

  //file size must be specified along with name, due to robotc limitations
  //using finalStore on recording end will show size after it's finished
  loadData("joy-data.dat", 2784);

  while (pretendJoy(joystick)) //instead of putting "true", get joystick
  {
     runWheels();
     controlMotors();
     
     printCurrentMoment(false); //not really necessary, nice for debugging

     if(joy1Btn(7)) //
       break;
     //wait1Msec(50);
   }

   //storeData("test.dat");
}
