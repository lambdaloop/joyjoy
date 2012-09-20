#pragma systemFile            // this eliminates warning for "unreferenced" functions

#include "Moment.c" //has JoystickDriver

#define MAX_BYTES 5200
#define MAX_SIZE (MAX_BYTES / MOMENT_SIZE)

Moment data[MAX_SIZE];
int curr = 0;
int number = 0;

void loadData(string filename, int fileSize)
{
  TFileIOResult IoResult;
  TFileHandle FH;
  OpenRead(FH, IoResult, filename, fileSize);
  int n = fileSize / MOMENT_SIZE;
  for(int i=0; i<n; i++)
  {
     ReadMoment(FH, IoResult, data[i]);
    // nxtDisplayTextLine(2, " "+data[i].length);
  }
  curr = 0;
  number = n;
  //nxtDisplayTextLine(7, ""+number);
}

bool nextData()
{
  if(curr+1>=number)
  {
    return false;
  }
  else
  {
    curr++;
    return true;
  }
}


bool pretendJoy(TJoystick & j)
{
  while (data[curr].length <= 0)
  {
    if(curr>=number)
      return false;
    else
      curr++;
  }
  //momentToJoy(data[curr], j);
  j.joy1_x1 = data[curr].joy1_x1;
  j.joy1_x2 = data[curr].joy1_x2;
  j.joy1_y1 = data[curr].joy1_y1;
  j.joy1_y2 = data[curr].joy1_y2;
  j.joy1_Buttons = data[curr].joy1_Buttons;
  j.joy1_TopHat = data[curr].joy1_TopHat;

  data[curr].length--;

  return true;
}

void printCurrentMoment(bool pMoment)
{
  nxtDisplayTextLine(1, "i:"+curr);
  nxtDisplayTextLine(2, "l:"+data[curr].length);
  if(pMoment)
    printMoment(data[curr]);
}
