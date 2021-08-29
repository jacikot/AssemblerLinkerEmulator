# include "../inc/sectionmapper.h"

void SectionMapper::newSectionContent(std::string name, int size){
    char*section=new char[size];
    content.insert({name,section});
}

void SectionMapper::skip(std::string name, int size, int from){
    for(int i=from;i<from+size;i++){
        content.find(name)->second[i]=0;
    }
}

void SectionMapper::init2(std::string name, int value, int from){
    //little endian
    char*data=(char*)&value;
    content.find(name)->second[from]=data[0];
    content.find(name)->second[from+1]=data[1];
}

void SectionMapper::init1(std::string name, int value, int from){
    char*data=(char*)&value;
    content.find(name)->second[from]=data[0];
}


char* SectionMapper::getSectionContent(std::string name){
    return content.find(name)->second;
}