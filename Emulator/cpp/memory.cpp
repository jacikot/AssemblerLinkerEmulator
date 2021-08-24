# include "../h/memory.h"
# include <algorithm>
# include "../h/emulator.h"

int Memory::initialize( std::map<int,std::vector<char>>&content){
    std::for_each(content.begin(),content.end(),[=](std::pair<int,std::vector<char>>p){
        if((p.first+p.second.size())>CAPACITY){
            //error
            return;
        }
        for(int i=0;i<p.second.size();i++){
            memory[p.first+i]=*(p.second.begin()+i);
        }
    });
}


char Memory::read1(int address){
    if(address>=0x10000){
        //exception
        return InstructionType::ERROR;
    }
    return memory[address];
}

short Memory::read2(int address){
    if(address+1>=0x10000){
        //exception
        return InstructionType::ERROR;
    }
    return *((short*)(memory+address));
}

void Memory::store2(int address,short data){
    if(address+1>=0x10000){
        //exception
        return;
    }
    *((short*)(memory+address))=data;
}