#include "interfaces/hash.h"
#include "crypto/fasthash.h"
#include "constants.h"
#include "utils.h"
#include <iostream>

int main(int argc, char** argv){
    hash<256U> *fh = new fasthash();
    str text = "some text!!!";
    std::cout << "Text : " << text << std::endl;
    vec<u8> bytes = toBytes(text);
    std::cout << "Hash : " << toHexStr(bytes) << std::endl;
    str hash = toHexStr<32>(fh->apply(bytes));
    std::cout << "Hash : " << hash << std::endl;
    return 0;
}
