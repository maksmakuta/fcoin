#ifndef DB_H
#define DB_H

#include <string>
#include <vector>
#include "constants.h"

template<typename T>
class DB{
public:
    DB(const str& fname);
    void exec(str cmd);
    void close();
    ~DB();
    
    virtual vec<T> load(str& cmd);
    virtual void push(vec<T> items);

private:

    bool isDBExist();
    bool hasTables(str name);

};

#endif