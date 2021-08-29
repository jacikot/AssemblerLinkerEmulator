# include "../inc/exceptions.h"


std::ostream& operator<<(std::ostream&out,const AssemblerException&exc){
    out<<exc.msg;
}