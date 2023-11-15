#ifndef BASE_H
#define BASE_H

#include "../constants.h"

class base{
public:

    virtual str encode(const str& input) = 0;
    virtual str decode(const str& input) = 0;    

};

#endif