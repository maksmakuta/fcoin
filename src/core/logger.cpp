#include "logger.h"

char endl = '\n';

str head(u8 lvl){
    return vec<str>{
            "\033[37mI:\033[0m ",
            "\033[32mD:\033[0m ",
            "\033[33mW:\033[0m ",
            "\033[31mE:\033[0m "
    }[lvl];
}

Log::Log(const str& h){
    this->header = h;
}

Log Log::i = Log(head(0));
Log Log::d = Log(head(1));
Log Log::w = Log(head(2));
Log Log::e = Log(head(3));
