#ifndef FCOIN_DB_H
#define FCOIN_DB_H

#include <optional>
#include "../constants.h"
#include "sqlite_orm.h"

template<typename T>
class db {
public:

    db() = default;
    ~db() = default;

    virtual i32 push(const T&) = 0;
    virtual std::optional<T> pop(const str&) = 0;
    virtual void del(const str&) = 0;
    virtual void upd(const T&) = 0;
};


#endif //FCOIN_DB_H
