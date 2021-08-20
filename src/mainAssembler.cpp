# include "../h/driver.h"
# include <iostream> 
# include <regex>
# include <string> 

int main (int argc, char *argv[])
{
  int res = 0;
  Driver drv;
  if(argc<=1)return -1;
  drv.file=argv[1];
  std::regex reg("^([^.]*)\\.[^.]*$");
  std::smatch sm;
  bool f=std::regex_match(drv.file,sm,reg);
  if(!f) return -1;
  if (argc>2&&argv[2] == "-o")
      drv.outfile=argv[3];
  else {
    drv.outfile=sm[1];
    drv.outfile+=".o";
  }
  if (drv.parse (drv.file)) return -1;
  res=drv.assembler.secondPass();
  if(res<0)return res;
  res=drv.assembler.output(drv.outfile);
  //print to file
  return res;
}

