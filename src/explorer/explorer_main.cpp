#include <iostream>
#include <sstream>
#include "crypto/merkle_tree.h"
#include "block.h"
#include "crypto/sha256.h"
#include "blockchain.h"
#include "crypto/ripemd160.h"
#include "DB.h"

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

    //str t = "hello";
    //ripemd160 h;
    //h.update(t);
    //str o = h.digest();
    //printf("h(t) = %s\n",o.c_str());
    //str out = "108f07b8382412612c048d07d13f814118445acd";
    //printf("assert = %i",o == out);

    //struct User{
    //    i32 id;
    //    str name;
    //};
    //vec<User> users = {
    //        {0,"Mike"},
    //        {1,"Nike"},
    //        {2,"Lola"},
    //        {3,"Alex"},
    //        {4,"Dan"},
    //        {5,"Nick"},
    //        {6,"Mitch"},
    //};
    //str table_init = "CREATE TABLE IF NOT EXISTS UserData (UserID INT PRIMARY KEY AUTOINCREMENT,UserName VARCHAR(255));";
    //DB d = DB("/tmp/lol.db");
    //d.run(table_init);
    //for(i32 i = 0; i < 16384;i++) {
    //    printf("i = %i\n",i);
    //    for (const User &u: users) {
    //        std::stringstream ss;
    //        ss << "INSERT INTO UserData (UserName) VALUES (\'" << u.name << "\');";
    //        //printf("EXEC : %s\n", ss.str().c_str());
    //        d.run(ss.str());
    //    }
    //}
    //d.close();
    return 0;
}
