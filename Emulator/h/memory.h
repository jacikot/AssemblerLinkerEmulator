# ifndef MEMORY
# define MEMORY

# define CAPACITY 0x10000


# include <string>
# include "memory.h"
# include <map>
# include <vector>

class Memory{
    public:
        int initialize( std::map<int,std::vector<char>>&content);

        char read1(int address);
    private:
        char memory[CAPACITY];
        

};


# endif