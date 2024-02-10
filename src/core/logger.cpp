#include "logger.h"

str head(u8 lvl){
    return vec<str>{
            "\033[37mI:\033[0m ",
            "\033[32mD:\033[0m ",
            "\033[33mW:\033[0m ",
            "\033[31mE:\033[0m "
    }[lvl];
}

Log Log::i() {
    Log l;
    l.header = head(0);
    l.newline = false;
    return l;
}

Log Log::d() {
    Log l;
    l.header = head(1);
    l.newline = false;
    return l;
}

Log Log::w() {
    Log l;
    l.header = head(2);
    l.newline = false;
    return l;
}

Log Log::e() {
    Log l;
    l.header = head(3);
    l.newline = false;
    return l;
}

char endl(){
    return '\n';
}

