# ifndef IN_RD_EMU
# define IN_RD_EMU

# include <string>
# include <map>
# include <fstream>
# include <vector>

class InputReader{
    public:
        int open(std::string name);
        int close();
        std::map<int,std::vector<char>> read();
    private:
        bool isopen;
        std::ifstream file;

};


# endif