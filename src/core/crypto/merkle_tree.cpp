#include "merkle_tree.h"
#include "sha/sha256.h"

void merkle_tree::update(const str& input){
    data.push_back(hash(input));
}

void merkle_tree::update(const vec<str>& input){
    for(const str& s : input){
        update(s);
    }
}

str merkle_tree::root(){
    if(data.empty())
        return "";
    while (data.size() > 1){
        vec<str> nodes;
        for(i32 i = 0; i < data.size(); i += 2){
            str dat;
            if(i + 1 < data.size()) {
                dat = data[i] + data[i + 1];
            }else{
                dat = data[i] + data[i];
            }
            nodes.push_back(hash(dat));
        }
        data = nodes;
    }
    return data[0];
}

str merkle_tree::hash(const str& input){
    return sha256::fast(input);
}