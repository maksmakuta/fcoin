#ifndef DB_H
#define DB_H

#include <string>
#include <vector>

template<typename T>
class DB{
public:
    DB(const std::string& fname);
    void close();
    ~DB();
    
    virtual std::vector<T> load(std::string& cmd);
};

#endif