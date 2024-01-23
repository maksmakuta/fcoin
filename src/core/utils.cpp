#include <functional>
#include <chrono>
#include "utils.h"

bool startsWith(const str& input, const str& prefix) {
    if (input.length() < prefix.length()) {
        return false;
    }
    return input.compare(0, prefix.length(), prefix) == 0;
}

u64 timestamp(){
    const auto p1 = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
}
