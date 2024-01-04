#include <iostream>
#include "crypto/merkle_tree.h"
#include "block.h"
#include "crypto/sha256.h"
#include "blockchain.h"
#include "crypto/ripemd160.h"

//block newBlock(str last,vec<str> tz){
//    u64 t = time(null);
//    str hash = block::new_hash(last, t,tz);
//    return block(hash,last,t,tz);
//}

int main(int argc, char** argv){
    //blockchain chain;
    //chain.add(newBlock("0",vec<str>()));
    //for(i32 i = 0; i < 2048/64;i++){
    //    printf("last = %s\n",chain.last().getHash().c_str());
    //    chain.add(newBlock(chain.last().getHash(),vec<str>()));
    //}
    //printf("last = %s\n",chain.last().getHash().c_str());
    //bool ver = chain.verify();
    //if(ver){
    //    printf("chain is GOOD");
    //}else{
    //    printf("chain is BAD");
    //}

    str t = "hello";
    ripemd160 h;
    h.update(t);
    str o = h.digest();
    printf("h(t) = %s\n",o.c_str());
    str out = "108f07b8382412612c048d07d13f814118445acd";
    printf("assert = %i",o == out);
    return 0;
}
