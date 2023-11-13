#ifndef KEYPAIR_H
#define KEYPAIR_H


#include <array>
#include <cstddef>
class KeyPair{
public:
    KeyPair();
    static KeyPair gen(int length);
};

#endif // KEYPAIR_H
