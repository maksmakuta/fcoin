#include "logger.h"

#define RES "\033[0m"

void Log::i(const str& msg){
    log(msg,0);
}

void Log::d(const str& msg){
    log(msg,1);
}

void Log::w(const str& msg){
    log(msg,2);
}

void Log::e(const str& msg){
    log(msg,3);
}

void Log::log(const str& msg,u8 lvl){
    vec<str> mods = {
            "\033[37m I: " RES,
            "\033[32m D: " RES,
            "\033[33m W: " RES,
            "\033[31m E: " RES
    };
    std::cout << mods[lvl] << msg << std::endl;
}
