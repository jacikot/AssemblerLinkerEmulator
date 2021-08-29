
# include <iostream> 
# include <string> 
# include <regex>
# include "../inc/linker.h"
# include "../inc/exceptions.h"

int main (int argc, char *argv[])
{
  int res=0;
  Linker l;
  if(argc<=1)return -1;
  std::regex reg("^-place=([a-zA-Z][a-zA-Z_0-9]*)@([0-9]+)$");
  std::regex reghex("^-place=([a-zA-Z][a-zA-Z_0-9]*)@(0x[0-9A-Fa-f]+)$");
  std::smatch sm;
  for(int i=1;i<argc;){
    if(std::string(argv[i]) ==std::string( "-o")){
      l.outputFile=argv[i+1];
      i+=2;
    }
    else if(std::string(argv[i]) ==std::string( "-hex")){
      l.hex=true;
      i++;
    }
    else if(std::string(argv[i]) ==std::string( "-linkable")){
      l.linkable=true;
      i++;
    }
    else {
      std::string arg=argv[i];
      if(std::regex_match(arg,sm,reg)){
        l.secAddr.insert({sm[1],stoi(sm[2])}); //proveri ove adrese
      }
      else if(std::regex_match(arg,sm,reghex)){
        l.secAddr.insert({sm[1],stoi(sm[2],nullptr,16)});
      }
      else{
        l.files.push_back(arg);
      }
      i++;
    }
  }
  try{
    return l.link();
  }
  catch(LinkerException exc){
    std::cerr<<exc<<std::endl;
    exit(-1);
  }
  
}



