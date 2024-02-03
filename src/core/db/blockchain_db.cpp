#include "blockchain_db.h"
#include "../crypto/merkle_tree.h"
#include "transaction_db.h"

void blockchain_db::init(){
    if(!isTableExist(BLOCK_TABLE)){
        std::stringstream ss;
        ss << "CREATE TABLE IF NOT EXISTS " << BLOCK_TABLE << " ("
           << " HASH VARCHAR(32),"
           << " PREV_HASH VARCHAR(32),"
           << " TIME INTEGER,"
           << " TZ_ROOT VARCHAR(32),"
           << " TZ_COUNT INTEGER"
           << ");";

        exec(ss.str(),null);
    }
}

void blockchain_db::clear(){
    str sql = str("DROP TABLE ") + BLOCK_TABLE + ";";
    exec(sql, nullptr);
}

void blockchain_db::put(const block &obj){
    std::stringstream sql;
    i32 c = (i32)obj.getTransactions().size();
    str root = merkle_tree::fast(obj.getTransactions());
    sql << "INSERT INTO " << BLOCK_TABLE << " ("
        << " HASH,PREV_HASH,TIME,TZ_ROOT,TZ_COUNT "
        << ") VALUES ( "
        << "'" << obj.getHash() << "' ,"
        << "'" << obj.getPrevHash() << "' ,"
        << obj.getTime() << " ,"
        << "'" << root << "' ,"
        << c << " );";
    if (isTransaction()) {
        pushTx(sql.str());
    } else {
        exec(sql.str(), nullptr);
    }
}

block blockchain_db::pull(const str &hash){
    bool err = false;
    block obj;
    std::stringstream sql;
    sql << "SELECT * FROM " << BLOCK_TABLE << " WHERE HASH = '" << hash << "';";

    transaction_db tzdb;
    tzdb.init();
    vec<str> txid = tzdb.txByBlock(hash);
    obj.setTransactions(txid);

    exec(sql.str(), [&obj, &err](int s, char **rows,char **cols){
        if (s == 5) {
            obj.setHash(rows[0]);
            obj.setPrevHash(rows[1]);
            obj.setTime(std::stoi(rows[2]));
            str root = rows[3];
            i32 count = std::stoi(rows[4]);
            if (obj.tz_count != count) {
                std::cerr << "wrong tz count\n";
                err = true;
            }
            if (obj.tz_root != root) {
                std::cerr << "wrong tz root\n";
                err = true;
            }
        } else {
            std::cerr << "Wrong amount of data\n";
        }
    });
    if(err)
        return {};
    else
        return obj;
}
