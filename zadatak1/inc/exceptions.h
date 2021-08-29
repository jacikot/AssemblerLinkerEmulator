# ifndef EXCEPT_ASM
# define EXCEPT_ASM

# include <exception>
# include <string>
# include <iostream>

class AssemblerException: public std::exception{
    public:
        AssemblerException(std::string str):msg(str){}
        friend std::ostream& operator<<(std::ostream&out,const AssemblerException&exc);
    private:
        std::string msg;

};



# endif