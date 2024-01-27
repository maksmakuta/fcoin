#include "transaction_input_db.h"

void transaction_input_db::clear(){
    str sql = str("DROP TABLE ") + INPUTS_TABLE + ";";
    exec(sql, nullptr);
}

void transaction_input_db::init(){
    if(!isTableExist(INPUTS_TABLE)){
        std::stringstream ss;
        ss << "CREATE TABLE IF NOT EXISTS " << INPUTS_TABLE << " (";
        ss << " HASH VARCHAR(32),";
        ss << " OUTPUT VARCHAR(32),";
        ss << " SIGN VARCHAR(32),";
        ss << " TXID VARCHAR(32)";
        ss << ");";

        exec(ss.str(),null);
    }
}

void transaction_input_db::put(const transaction_input &obj){
    std::stringstream sql;
    sql << "INSERT INTO " << INPUTS_TABLE << " ("
        << " HASH,OUTPUT,SIGN,TXID "
        << ") VALUES ( "
        << "'" << obj.hash << "' ,"
        << "'" << obj.output_hash << "' ,"
        << "'" << obj.sign << "' ,"
        << "'" << obj.txid << "' );";
    if (isTransaction()) {
        pushTx(sql.str());
    } else {
        exec(sql.str(), nullptr);
    }
}

transaction_input transaction_input_db::pull(const str &hash){
    transaction_input obj;
    std::stringstream sql;
    sql << "SELECT * FROM " << INPUTS_TABLE << " WHERE HASH = '" << hash << "';";

    exec(sql.str(), [&obj](int s, char** rows, char **cols){
        if(s == 4){
            obj.hash = rows[0];
            obj.output_hash = rows[1];
            obj.sign = rows[2];
            obj.txid = rows[3];
        }else{
            std::cerr << "Wrong amount of data\n";
        }
    });
    return obj;
}

vec<str> transaction_input_db::inputsByTXID(const str& txid){
    vec<str> t;
    std::stringstream sql;
    sql << "SELECT HASH FROM " << INPUTS_TABLE << " WHERE TXID = '" << txid << "';";

    exec(sql.str(), [&t](int s, char** rows, char **cols){
        if(s == 1){
            t.emplace_back(rows[0]);
        }else{
            std::cerr << "Wrong amount of data\n";
        }
    });
    return t;
}