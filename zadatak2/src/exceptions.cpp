# include "../inc/exceptions.h"


std::ostream& operator<<(std::ostream&out,const LinkerException&exc){
    out<<exc.msg;
}