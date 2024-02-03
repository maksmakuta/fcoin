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

vec<byte> toBytes(const str& hex){
    std::vector<byte> bytes;
    for (u32 i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        byte b = (char) strtol(byteString.c_str(), nullptr, 16);
        bytes.push_back(b);
    }
    return bytes;
}