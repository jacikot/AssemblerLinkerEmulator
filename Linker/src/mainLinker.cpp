
# include <iostream> 
# include <string> 
# include <regex>
# include "../h/linker.h"

int main (int argc, char *argv[])
{
  int res=0;
  Linker l;
  if(argc<=1)return -1;
  std::regex reg("^-place=([a-zA-Z][a-zA-Z_0-9]*)@([0-9]+)$");
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
        l.secAddr.insert({sm[1],stoi(sm[2])});
      }
      else{
        l.files.push_back(arg);
      }
      i++;
    }
  }
  if(!l.hex && !l.linkable)return -1;
  l.readFiles();
  return res;
}

