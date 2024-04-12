#include <chrono>
#include "utils.h"

#define U64_LEN (sizeof(u64) * 2)

template<u64 size>
str to_string(const arr<u64,size>& data){
    strss ss;
    for(u64 i = 0;i < size;i++) {
        ss << std::setfill('0') << std::setw(U64_LEN) << std::hex << data[i];
    }
    return ss.str();
}

template<u64 size>
arr<u64,size> to_arr(const str& in){
    arr<u64,size> out;
    strss ss;
    u64 t;
    for(u64 u = 0; u < size;u++){
        ss << std::hex <<  in.substr(U64_LEN*u,U64_LEN);
        ss >> t;
        ss.clear();
        out[u] = t;
    }
    return out;
}

u64 timestamp(){
    const auto p1 = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
}

str to_string(const hash256& hash){
    return to_string<4>(hash);
}

str to_string(const hash384& hash){
    return to_string<6>(hash);
}

str to_string(const hash512& hash){
    return to_string<8>(hash);
}

hash256 to_hash256(const str& hex){
    return to_arr<4>(hex);
}

hash384 to_hash384(const str& hex){
    return to_arr<6>(hex);
}

hash512 to_hash512(const str& hex){
    return to_arr<8>(hex);
}

std::ostream& operator << (std::ostream& cout, const hash256& hash){
    cout << to_string(hash);
    return cout;
}

std::ostream& operator << (std::ostream& cout, const hash384& hash){
    cout << to_string(hash);
    return cout;
}

std::ostream& operator << (std::ostream& cout, const hash512& hash){
    cout << to_string(hash);
    return cout;
}