#ifndef FCOIN_MERKLE_TREE_H
#define FCOIN_MERKLE_TREE_H

#include "../constants.h"

class merkle_tree {
public:
    merkle_tree() = default;
    void update(const str& input);
    void update(const vec<str>& input);
    str root();

    static str fast(const vec<str>& input);
private:
    static str hash(const str& input);
    vec<str> data;
};


#endif //FCOIN_MERKLE_TREE_H
