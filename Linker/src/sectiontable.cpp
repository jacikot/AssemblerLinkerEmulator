# include "../h/sectiontable.h"
# include <algorithm>
# include "../h/exceptions.h"

bool SectionTable::exist(std::string name){
    return sectionMap.find(name)!=sectionMap.end();
}

void SectionTable::insertSection(SectionsData& data, int fileID){
    if(!exist(data.name)){
        std::map<int,SectionsData> map;
        sectionMap.insert({data.name, new std::map<int,SectionsData*>()});
    }
    sectionMap.find(data.name)->second->insert({fileID,new SectionsData(data)});
}


void SectionTable::setContent(std::string name, int fileID,char*cnt){
    sectionMap.find(name)->second->find(fileID)->second->content=cnt;
}


bool SectionTable::resolveSectionOffsets(bool hex,std::map<std::string,int>& secAddr){
    int start=0;
    if(hex){
        std::for_each(sectionMap.begin(),sectionMap.end(),[=, &start](std::pair<std::string,std::map<int,SectionsData*>*>p){//foreach section name
            int addr; //starting address
            if(secAddr.find(p.first)!=secAddr.end()){
                addr=secAddr.find(p.first)->second;
                std::for_each(p.second->begin(),p.second->end(),[&addr](std::pair<int,SectionsData*>d){
                    d.second->value=addr;
                    addr+=d.second->size;
                });
                if(start<addr)start=addr;
            }
        });
    }
    std::for_each(sectionMap.begin(),sectionMap.end(),[=, &start](std::pair<std::string,std::map<int,SectionsData*>*>p){//foreach section name
        int addr; //starting address
        if(secAddr.find(p.first)==secAddr.end()){
            addr=start;
            std::for_each(p.second->begin(),p.second->end(),[&addr](std::pair<int,SectionsData*>d){
                d.second->value=addr;
                addr+=d.second->size;
            });
            if(hex)start=addr;
        }
    });
    if(hex) return checkAddresses();
    else return true;
}

SectionTable::~SectionTable(){
    std::for_each(sectionMap.begin(),sectionMap.end(),[](std::pair<std::string,std::map<int,SectionsData*>*>p){
        std::for_each(p.second->begin(),p.second->end(),[](std::pair<int,SectionsData*>d){
           delete d.second; 
        });
        delete p.second;
    });
}

int SectionTable::getValue(std::string sec, int fileID){
    return sectionMap.find(sec)->second->find(fileID)->second->value;
}


char* SectionTable::getContent(std::string sec, int fileID,int offset){
    return sectionMap.find(sec)->second->find(fileID)->second->content+offset;
}


std::vector<SectionsData> SectionTable::getLinkerData(){
    std::vector<SectionsData> ret;
    int i=0;
    std::for_each(sectionMap.begin(),sectionMap.end(),[=, &i, &ret](std::pair<std::string,std::map<int,SectionsData*>*> p){
        SectionsData data;
        data.name=p.first;
        data.global=false;
        int size=0;
        int value=MAX_ADDR;
        std::for_each(p.second->begin(),p.second->end(),[&size,&value](std::pair<int,SectionsData*> p){
            size+=p.second->size;
            if(value>p.second->value)value=p.second->value;

        });
        data.size=size;
        data.value=value;
        char*cnt=new char[size];
        int cursor=0;
        std::for_each(p.second->begin(),p.second->end(),[cnt, &cursor](std::pair<int,SectionsData*> p){
            for(int i=0;i<p.second->size;i++){
                cnt[i+cursor]=p.second->content[i];
            }
        });
        data.content=cnt;
        ret.push_back(data);

    });
    std::sort(ret.begin(),ret.end(),[](SectionsData d1, SectionsData d2)->bool{
        return d1.value<d2.value;
    });
    return ret;
}


bool SectionTable::checkAddresses(){
    std::vector<SectionsData> ret=getLinkerData();
    for(auto i=ret.begin();i!=(ret.end()-1);i++){
        if(i->value+i->size>(i+1)->value){
            throw LinkerException("Sections "+ i->name+" and "+(i+1)->name+" overlap!");
        }
    }
    return true;
}