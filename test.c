task main
{
  string filename = "kosha";
  TFileIOResult IoResult;
  TFileHandle FH;
  int fileSize = 1;
  Delete(filename, IoResult);
  OpenWrite(FH, IoResult, filename, fileSize);
  nxtDisplayTextLine(1, "io:"+IoResult);
  //wait10Msec(300);
  while(IoResult == ioRsltFileExists)
  {
    nxtDisplayTextLine(2, "correcting...");
    Close(FH, IoResult);
    nxtDisplayTextLine(5, "io:"+IoResult);
    Delete(filename, IoResult);
    nxtDisplayTextLine(4, "io:"+IoResult);
    OpenWrite(FH, IoResult, filename, fileSize);
    nxtDisplayTextLine(3, "io:"+IoResult);
  }
  nxtDisplayTextLine(4, "io:"+IoResult);
  wait10Msec(400);
  WriteByte(FH, IoResult, 2);
  Close(FH, IoResult);
}
