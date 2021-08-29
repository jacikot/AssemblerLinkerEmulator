# include "../inc/driver.h"
# include "../inc/exceptions.h"
# include <iostream> 
# include <regex>
# include <string> 

int main (int argc, char *argv[])
{
  int res = 0;
  Driver drv;
  if(argc<=1)return -1;
  drv.outfile="";
  for(int i=1;i<argc;){
    if(std::string(argv[i]) ==std::string( "-o")){
      drv.outfile=argv[i+1];
      i+=2;
    }
    else{
      drv.file=argv[i];
      i++;
    }
  }

  if(drv.outfile==""){
    std::regex reg("^([^.]*)\\.[^.]*$");
    std::smatch sm;
    bool f=std::regex_match(drv.file,sm,reg);
    drv.outfile=sm[1];
    drv.outfile+=".o";
  }
  try{
    if (drv.parse (drv.file)) return -1;
    res=drv.assembler.secondPass();
    if(res<0)return res;
    res=drv.assembler.output(drv.outfile);
    return res;
  }
  catch(AssemblerException exc){
    std::cerr<<exc<<std::endl;
    
  }
  exit(-1);
  
}

