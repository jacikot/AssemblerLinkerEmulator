
# include <iostream> 
# include <string> 

#include "../h/emulator.h"
int main (int argc, char *argv[])
{
  // std::cout<<"JANA"<<std::endl;
  int res=0;
  Emulator emulator;
  if(argc<=1)return -1;
  emulator.inputFile=argv[1];
  emulator.init();
  emulator.emulate();
 
}



