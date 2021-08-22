# ifndef LINKER_H
# define LINKER_H


# include <string>
# include <map>
# include <vector>
# include "inputreader.h"

class Linker{
    public:
        int readFiles();
    public:
        std::string outputFile="";
        bool hex=false;
        bool linkable=false;
        std::map<std::string,int> secAddr;
        std::vector<std::string> files;

    private:
        InputReader reader;


};


# endif
