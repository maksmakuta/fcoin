#ifndef FCOIN_BLOCK_H
#define FCOIN_BLOCK_H

#include "../constants.h"
#include "../interface/serializable.h"

class block : public serializable {
private:
    hash256 hash { 0L };
    hash256 phash{ 0L };
    u64 time = 0L;
    vec<hash384> tx = {};

public:
    block() = default;
    block(const hash256& _hash,const hash256& _phash,u64 _time,const vec<hash384>& _tx);

    void deserialize(bytebuff &) override;
    bytebuff serialize() override;

    [[nodiscard]] hash256 getHash() const;
    [[nodiscard]] hash256 getPHash() const;
    [[nodiscard]] u64 getTime() const;
    [[nodiscard]] vec<hash384> getTx() const;

    bool operator == (const block& blk) const;

private:
    //can use serializer
    void setHash(const hash256& data);
    void setPHash(const hash256& data);
    void setTime(u64 data);
    void setTx(const vec<hash384>& data);

};


#endif //FCOIN_BLOCK_H
