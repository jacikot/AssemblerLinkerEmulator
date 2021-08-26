# ifndef EXCEPT_LIN
# define EXCEPT_LIN

# include <exception>
# include <string>
# include <iostream>

class LinkerException: public std::exception{
    public:
        LinkerException(std::string str):msg(str){}
        friend std::ostream& operator<<(std::ostream&out,const LinkerException&exc);
    private:
        std::string msg;

};



# endif