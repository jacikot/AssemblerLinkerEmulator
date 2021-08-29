# include "../inc/timer.h"
# include "../inc/memory.h"
# include "../inc/cpu.h"

# include <chrono>
# include <iostream>

void Timer::init(Memory*mem,CPU*proc){
    memory=mem;
    cpu=proc;
    memory->store2(TIM_CFG,0);
    map.insert({0x0,500});
    map.insert({0x1,1000});
    map.insert({0x2,1500});
    map.insert({0x3,2000});
    map.insert({0x4,5000});
    map.insert({0x5,10000});
    map.insert({0x6,30000});
    map.insert({0x7,60000});
    auto time=std::chrono::system_clock::now();
    last=std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch());
}


void Timer::tick(){
    short config=memory->read2(TIM_CFG);
    if(config<0||config>7)return;
    int dur=map.find(config)->second;
    auto time=std::chrono::system_clock::now();
    auto now=std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch());
    auto next=last+std::chrono::milliseconds(dur);
    if(next<=now){
        cpu->notifyInterrupt(Interrupts::TIMER);
        last=now;
    }
    
}