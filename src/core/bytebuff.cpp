#include <iomanip>
#include "bytebuff.h"
#include "logger.h"

bytebuff::bytebuff(const str& hexData){
    load(hexData);
}
bytebuff::bytebuff(const vec<u8>& binData){
    load(binData);
}

void bytebuff::put(const hash256& hash){
    for(u64 v : hash){
        put<u64>(v);
    }
}

void bytebuff::put(const hash384& hash){
    for(u64 v : hash){
        put<u64>(v);
    }
}

void bytebuff::put(const hash512& hash){
    for(u64 v : hash){
        put<u64>(v);
    }
}

void bytebuff::put(const vec<hash256>& hashes){
    put<u32>(hashes.size());
    for(hash256 v : hashes){
        put(v);
    }
}

void bytebuff::put(const vec<hash384>& hashes){
    put<u32>(hashes.size());
    for(hash384 v : hashes){
        put(v);
    }
}

void bytebuff::put(const vec<hash512>& hashes){
    put<u32>(hashes.size());
    for(hash512 v : hashes){
        put(v);
    }
}

hash256   bytebuff::getH256(){
    hash256 value;
    if(pos + 32 <= data.size()){
        for(u8 a = 0;a < 4;a++){
            value[a] = get<u64>();
        }
    }else{
        Log::e() << "wrong cursor position " << pos << ".." << (pos + 32) << endl();
    }
    return value;
}

hash384   bytebuff::getH384(){
    hash384 value;
    if(pos + 48 <= data.size()){
        for(u8 a = 0;a < 6;a++){
            value[a] = get<u64>();
        }
    }else{
        Log::e() << "wrong cursor position " << pos << ".." << (pos + 48) << endl();
    }
    return value;
}

hash512   bytebuff::getH512(){
    hash512 value;
    if(pos + 64 <= data.size()){
        for(u8 a = 0;a < 8;a++){
            value[a] = get<u64>();
        }
    }else{
        Log::e() << "wrong cursor position " << pos << ".." << (pos + 64) << endl();
    }
    return value;
}

vec<hash256> bytebuff::getVH256(){
    vec<hash256> items;
    u32 size = get<u32>();
    for(u32 i = 0; i < size;i++){
        items.push_back(getH256());
    }
    return items;
}

vec<hash384> bytebuff::getVH384(){
    vec<hash384> items;
    u32 size = get<u32>();
    for(u32 i = 0; i < size;i++){
        items.push_back(getH384());
    }
    return items;
}

vec<hash512> bytebuff::getVH512(){
    vec<hash512> items;
    u32 size = get<u32>();
    for(u32 i = 0; i < size;i++){
        items.push_back(getH512());
    }
    return items;
}


vec<u8> bytebuff::subbuff(u64 _pos, u32 len = -1){
    if(len == -1){ //take all data to end
        if(_pos <= data.size()){
            return {data.begin() + _pos, data.end()};
        }else{
            Log::e() << "pos is out of indices" << endl();
            return {};
        }
    }else{
        if(_pos + len <= data.size()){
            return {data.begin() + _pos, data.begin() + _pos + len};
        }else{
            Log::e() << "pos is out of indices" << endl();
            return {};
        }
    }
}

void bytebuff::move(u64 p){
    pos = p;
}


u64 bytebuff::cursor() const{
    return pos;
}

void bytebuff::clear(){
    data.clear();
    move(0);
}

str bytebuff::string(){
    strss ss;
    ss << std::setfill('0');
    for(u8 b : data) {
        ss << std::hex << std::setw(2)  << static_cast<unsigned>(b);
    }
    return ss.str();
}

vec<u8> bytebuff::raw(){
    return data;
}

u64 bytebuff::len(){
    return data.size();
}

void bytebuff::load(const str& input){
    vec<u8> bytes;
    for (u32 i = 0; i < input.length(); i += 2) {
        str byteString = input.substr(i, 2);
        u8 byte = (u8) strtol(byteString.c_str(), nullptr, 16);
        bytes.push_back(byte);
    }
    load(bytes);
}

void bytebuff::load(const vec<u8>& input){
    data.clear();
    data.reserve(input.size());
    data.insert(data.begin(),input.begin(), input.end());
}