#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_EXCEPTIONS
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS
#include <doctest/doctest.h>

#include "../src/core/crypto/sha/sha256.h"
#include "../src/core/crypto/sha/sha384.h"
#include "../src/core/crypto/sha/sha512.h"
#include "../src/core/crypto/ripemd160.h"
#include "../src/core/crypto/BigInt.h"
#include "../src/core/crypto/secp256k1.h"
#include "../src/core/wallet.h"
#include "../src/core/components/coins.h"
#include "../src/core/bytebuff.h"
#include "../src/core/components/block.h"
#include "../src/core/utils.h"

TEST_CASE("hashing text with sha256"){
    CHECK_EQ(sha256::fast("hello"),"2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824");
    CHECK_EQ(sha256::fast(""),"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
    CHECK_EQ(sha256::fast("-"),"3973e022e93220f9212c18d0d0c543ae7c309e46640da93a4a0314de999f5112");
    CHECK_EQ(sha256::fast(sha256::fast("")),"cd372fb85148700fa88095e3492d3f9f5beb43e555e5ff26d95f5a6adc36f8e6");
}

TEST_CASE("hashing text with sha384"){
    CHECK_EQ(sha384::fast("hello"),"59e1748777448c69de6b800d7a33bbfb9ff1b463e44354c3553bcdb9c666fa90125a3c79f90397bdf5f6a13de828684f");
    CHECK_EQ(sha384::fast(""),"38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b");
    CHECK_EQ(sha384::fast("-"),"d9c7e80d0b30f3cf8b70f6b90e51a306888cbe40070b6144fd67061558adfdf502653da4bd87671286448539cb2d016e");
    CHECK_EQ(sha384::fast(sha384::fast("")),"7e4a22bac84bf4653c27cf66fdbfc94b1f7aa38fda6777d60b2598ea5a353af6e6091bd1e1c789209548a4f1e16c0f55");
}

TEST_CASE("hashing text with sha512"){
    CHECK_EQ(sha512::fast("hello"),"9b71d224bd62f3785d96d46ad3ea3d73319bfbc2890caadae2dff72519673ca72323c3d99ba5c11d7c7acc6e14b8c5da0c4663475c2e5c3adef46f73bcdec043");
    CHECK_EQ(sha512::fast(""),"cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e");
    CHECK_EQ(sha512::fast("-"),"7c0b0d99a6e4c33cda0f6f63547f878f4dd9f486dfe5d0446ce004b1c0ff28f191ff86f5d5933d3614cceee6fbbdc17e658881d3a164dfa5d6f4c699b2126e3d");
    CHECK_EQ(sha512::fast(sha512::fast("")),"8fb29448faee18b656030e8f5a8b9e9a695900f36a3b7d7ebb0d9d51e06c8569d81a55e39b481cf50546d697e7bde1715aa6badede8ddc801c739777be77f166");
}

TEST_CASE("hashing text with ripemd160"){
    CHECK_EQ(ripemd160::fast("hello"),"108f07b8382412612c048d07d13f814118445acd");
    CHECK_EQ(ripemd160::fast(""),"9c1185a5c5e9fc54612808977ee8f548b2258d31");
    CHECK_EQ(ripemd160::fast("-"),"4c3b58aa82048b1db748e6b816165c87c551e013");
    CHECK_EQ(ripemd160::fast(ripemd160::fast("")),"669a1d32371a8f2a7849025ca0d73dc8c89a6cf8");
}

TEST_CASE("BigInt operators"){
    auto a = BigInt();
    auto b = BigInt(1);
    auto c = BigInt("2");
    auto d = BigInt::fromHex("ABC");
    auto e = BigInt::fromBin("011011001");

    CHECK_EQ(a.to_string(),"0");
    CHECK_EQ(b.to_string(),"1");
    CHECK_EQ(c.to_string(),"2");
    CHECK_EQ(d.to_string(),"2748");
    CHECK_EQ(e.to_string(),"217");

    CHECK_EQ(a.to_int(),0);
    CHECK_EQ(b.to_int(),1);
    CHECK_EQ(c.to_int(),2);
    CHECK_EQ(d.to_int(),2748);
    CHECK_EQ(e.to_int(),217);

    CHECK_EQ((a*b).to_int(),0);
    CHECK_EQ((a+c).to_int(),2);
    CHECK_EQ((d/e).to_int(),12);
    CHECK_EQ((d-c).to_int(),2746);

    CHECK_EQ(pow(c,10),1024);
    CHECK_EQ(sqrt(BigInt(16)),4);
    CHECK_EQ(abs(BigInt(-256)),256);
    CHECK_EQ(gcd(BigInt(1000),BigInt(725)),25);
    CHECK_EQ(lcm(BigInt(1000),BigInt(725)),29000);

    a = BigInt(-1);
    b = BigInt("-1");
    c = BigInt::fromHex("-A");
    d = BigInt::fromBin("-01110");

    CHECK_EQ(a.to_int(),-1);
    CHECK_EQ(b.to_int(),-1);
    CHECK_EQ(c.to_int(),-10);
    CHECK_EQ(d.to_int(),-14);

    auto t = BigInt("565656469497945163215465689");
    CHECK_EQ(t.to_hex(),"1D3E66AA7CF591D5448ECD9");


    auto x = BigInt::fromBase("156",8);
    CHECK_EQ(x.to_string(),"110");
}

TEST_CASE("secp256k1 serializing"){
    auto kp = secp256k1::generator::gen();

    str data = secp256k1::writer::writePub(kp.pub);
    auto pub = secp256k1::reader::readPub(data);
    CHECK_EQ(kp.pub.x, pub.x);
    CHECK_EQ(kp.pub.y, pub.y);

    auto pubc = secp256k1::public_key_short{ pub.x };
    data = secp256k1::writer::writePubComp(pubc);
    auto pubc_s = secp256k1::reader::readPubComp(data);
    CHECK_EQ(pubc.x, pubc_s.x);

    data = secp256k1::writer::writePriv(kp.priv);
    auto privc = secp256k1::reader::readPriv(data);
    CHECK_EQ(kp.priv.secret, privc.secret);

    auto kpc = secp256k1::keypair_short{kp.pub.x,kp.priv.secret};
    data = secp256k1::writer::writeKeyPairComp(kpc);
    auto kpc_s = secp256k1::reader::readKeyPairComp(data);
    CHECK_EQ(kpc.priv, kpc_s.priv);
    CHECK_EQ(kpc.pub , kpc_s.pub);

    data = secp256k1::writer::writeKeyPair(kp);
    auto kps = secp256k1::reader::readKeyPair(data);
    CHECK_EQ(kp.pub.x, kps.pub.x);
    CHECK_EQ(kp.pub.y, kps.pub.y);
    CHECK_EQ(kp.priv.secret, kps.priv.secret);

    data.clear();
}

TEST_CASE("secp256k1 singing and verifying"){
    str text = "Hello, World!";
    auto kp = secp256k1::generator::gen();
    auto sign = secp256k1::sign(kp.priv,text);
    auto s = secp256k1::verify(kp.pub,text,sign);
    CHECK_EQ(s,true);
}

transaction_output randTO(){
    srand(time(null));
    transaction_output t;
    t.hash      = sha256::fast(std::to_string(rand() % 16384));
    t.sender    = sha384::fast(std::to_string(rand() % (16384*16)));
    t.receiver  = sha384::fast(std::to_string(rand() % (16384*16)));
    t.amount    = rand() % 16000000;
    t.txid      = sha256::fast(t.sender + t.receiver);
    return t;
}


TEST_CASE("wallet things"){
    auto walletA = wallet::generate();
    auto walletB = wallet::generate();

    std::cout << "WalletA address = " << walletA.address() << "\n";
    std::cout << "WalletB address = " << walletB.address() << "\n";

    auto tz = walletA.send(walletB.address(),1);
    //TODO test
}

TEST_CASE("parse coins"){
    auto a = Coins(12.2650F);
    CHECK_EQ(a.enc(),122650);

    a = Coins(700UL);
    CHECK_EQ(a.enc(),700);

    a = Coins::MIN();
    CHECK_EQ(a.enc(),1);

    a = Coins::MAX();
    CHECK_EQ(a.enc(),10000000000000000000UL);
}

#define isEqualVec(a,b) \
    CHECK_EQ(a.size(),b.size()); \
    for(u32 i = 0;i < a.size();i++){ \
        CHECK_EQ(a[i],b[i]); \
    } \

TEST_CASE("bytebuff"){
    bytebuff buff;

    buff.put<u8 >(0x01);
    buff.put<u16>(0x0102);
    buff.put<u32>(0x01020304);
    buff.put<u64>(0x0101020304050607);
    buff.put<i8 >(0x0F);
    buff.put<i16>(0x10F1);
    buff.put<i32>(0x10F1F2F3);
    buff.put<i64>(0x10F1F2F3F4F5F6F7);

    u8  a = buff.get<u8 >();
    u16 b = buff.get<u16>();
    u32 c = buff.get<u32>();
    u64 d = buff.get<u64>();
    i8  e = buff.get<i8 >();
    i16 f = buff.get<i16>();
    i32 g = buff.get<i32>();
    i64 h = buff.get<i64>();

    CHECK_EQ(a,0x01);
    CHECK_EQ(b,0x0102);
    CHECK_EQ(c,0x01020304);
    CHECK_EQ(d,0x0101020304050607);
    CHECK_EQ(e,0x0F);
    CHECK_EQ(f,0x10F1);
    CHECK_EQ(g,0x10F1F2F3);
    CHECK_EQ(h,0x10F1F2F3F4F5F6F7);

    buff.clear();

    srand(time(null));

    u32 count = 1000;
    Log::i() << "count = " << count << endl();

    vec<u8 >  u8arr; u8arr .reserve(count);
    vec<u16> u16arr; u16arr.reserve(count);
    vec<u32> u32arr; u32arr.reserve(count);
    vec<u64> u64arr; u64arr.reserve(count);
    vec<i8 >  i8arr; i8arr .reserve(count);
    vec<i16> i16arr; i16arr.reserve(count);
    vec<i32> i32arr; i32arr.reserve(count);
    vec<i64> i64arr; i64arr.reserve(count);

    Log::i() << "generate vectors"<< endl();

    for(u32 i = 0; i < count;i++){
        u8arr .push_back((u8 )rand() % (sizeof(u8 )*8));
        u16arr.push_back((u16)rand() % (sizeof(u16)*8));
        u32arr.push_back((u32)rand() % (sizeof(u32)*8));
        u64arr.push_back((u64)rand() % (sizeof(u64)*8));
        i8arr .push_back((i8 )rand() % (sizeof(i8 )*8));
        i16arr.push_back((i16)rand() % (sizeof(i16)*8));
        i32arr.push_back((i32)rand() % (sizeof(i32)*8));
        i64arr.push_back((i64)rand() % (sizeof(i64)*8));
    }

    Log::i() << "insert random data"<< endl();

    buff.putVec<u8 >(u8arr );
    buff.putVec<u16>(u16arr);
    buff.putVec<u32>(u32arr);
    buff.putVec<u64>(u64arr);
    buff.putVec<i8 >(i8arr );
    buff.putVec<i16>(i16arr);
    buff.putVec<i32>(i32arr);
    buff.putVec<i64>(i64arr);

    Log::i() << "write into buffer"<< endl();

    str sBuff = buff.string();
    Log::i() << "buff = " << sBuff << endl();
    Log::i() << " len = " << sBuff.length() / 2 << endl();

    vec<u8 >  u8C = buff.getVec<u8 >();
    vec<u16> u16C = buff.getVec<u16>();
    vec<u32> u32C = buff.getVec<u32>();
    vec<u64> u64C = buff.getVec<u64>();
    vec<i8 >  i8C = buff.getVec<i8 >();
    vec<i16> i16C = buff.getVec<i16>();
    vec<i32> i32C = buff.getVec<i32>();
    vec<i64> i64C = buff.getVec<i64>();

    Log::i() << "read from buffer"<< endl();

    isEqualVec(u8arr ,u8C)
    isEqualVec(u16arr,u16C)
    isEqualVec(u32arr,u32C)
    isEqualVec(u64arr,u64C)
    isEqualVec(i8arr ,i8C)
    isEqualVec(i16arr,i16C)
    isEqualVec(i32arr,i32C)
    isEqualVec(i64arr,i64C)

    buff.clear();

    hash256 h1 = sha256::fastH("1");
    hash384 h2 = sha384::fastH("1");
    hash512 h3 = sha512::fastH("1");

    buff.put(h1);
    buff.put(h2);
    buff.put(h3);

    Log::i() << "len  = " << buff.len() << endl();
    Log::i() << "data = " << buff.string() << endl();

    hash256 h10 = buff.getH256();
    hash384 h20 = buff.getH384();
    hash512 h30 = buff.getH512();

    isEqualVec(h1,h10)
    isEqualVec(h2,h20)
    isEqualVec(h3,h30)

}

TEST_CASE("block de/serialization"){
    srand(time(null));
    vec<hash384> tx;
    for(u32 i = 0; i < rand() % 10;i++){
        tx.push_back(sha384::fastH((strss() << "transaction" << i).str()));
    }
    auto hash = sha256::fastH("block hash");
    auto phash = sha256::fastH("block previous hash");
    block blk(hash,phash,timestamp(),tx);
    bytebuff blockBuff = blk.serialize();

    //Log::i() << "len  = " << blockBuff.len() << endl();
    //Log::i() << "buff = " << blockBuff.string() << endl();

    block b;
    b.deserialize(blockBuff);
    CHECK_EQ(blk == b,true);
    //Log::i() << " ==? " << (blk == b ? "good" : "bad") << endl();
    //Log::i() << "hash   = " << to_string(b.getHash()) << endl();
    //Log::i() << "phash  = " << to_string(b.getPHash()) << endl();
    //Log::i() << "time   = " << b.getTime() << endl();
    //Log::i() << "tx len = " << b.getTx().size() << endl();

}
