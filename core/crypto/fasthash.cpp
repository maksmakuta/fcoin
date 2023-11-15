#include "fasthash.h"

/**
 *
 * fasthash (crypto)
 * 
 * 
 *
 *
 *
 */

#include <iomanip>
#include <iostream>

arr<u8,32U> fasthash::apply(const vec<u8>& input){
    arr<u8,8> ctx = {
        0x4F,0x2A,0x17,0xD8,0xC9,0x6B,0x5A,0x3E
    };
    arr<u8,32> data;
    for(int a = 0;a < 32;a++){
        u8 t = input[a % input.size()];
        for(int b = 0;b < 16;b++){
            t = ctx[(8 - b) % 8] ^ (t << (a % 3));
            t = ctx[b % 8] ^ (t >> (a % 7));
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<i32>(t) << " ";
        }
        ctx[a % 8] = t;
        std::cout << "\n";
        data[a] = t;
    }
    return data;
}