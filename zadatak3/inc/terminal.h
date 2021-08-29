# ifndef TERMINAL_H
# define TERMINAL_H

# define TERM_OUT 0xFF00
# define TERM_IN 0xFF02


#include <termios.h>

void restoreConfig();


class Memory;
class CPU;

class Terminal{
    public:
        void init(Memory*m, CPU*cpu);

        void printout();

        void readin();
    private:
        Memory* memory;
        CPU*cpu;
        struct termios config;
        
        
};


# endif