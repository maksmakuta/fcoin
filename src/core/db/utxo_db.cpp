#include "utxo_db.h"

void utxo_db::init(){
    if(!isTableExist(UTXO_TABLE)){
        std::stringstream ss;
        ss << "CREATE TABLE IF NOT EXISTS " << UTXO_TABLE << " ("
           << " HASH VARCHAR(32),"
           << " SENDER VARCHAR(48),"
           << " RECEIVER VARCHAR(48),"
           << " AMOUNT INTEGER,"
           << " TXID VARCHAR(32)"
           << ");";

        exec(ss.str(),null);
    }
}

void utxo_db::clear(){
    str sql = str("DROP TABLE ") + UTXO_TABLE + ";";
    exec(sql, nullptr);
}

void utxo_db::put(const transaction_output &obj){
    std::stringstream sql;
    sql << "INSERT INTO " << UTXO_TABLE << " ("
        << " HASH,SENDER,RECEIVER,AMOUNT,TXID "
        << ") VALUES ( "
        << "'" << obj.hash << "' ,"
        << "'" << obj.sender << "' ,"
        << "'" << obj.receiver << "' ,"
        << obj.amount << " ,"
        << "'" << obj.txid << "' );";
    if (isTransaction()) {
        pushTx(sql.str());
    } else {
        exec(sql.str(), nullptr);
    }
}

transaction_output utxo_db::pull(const str &hash){
    transaction_output obj;
    std::stringstream sql;
    sql << "SELECT * FROM " << UTXO_TABLE << " WHERE HASH = '" << hash << "';";

    exec(sql.str(), [&obj](int s, char** rows, char **cols){
        if(s == 5){
            obj.hash = rows[0];
            obj.sender = rows[1];
            obj.receiver = rows[2];
            obj.amount = std::stoi(rows[3]);
            obj.txid = rows[4];
        }else{
            std::cerr << "Wrong amount of data\n";
        }
    });
    return obj;
}
