#include "utils.h"
#include "constants.h"
#include <complex>

vec<u8> toBytes(const str &input){
    return vec<u8>(input.begin(),input.end());
}

str toHexStr(const vec<u8> &input){
    std::stringstream ss;
    ss << std::hex << std::uppercase << std::setfill('0');
    for(int a = 0; a < input.size();a++){
        ss << std::setw(2) << static_cast<int>(static_cast<unsigned char>(input[a]));
    }
    return ss.str();
}

