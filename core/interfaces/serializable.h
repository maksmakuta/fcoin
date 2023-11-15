#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "../constants.h"

class serializable {
public:
    virtual vec<str> serialize() = 0;
    virtual void deserialize(const vec<str> &input) = 0;
    virtual ~serializable() = default;
};

#endif