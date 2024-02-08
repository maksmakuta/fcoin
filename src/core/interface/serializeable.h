#ifndef FCOIN_SERIALIZEABLE_H
#define FCOIN_SERIALIZEABLE_H

#include "../bytebuff.h"

class serializeable{
public:
    virtual void deserialize(const bytebuff&) = 0;
    virtual bytebuff serialize() = 0;
};

#endif //FCOIN_SERIALIZEABLE_H
