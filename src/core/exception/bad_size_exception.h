#ifndef FCOIN_BAD_SIZE_EXCEPTION_H
#define FCOIN_BAD_SIZE_EXCEPTION_H

#include <exception>

class bad_size_exception : public std::exception{
    [[nodiscard]] const char * what() const noexcept override;
};


#endif //FCOIN_BAD_SIZE_EXCEPTION_H
