#include "runtime_exception.h"

runtime_exception::runtime_exception(){
    msg = (const char*)"runtime exception";
}
runtime_exception::runtime_exception(const char* t){
    msg = t;
}
runtime_exception::runtime_exception(const str& t){
    msg = t.c_str();
}
const char * runtime_exception::what() const noexcept{
    return msg;
}