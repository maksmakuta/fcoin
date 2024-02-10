#ifndef FCOIN_LOGGER_H
#define FCOIN_LOGGER_H

#include <iostream>
#include "constants.h"

char endl();

class Log{
public:
    static Log i();
    static Log d();
    static Log w();
    static Log e();

    template<typename T>
    Log& operator<< (const T& data){
        if(newline){
            this->stream << data;
        }else{
            this->stream << header << data;
            newline = true;
        }
        return *this;
    }

    Log& operator<< (char data){
        this->stream << data;
        if(data == endl())
            newline = false;
        return *this;
    }

private:
    bool newline = false;
    str header;
    std::ostream& stream = std::cout;
};

#endif //FCOIN_LOGGER_H
