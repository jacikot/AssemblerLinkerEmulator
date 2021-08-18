# include <string>
# include <vector>


enum RelocationType{
    R_386_16, R_386_PC16
};

class RelocationRecord{
    public:
        RelocationRecord(int o,RelocationType t,std::string n, std::string s):offset(o),type(t),name(n), section(s){}

        //section
        std::string section;

        //offset from beginning of the section
        int offset;

        //type
        RelocationType type;

        //symbol name
        std::string name;

};

class RelocationTable{
    public:
        void addRecord(int offset,RelocationType type,std::string name, std::string section){
            records.push_back(RelocationRecord(offset,type,name,section));
        }
    private:
        std::vector<RelocationRecord> records;
};