#ifndef UTILS_H
#define UTILS_H

#include "constants.h"
#include <sstream>
#include <iomanip>

vec<u8> toBytes(const str& input);
str toHexStr(const vec<u8> &input);

template <u32 size> 
str toHexStr(const arr<u8,size>& input){
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setfill('0');
    for(int a = 0; a < input.size();a++){
        ss << std::setw(2) << static_cast<int>(static_cast<unsigned char>(input[a]));
    }
    return ss.str();
}

#endif