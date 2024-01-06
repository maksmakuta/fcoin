#include <iostream>
#include "constants.h"
#include "blockchain.h"

void blockchain::add(const block &blk){
    if(data.empty()){
        data.push_back(blk);
    }else{
        if(blk.verify() && last().getHash() == blk.getPrevHash()){
            data.push_back(blk);
        }else{
            std::cerr << errors::block_bad << std::endl;
        }
    }
}
std::optional<block> blockchain::getBlock(const str &blk) const{
    std::optional<block> res;
    if(!data.empty()){
        for(const block& b : data){
            if(b.getHash() == blk)
                res = b;
        }
    }
    return res;
}
bool blockchain::verify() const{
    if(data.empty()){
        return true;
    } else{
        for(i32 i = 0; i < data.size();i++){
            if(i + 1 < data.size()) {
                block blk = data[i];
                if (blk.verify()) {
                    if (blk.getHash() != data[i + 1].getPrevHash()) {
                        std::cerr << "Bad hash : " << i << "\n";
                        return false;
                    }
                } else {
                    std::cerr << "Bad block\n";
                    return false;
                }
            }
        }
        return true;
    }
}

block blockchain::last() const{
    return data[data.size() - 1];
}
