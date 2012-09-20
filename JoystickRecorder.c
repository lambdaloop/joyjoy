#pragma systemFile            // this eliminates warning for "unreferenced" functions

#include "Moment.c" //has JoystickDriver

#define MAX_BYTES 5200
#define MAX_SIZE (MAX_BYTES / MOMENT_SIZE)

Moment data[MAX_SIZE];

int curr = -1;


void resetData()
{
  curr = 0;
  emptyMoment(data[0]);
}

bool addJoy(TJoystick & j)
{
  if(curr==-1)
    resetData();

  if(sameJoyOfMoment(j, data[curr]))
  {
    //printJoy(j);
    data[curr].length++;
  }
  else if (curr+1<MAX_SIZE)
  {
    curr++;
    joyToMoment(j, data[curr]);
    data[curr].length = 1;
  }
  else
  {
    return false;
  }

  nxtDisplayTextLine(1, "i:"+curr);
  nxtDisplayTextLine(2, "l:"+data[curr].length);
  return true;
}

bool addJoystickSettings()
{
  return addJoy(joystick);
}

//flush joystick data into file.
//returns size of file (useful for reading)
int storeData(string filename)
{
  TFileIOResult IoResult;
  TFileHandle FH;
  int fileSize = curr*MOMENT_SIZE;

  Delete(filename, IoResult);
  OpenWrite(FH, IoResult, filename, fileSize);

  for(int i=0; i<=curr; i++)
  {
     WriteMoment(FH, IoResult, data[i]);
  }
  Close(FH, IoResult);
  return fileSize;
}

void finalStore(string filename, int waitTime)
{
  int size = storeData(filename);
  nxtDisplayTextLine(2, "size:" + size);
  wait1Msec(waitTime);
}
