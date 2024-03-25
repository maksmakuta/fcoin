#ifndef FCOIN_APP_H
#define FCOIN_APP_H

#include <map>
#include "constants.h"

class app{
private:
    std::map<str,vec<str>> args;
public:
    app(int,char**);
    ~app() = default;
    vec<str> get(const str&);
    bool exist(const str&);
private:
    static vec<str> split(const str& input, char delimeter);
};

#endif //FCOIN_APP_H
