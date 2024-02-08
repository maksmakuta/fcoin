#include "hex.h"

str hex::encode(u8 u){
    char s[3];
    sprintf(s,"%02x",u);
    return str({s[0],s[1]});
}

str hex::encode(const vec<u8>& v){
    strss ss;
    for(u8 u : v){
        ss << encode(u);
    }
    return ss.str();
}

u8 hex::decode(const str& byte){
    return (u8)stoul(byte,null,16);
}

vec<u8> hex::decodeVec(const str& bytes){
    vec<u8> data;
    for(u32 i = 0; i < bytes.size();i+=2){
        str t = {bytes[i], bytes[i + 1]};
        data.push_back(decode(t));
    }
    return data;
}
