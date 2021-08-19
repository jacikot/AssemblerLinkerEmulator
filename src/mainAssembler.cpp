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
  if (argc>2&&argv[1] == std::string ("-o"))
      drv.outfile=argv[2];
  else drv.outfile=sm[1];
  if (drv.parse (drv.file)) return -1;
  res=drv.assembler.secondPass();

  //print to file
  return res;
}

