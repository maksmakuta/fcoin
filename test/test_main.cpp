#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "../src/core/crypto/sha/sha256.h"
#include "../src/core/crypto/sha/sha384.h"
#include "../src/core/crypto/sha/sha512.h"
#include "../src/core/crypto/ripemd160.h"
#include "../src/core/crypto/BigInt.h"
#include "../src/core/crypto/secp256k1.h"
#include "../src/core/db/transaction_output_db.h"
#include "../src/core/wallet.h"
#include "../src/core/components/coins.h"
#include "../src/core/hex.h"
#include "../src/core/bytebuff.h"

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

TEST_CASE("db push and pop"){
    auto db = transaction_output_db();
    db.init();

    transaction_output a = randTO();
    transaction_output b = randTO();
    transaction_output c = randTO();
    transaction_output d = randTO();

    db.put(a);

    transaction_output ta = db.pull(a.hash);

    CHECK_EQ(a.hash    ,ta.hash    );
    CHECK_EQ(a.sender  ,ta.sender  );
    CHECK_EQ(a.receiver,ta.receiver);
    CHECK_EQ(a.amount  ,ta.amount  );
    CHECK_EQ(a.txid    ,ta.txid    );

    db.newTx();
    db.put(b);
    db.put(c);
    db.put(d);
    db.commit();

    auto ba = db.pull(b.hash);
    auto ca = db.pull(c.hash);
    auto da = db.pull(d.hash);

    CHECK_EQ(b.hash    ,ba.hash    );
    CHECK_EQ(b.sender  ,ba.sender  );
    CHECK_EQ(b.receiver,ba.receiver);
    CHECK_EQ(b.amount  ,ba.amount  );
    CHECK_EQ(b.txid    ,ba.txid    );

    CHECK_EQ(c.hash    ,ca.hash    );
    CHECK_EQ(c.sender  ,ca.sender  );
    CHECK_EQ(c.receiver,ca.receiver);
    CHECK_EQ(c.amount  ,ca.amount  );
    CHECK_EQ(c.txid    ,ca.txid    );

    CHECK_EQ(d.hash    ,da.hash    );
    CHECK_EQ(d.sender  ,da.sender  );
    CHECK_EQ(d.receiver,da.receiver);
    CHECK_EQ(d.amount  ,da.amount  );
    CHECK_EQ(d.txid    ,da.txid    );

    db.clear();
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

TEST_CASE("hex serialization"){
    u8 a = 0x99;
    str hexA = hex::encode(a);
    u8 b = hex::decode(hexA);
    CHECK_EQ(a,b);

    vec<u8> vecA = {0x01,0x02,0x04,0x08,0x10,0xFF};
    str vA = hex::encode(vecA);
    CHECK_EQ(vecA.size() * 2,vA.length());
    vec<u8> res = hex::decodeVec(vA);
    CHECK_EQ(vecA.size(),res.size());
    for(u32 i = 0;i < res.size();i++) {
        CHECK_EQ(vecA[i], res[i]);
    }
}

TEST_CASE("bytebuff tests"){
    bytebuff buff;

}
