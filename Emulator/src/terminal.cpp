# include "../h/terminal.h"
# include "../h/memory.h"
# include "../h/cpu.h"

#include <iostream>
#include <unistd.h>
#include <termios.h>



struct termios oldCONFIG;

volatile bool exitTerminal = false;

void restoreConfig() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldCONFIG);
}

void cleanTerminal(int sig){ 
  restoreConfig();
  exitTerminal = true;
}

void Terminal::init(Memory*mem, CPU*processor){
    memory=mem;
    cpu=processor;
    memory->store2(TERM_IN,0xFFFF);
    memory->store2(TERM_OUT,0xFFFF);

    int status = tcgetattr(STDIN_FILENO, &oldCONFIG); //get curent configuration to config
    if ( status < 0) {
        //exception
        return;
    }

    config=oldCONFIG;
    //configuration
    config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
    config.c_cflag &= ~(CSIZE | PARENB);
    config.c_cflag |= CS8;
    config.c_cc[VMIN] = 0;
    config.c_cc[VTIME] = 0;

    //set configuration
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &config)) {
        //exception
    }
    //it is called before exit
    if (atexit(restoreConfig) != 0) {
        //exception
    }

    if (exitTerminal) exit(-1);
}


void Terminal::printout(){
    char checkB=memory->read1(TERM_OUT+1);
    if(checkB==-1) return;
    std::cout<<memory->read1(TERM_OUT)<<std::flush;
    memory->store2(TERM_OUT,0xFFFF);
}

void Terminal::readin(){
    unsigned char c;
    
    if (read(STDIN_FILENO, &c, 1) == 1) {
        short x=c&0xFF;
        memory->store2(TERM_IN,x);
        cpu->notifyInterrupt(Interrupts::TERMINAL);
    }
    if (exitTerminal) exit(1);
}

