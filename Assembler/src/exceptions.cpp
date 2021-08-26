# include "../h/exceptions.h"


std::ostream& operator<<(std::ostream&out,const AssemblerException&exc){
    out<<exc.msg;
}