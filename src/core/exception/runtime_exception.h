#ifndef FCOIN_RUNTIME_EXCEPTION_H
#define FCOIN_RUNTIME_EXCEPTION_H

#include <exception>
#include "../constants.h"

class runtime_exception : public std::exception{
public:
    runtime_exception();
    explicit runtime_exception(const char*);
    explicit runtime_exception(const str&);
    const char* what() const noexcept override;
private:
    const char* msg;
};


#endif //FCOIN_RUNTIME_EXCEPTION_H
