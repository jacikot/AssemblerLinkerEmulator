# ifndef EXCEPT_EMU
# define EXCEPT_EMU

# include <exception>
# include <string>
# include <iostream>

class EmulatorException: public std::exception{
    public:
        EmulatorException(std::string str):msg(str){}
        friend std::ostream& operator<<(std::ostream&out,const EmulatorException&exc);
    private:
        std::string msg;

};



# endif