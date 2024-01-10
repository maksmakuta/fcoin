#ifndef FCOIN_SECP256K1_H
#define FCOIN_SECP256K1_H

#include "../constants.h"
#include "BigInt.h"

class secp256k1 {
public:
    struct public_key{
        BigInt x,y;
    };

    struct public_key_short{
        BigInt x;
    };

    struct private_key{
        BigInt secret;
    };

    struct keypair{
        public_key pub;
        private_key priv;
    };

    struct keypair_short{
        BigInt pub;
        BigInt priv;
    };

    secp256k1() = default;

    static str sign(private_key &p,const str& data);
    static bool verify(public_key &p,const str& sign);

    class generator{
    public:
        generator() = default;

        static keypair gen();
        static keypair_short genComp();
    };

    class reader{
    public:
        reader() = default;

        static public_key readPub(const str&);
        static public_key_short readPubComp(const str&);
        static private_key readPriv(const str&);
        static keypair readKeyPair(const str&);
        static keypair_short readKeyPairComp(const str&);
    };

    class writer{
    public:
        writer() = default;

        static str writePub(const public_key&);
        static str writePubComp(const public_key_short&);
        static str writePriv(const private_key&);
        static str writeKeyPair(const keypair&);
        static str writeKeyPairComp(const keypair_short&);
    };

    class recovery{
        static public_key pub(private_key&);
        static public_key_short pubComp(private_key&);
    };
};


#endif //FCOIN_SECP256K1_H
