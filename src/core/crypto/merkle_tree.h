#ifndef FCOIN_MERKLE_TREE_H
#define FCOIN_MERKLE_TREE_H

#include "../constants.h"

class merkle_tree{
public:

    merkle_tree() = default;
    explicit merkle_tree(u32 _size);

    void push(const vec<str>& data);
    void push(const str& data);

    str root();

    static hash256 fast256(const vec<str>& inputs);
    static hash384 fast384(const vec<str>& inputs);
    static hash512 fast512(const vec<str>& inputs);

    static hash256 fastH256(const vec<hash256>& inputs);
    static hash384 fastH384(const vec<hash384>& inputs);
    static hash512 fastH512(const vec<hash512>& inputs);

private:
    u32 size = 256;
    vec<str> items;
    vec<str> tree;
    str root_hash ;

    [[nodiscard]] str hash(const str& input) const;
    void calcRoot();
};

#endif //FCOIN_MERKLE_TREE_H
