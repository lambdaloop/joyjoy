#pragma systemFile

#define MOMENT_SIZE 16

#include "JoystickDriver.c"

typedef struct
{
  //stolen from JoystickDriver, apparently RobotC has bugs with structs inside structs... =(
  short   joy1_x1;           // -128 to +127
	short   joy1_y1;           // -128 to +127
	short   joy1_x2;           // -128 to +127
	short   joy1_y2;           // -128 to +127
	short   joy1_Buttons;      // Bit map for 12-buttons
	short   joy1_TopHat;       // value -1 = not pressed, otherwise 0 to 7 for selected "octant".
  long length;               // number of times this "moment" will be repeated
} Moment;

void joyToMoment(TJoystick & j, Moment & m)
{
  m.joy1_x1 = j.joy1_x1;
  m.joy1_x2 = j.joy1_x2;
  m.joy1_y1 = j.joy1_y1;
  m.joy1_y2 = j.joy1_y2;
  m.joy1_Buttons = j.joy1_Buttons;
  m.joy1_TopHat = j.joy1_TopHat;
}

void momentToJoy(Moment & m, TJoystick & j)
{
  j.joy1_x1 = m.joy1_x1;
  j.joy1_x2 = m.joy1_x2;
  j.joy1_y1 = m.joy1_y1;
  j.joy1_y2 = m.joy1_y2;
  j.joy1_Buttons = m.joy1_Buttons;
  j.joy1_TopHat = m.joy1_TopHat;
}

void printJoy(TJoystick & j)
{
  nxtDisplayTextLine(3, "x1:"+j.joy1_x1+"  x2:"+j.joy1_x2);
  nxtDisplayTextLine(4, "y1:"+j.joy1_y1+"  y2:"+j.joy1_y2);
	nxtDisplayTextLine(5, "Buttons:"+j.joy1_Buttons);
	nxtDisplayTextLine(6, "TopHat :"+j.joy1_TopHat);
}

void printMoment(Moment & m)
{
  nxtDisplayTextLine(3, "x1:"+m.joy1_x1+"  x2:"+m.joy1_x2);
  nxtDisplayTextLine(4, "y1:"+m.joy1_y1+"  y2:"+m.joy1_y2);
	nxtDisplayTextLine(5, "Buttons:"+m.joy1_Buttons);
	nxtDisplayTextLine(6, "TopHat :"+m.joy1_TopHat);
	nxtDisplayTextLine(7, "length :"+m.length);
}

void printJoys(TJoystick & j1, TJoystick & j2)
{
  nxtDisplayTextLine(2, "j1: "+j1.joy1_x1+"  j2:" + j2.joy1_x1);
  nxtDisplayTextLine(3, "j1: "+j1.joy1_x2+"  j2:" + j2.joy1_x2);
  nxtDisplayTextLine(4, "j1: "+j1.joy1_y1+"  j2:" + j2.joy1_y1);
	nxtDisplayTextLine(5, "j1: "+j1.joy1_y2+"  j2:" + j2.joy1_y2);
	nxtDisplayTextLine(6, "j1: "+j1.joy1_Buttons+"  j2:" + j2.joy1_Buttons);
	nxtDisplayTextLine(7, "j1: "+j1.joy1_TopHat+"  j2:" + j2.joy1_TopHat);
}

void printJoyMoment(TJoystick & j, Moment & m)
{
  nxtDisplayTextLine(2, "j: "+j.joy1_x1+"  m:" + m.joy1_x1);
  nxtDisplayTextLine(3, "j: "+j.joy1_x2+"  m:" + m.joy1_x2);
  nxtDisplayTextLine(4, "j: "+j.joy1_y1+"  m:" + m.joy1_y1);
	nxtDisplayTextLine(5, "j: "+j.joy1_y2+"  m:" + m.joy1_y2);
	nxtDisplayTextLine(6, "j: "+j.joy1_Buttons+"  m:" + m.joy1_Buttons);
	nxtDisplayTextLine(7, "j: "+j.joy1_TopHat+"  m:" + m.joy1_TopHat);
}

bool sameJoystick(TJoystick & j1, TJoystick & j2)
{

  return ((abs(j1.joy1_x1 - j2.joy1_x1) <= 5) &&
          (abs(j1.joy1_x2 - j2.joy1_x2) <= 5) &&
          (abs(j1.joy1_y1 - j2.joy1_y1) <= 5) &&
	        (abs(j1.joy1_y2 - j2.joy1_y2) <= 5) &&
    	    ( j1.joy1_Buttons -  j2.joy1_Buttons == 0) &&
	        ( j1.joy1_TopHat -  j2.joy1_TopHat == 0));
}

bool sameJoyOfMoment(TJoystick & j, Moment & m)
{
  return ((abs(j.joy1_x1 - m.joy1_x1) <= 5) &&
          (abs(j.joy1_x2 - m.joy1_x2) <= 5) &&
          (abs(j.joy1_y1 - m.joy1_y1) <= 5) &&
	        (abs(j.joy1_y2 - m.joy1_y2) <= 5) &&
    	    ( j.joy1_Buttons -  m.joy1_Buttons == 0) &&
	        ( j.joy1_TopHat -  m.joy1_TopHat == 0));
}

void WriteJoystick(TFileHandle F, TFileIOResult IoResult, TJoystick & j)
{
  WriteShort(F, IoResult, j.joy1_x1);
  WriteShort(F, IoResult, j.joy1_x2);
  WriteShort(F, IoResult, j.joy1_y1);
  WriteShort(F, IoResult, j.joy1_y2);
  WriteShort(F, IoResult, j.joy1_Buttons);
  WriteShort(F, IoResult, j.joy1_TopHat);
}

void ReadJoystick(TFileHandle F, TFileIOResult IoResult, TJoystick & j)
{
  ReadShort(F, IoResult, j.joy1_x1);
  ReadShort(F, IoResult, j.joy1_x2);
  ReadShort(F, IoResult, j.joy1_y1);
  ReadShort(F, IoResult, j.joy1_y2);
  ReadShort(F, IoResult, j.joy1_Buttons);
  ReadShort(F, IoResult, j.joy1_TopHat);
}

void WriteMoment(TFileHandle F, TFileIOResult IoResult, Moment & m)
{
  WriteShort(F, IoResult, m.joy1_x1);
  WriteShort(F, IoResult, m.joy1_x2);
  WriteShort(F, IoResult, m.joy1_y1);
  WriteShort(F, IoResult, m.joy1_y2);
  WriteShort(F, IoResult, m.joy1_Buttons);
  WriteShort(F, IoResult, m.joy1_TopHat);
  WriteLong(F, IoResult, m.length);
}


void ReadMoment(TFileHandle F, TFileIOResult IoResult, Moment & m)
{
  ReadShort(F, IoResult, m.joy1_x1);
  ReadShort(F, IoResult, m.joy1_x2);
  ReadShort(F, IoResult, m.joy1_y1);
  ReadShort(F, IoResult, m.joy1_y2);
  ReadShort(F, IoResult, m.joy1_Buttons);
  ReadShort(F, IoResult, m.joy1_TopHat);
  ReadLong(F, IoResult, m.length);
}

void emptyMoment(Moment & m)
{
  m.joy1_x1 = 0;
	m.joy1_x2 = 0;
	m.joy1_y1 = 0;
	m.joy1_y2 = 0;
	m.joy1_Buttons = 0;
	m.joy1_TopHat = -1;
	m.length = 0;
}
