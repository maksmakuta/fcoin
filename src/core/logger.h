#ifndef FCOIN_LOGGER_H
#define FCOIN_LOGGER_H

#include <iostream>
#include <chrono>
#include "constants.h"

extern char endl;

class Log{
public:
    static Log i;
    static Log d;
    static Log w;
    static Log e;

    explicit Log(const str& h);

    template<typename T>
    Log& operator<< (const T& data){
        if(newline){
            this->stream << data;
        }else{
            this->stream << '['<< datetime() << "] " << header << data;
            newline = true;
        }
        return *this;
    }

    Log& operator<< (char data){
        this->stream << data;
        if(data == endl)
            newline = false;
        return *this;
    }

private:
    bool newline = false;
    str header;
    std::ostream& stream = std::cout;

    static str datetime(){
        return (strss() <<  std::chrono::zoned_time { std::chrono::current_zone(), std::chrono::system_clock::now() }).str();
    }
};

#endif //FCOIN_LOGGER_H
