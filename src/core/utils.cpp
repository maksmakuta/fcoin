#include <chrono>
#include "utils.h"

#define U64_LEN (sizeof(u64) * 2)

u64 timestamp(){
    const auto p1 = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
}

str to_string(const hash256& hash){
    strss ss;
    for(u64 v : hash) {
        ss << std::setfill('0') << std::setw(U64_LEN) << std::hex << v;
    }
    return ss.str();
}

str to_string(const hash384& hash){
    strss ss;
    for(u64 v : hash) {
        ss << std::setfill('0') << std::setw(U64_LEN) << std::hex << v;
    }
    return ss.str();
}

str to_string(const hash512& hash){
    strss ss;
    for(u64 v : hash) {
        ss << std::setfill('0') << std::setw(U64_LEN) << std::hex << v;
    }
    return ss.str();
}

hash256 to_hash256(const str& hex){
    hash256 hash;
    strss ss;
    u64 t;
    for(u8 u = 0; u < 4;u++){
        ss << std::hex <<  hex.substr(U64_LEN*u,U64_LEN);
        ss >> t;
        ss.clear();
        hash[u] = t;
    }
    return hash;
}

hash384 to_hash384(const str& hex){
    hash384 hash;
    strss ss;
    u64 t;
    for(u8 u = 0; u < 6;u++){
        ss << std::hex << hex.substr(U64_LEN*u,U64_LEN);
        ss >> t;
        ss.clear();
        hash[u] = t;
    }
    return hash;

}

hash512 to_hash512(const str& hex){
    hash512 hash;
    strss ss;
    u64 t;
    for(u8 u = 0; u < 8;u++){
        ss << std::hex << hex.substr(U64_LEN*u,U64_LEN);
        ss >> t;
        ss.clear();
        hash[u] = t;
    }
    return hash;

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

str to_time(){
    return "";
}