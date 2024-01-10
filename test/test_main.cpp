#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "../src/core/crypto/sha256.h"
#include "../src/core/crypto/ripemd160.h"
#include "../src/core/crypto/BigInt.h"

str hash(const str& input){
    sha256 h;
    h.update(input);
    return h.digest();
}

str rhash(const str& input){
    ripemd160 h;
    h.update(input);
    return h.digest();
}

TEST_CASE("hashing text with sha256"){
    CHECK_EQ(hash("hello"),"2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824");
    CHECK_EQ(hash(""),"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
    CHECK_EQ(hash("-"),"3973e022e93220f9212c18d0d0c543ae7c309e46640da93a4a0314de999f5112");
    CHECK_EQ(hash(hash("")),"cd372fb85148700fa88095e3492d3f9f5beb43e555e5ff26d95f5a6adc36f8e6");
}

TEST_CASE("hashing text with ripemd160"){
    CHECK_EQ(rhash("hello"),"108f07b8382412612c048d07d13f814118445acd");
    CHECK_EQ(rhash(""),"9c1185a5c5e9fc54612808977ee8f548b2258d31");
    CHECK_EQ(rhash("-"),"4c3b58aa82048b1db748e6b816165c87c551e013");
    CHECK_EQ(rhash(rhash("")),"669a1d32371a8f2a7849025ca0d73dc8c89a6cf8");
}

TEST_CASE("BigInt operators"){
    auto a = BigInt(32);
    auto b = BigInt("32");
    CHECK_EQ(a.to_string(),"32");
    CHECK_EQ(b.to_string(),"32");
    CHECK_EQ(pow(BigInt(2),5),"32");
    a = BigInt(-2);
    CHECK_EQ(a.to_string(),"-2");
    auto h = BigInt::fromHex("AA0");
    CHECK_EQ(h.to_string(),"2720");
    auto base2 = BigInt::fromBin("0100110");
    CHECK_EQ(h.to_string(),"38");
}
