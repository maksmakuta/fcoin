#include "bad_size_exception.h"

const char *bad_size_exception::what() const noexcept {
    return "size must be 256 or 384 or 512";
}
