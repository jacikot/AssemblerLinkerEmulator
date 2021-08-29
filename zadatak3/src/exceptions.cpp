# include "../inc/exceptions.h"


std::ostream& operator<<(std::ostream&out,const EmulatorException&exc){
    out<<exc.msg;
}