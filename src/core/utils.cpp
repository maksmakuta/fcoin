#include "utils.h"

bool startsWith(const str& input, const str& prefix) {
    if (input.length() < prefix.length()) {
        return false;
    }
    return input.compare(0, prefix.length(), prefix) == 0;
}