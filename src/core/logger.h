#ifndef FCOIN_LOGGER_H
#define FCOIN_LOGGER_H

#include <iostream>
#include "constants.h"

class Log{
public:
    static void i(const str& msg);
    static void d(const str& msg);
    static void w(const str& msg);
    static void e(const str& msg);

    static void i(const strss& msg);
    static void d(const strss& msg);
    static void w(const strss& msg);
    static void e(const strss& msg);
private:
    static void log(const str& msg,u8 lvl);
};

#endif //FCOIN_LOGGER_H
