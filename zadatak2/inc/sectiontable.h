# ifndef SECTAB_LIN
# define SECTAB_LIN

#define MAX_ADDR 0xFFFF

#include <map>
# include "inputreader.h"
# include <string>
# include <vector>

class SectionTable{
    public:
        bool exist(std::string);

        void insertSection(SectionsData& data, int fileID);

        void setContent(std::string name, int fileID,char*cnt);

        bool resolveSectionOffsets(bool hex,std::map<std::string,int>& secAddr);

        ~SectionTable();

        int getValue(std::string sec, int fileID);

        char* getContent(std::string sec, int fileID,int offset);

        bool checkAddresses();

        int size(){
            return sectionMap.size();
        }
        std::vector<SectionsData> getLinkerData();

    private:
        std::map<std::string,std::map<int,SectionsData*>*> sectionMap;
};

#endif