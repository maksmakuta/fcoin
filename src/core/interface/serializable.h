#ifndef FCOIN_SERIALIZABLE_H
#define FCOIN_SERIALIZABLE_H

#include "../bytebuff.h"

class serializable{
public:
    virtual void deserialize(bytebuff&) = 0;
    virtual bytebuff serialize() = 0;
};

#endif //FCOIN_SERIALIZABLE_H
