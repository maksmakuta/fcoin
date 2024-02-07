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

void Log::i(const strss& msg){
    Log::i(msg.str());
}

void Log::d(const strss& msg){
    Log::d(msg.str());
}

void Log::w(const strss& msg){
    Log::w(msg.str());
}

void Log::e(const strss& msg){
    Log::e(msg.str());
}

void Log::log(const str& msg,u8 lvl){
    vec<str> mods = {
            "\033[37mI: " RES,
            "\033[32mD: " RES,
            "\033[33mW: " RES,
            "\033[31mE: " RES
    };
    std::cout << mods[lvl] << msg << std::endl;
}
