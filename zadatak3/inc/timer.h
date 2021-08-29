# ifndef TIMER_H
# define TIMER_H

class Memory;
class CPU;

# define TIM_CFG 0xFF10 

# include <chrono>
# include <map>

class Timer{
    public:
        void init(Memory*mem,CPU*cpu);

        void tick();
    private:
        Memory*memory;
        CPU*cpu;
        std::chrono::milliseconds last;
        std::map<short,int> map;

};



# endif