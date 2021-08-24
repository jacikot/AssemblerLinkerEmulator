# include "../h/inputreader.h"
# include <sstream>
# include <regex>

int InputReader::open(std::string name){
    if(!isopen)file.open(name);
    else return -1;
    isopen=true;
    return 0;
}

int InputReader::close(){
    if(isopen)file.close();
    else return -1;
    isopen=false;
    return 0;
}

std::map<int,std::vector<char>> InputReader::read(){
    std::map<int,std::vector<char>> map;
    std::string line;
    while(std::getline(file,line)){
        std::stringstream str(line);
        std::string data;
        std::getline(str,data,' ');
        std::regex reg("^([0-9a-fA-F]*):$");
        std::smatch sm;
        if(!std::regex_match(data,sm, reg)){
            //exception 
            return map;
        }
        int addr=stoi(sm[0],nullptr,16);
        int num;
        std::vector<char> content;
        while(str>>std::hex>>num){
            content.push_back(((char*)(&num))[0]);
        }
        map.insert({addr,content});
    }
    return map;


}

