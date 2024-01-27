#include <sstream>
#include "transaction_output_db.h"

transaction_output_db::transaction_output_db()  : db(OUTPUTS_DB) {}

transaction_output_db::~transaction_output_db() = default;

void transaction_output_db::init(){
    if(!isTableExist(OUTPUTS_TABLE)){
        std::stringstream ss;
        ss << "CREATE TABLE IF NOT EXISTS " << OUTPUTS_TABLE << " (";
        ss << " HASH VARCHAR(32),";
        ss << " SENDER VARCHAR(48),";
        ss << " RECEIVER VARCHAR(48),";
        ss << " AMOUNT INTEGER,";
        ss << " TXID VARCHAR(32)";
        ss << ");";

        exec(ss.str(),null);
    }
}

void transaction_output_db::clear(){
    str sql = str("DROP TABLE ") + OUTPUTS_TABLE + ";";
    exec(sql, nullptr);
}

void transaction_output_db::put(const transaction_output &obj) {
    std::stringstream sql;
    sql << "INSERT INTO " << OUTPUTS_TABLE << " ("
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

transaction_output transaction_output_db::pull(const str &hash){
    transaction_output obj;
    std::stringstream sql;
    sql << "SELECT * FROM " << OUTPUTS_TABLE << " WHERE HASH = '" << hash << "';";

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

vec<str> transaction_output_db::outputsByTXID(const str& txid){
    vec<str> t;
    std::stringstream sql;
    sql << "SELECT HASH FROM " << OUTPUTS_TABLE << " WHERE TXID = '" << txid << "';";

    exec(sql.str(), [&t](int s, char** rows, char **cols){
        if(s == 1){
            t.emplace_back(rows[0]);
        }else{
            std::cerr << "Wrong amount of data\n";
        }
    });
    return t;
}

