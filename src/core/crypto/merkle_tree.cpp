#include "merkle_tree.h"
#include "../logger.h"
#include "sha/sha384.h"
#include "sha/sha512.h"
#include "sha/sha256.h"
#include "../utils.h"

merkle_tree::merkle_tree(u32 _size){
    this->size = _size;
}

void merkle_tree::push(const vec<str>& data){
    for(const str& item : data){
        push(item);
    }
}

void merkle_tree::push(const str& data){
    items.push_back(data);
}

str merkle_tree::root(){
    calcRoot();
    return root_hash;
}

void merkle_tree::calcRoot(){
    if(items.empty()){
        //if no items to build merkle tree return zero hash
        for(i32 i = 0 ; i < size;i++){
            root_hash += '0';
        }
    }else {
        if (items.size() % 2 != 0) {
            items.push_back(items.back());
        }
        tree.insert(tree.end(), items.begin(), items.end());
        for (size_t levelSize = items.size(); levelSize > 1; levelSize = (levelSize + 1) / 2) {
            for (size_t i = 0; i < levelSize; i += 2) {
                std::string left = tree[tree.size() - levelSize + i];
                std::string right = tree[tree.size() - levelSize + i + 1];
                tree.push_back(hash(left + right));
            }
        }
        root_hash = tree.back();
    }
}

hash256 merkle_tree::fast256(const vec<str>& inputs){
    merkle_tree tree(256);
    tree.push(inputs);
    return to_hash256(tree.root());
}

hash384 merkle_tree::fast384(const vec<str>& inputs){
    merkle_tree tree(384);
    tree.push(inputs);
    return to_hash384(tree.root());
}

hash512 merkle_tree::fast512(const vec<str>& inputs){
    merkle_tree tree(512);
    tree.push(inputs);
    return to_hash512(tree.root());
}

hash256 merkle_tree::fastH256(const vec<hash256>& inputs){
    return fast256( mapTo<hash256,str>(inputs, [](const hash256& i){ return to_string(i); }) );
}

hash384 merkle_tree::fastH384(const vec<hash384>& inputs){
    return fast384( mapTo<hash384,str>(inputs, [](const hash384& i){ return to_string(i); }) );
}

hash512 merkle_tree::fastH512(const vec<hash512>& inputs){
    return fast512( mapTo<hash512,str>(inputs, [](const hash512& i){ return to_string(i); }) );
}

str merkle_tree::hash(const str &input) const {
    switch (this->size) {
        case 256:
            return sha256::fast(input);
        case 384:
            return sha384::fast(input);
        case 512:
            return sha512::fast(input);
        default:
            Log::i << "Unsupported size : " << this->size << endl;
            return "";
    }
}