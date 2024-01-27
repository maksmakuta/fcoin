#include "transaction_db.h"
#include "transaction_input_db.h"
#include "transaction_output_db.h"

void transaction_db::init() {
    if(!isTableExist(TZ_TABLE)){
        std::stringstream ss;
        ss << "CREATE TABLE IF NOT EXISTS " << TZ_TABLE << " (";
        ss << " TXID VARCHAR(32),";
        ss << " BLOCK VARCHAR(32),";
        ss << " TIME INTEGER,";
        ss << " INPUTS INTEGER";
        ss << " INPUTS_ROOT VARCHAR(32)";
        ss << " OUTPUTS INTEGER";
        ss << " OUTPUTS_ROOT VARCHAR(32)";
        ss << ");";

        exec(ss.str(),null);
    }
}

void transaction_db::clear() {
    str sql = str("DROP TABLE ") + TZ_TABLE + ";";
    exec(sql, nullptr);
}

void transaction_db::put(const transaction &obj) {
    std::stringstream sql;
    sql << "INSERT INTO " << TZ_TABLE << " ("
        << " TXID,BLOCK,TIME,INPUTS,INPUTS_ROOT,OUTPUTS,OUTPUTS_ROOT "
        << ") VALUES ( "
        << "'" << obj.getTXID() << "' ,"
        << "'" << obj.getBlock() << "' ,"
        << obj.getTime() << " ,"
        << obj.input_size << " ,"
        << "'" << obj.input_root << "' ,"
        << obj.output_size << " ,"
        << "'" << obj.output_root << "' );";

    if (isTransaction()) {
        pushTx(sql.str());
    } else {
        exec(sql.str(), nullptr);
    }
}

transaction transaction_db::pull(const str &hash) {
    bool err = false;
    transaction obj;
    std::stringstream sql;
    sql << "SELECT * FROM " << TZ_TABLE << " WHERE TXID = '" << hash << "';";

    transaction_input_db inputDb;
    inputDb.init();
    vec<str> input_hashes = inputDb.inputsByTXID(hash);
    obj.setInputs(input_hashes);

    transaction_output_db outputDb;
    outputDb.init();
    vec<str> output_hashes = outputDb.outputsByTXID(hash);
    obj.setOutputs(output_hashes);

    exec(sql.str(), [&obj, &err](int s, char **rows, char **cols) {
        if (s == 7) {
            obj.setTXID(rows[0]);
            obj.setBlock(rows[1]);
            obj.setTime(std::stol(rows[2]));
            int inputs = std::stoi(rows[3]);
            str inputs_root = rows[4];
            if (obj.input_root != inputs_root) {
                std::cerr << "input root is not same\n";
                err = true;
            }
            if (obj.input_size == inputs) {
                std::cerr << "inputs size is not same\n";
                err = true;
            }
            int outputs = std::stoi(rows[5]);
            str outputs_root = rows[6];
            if (obj.output_root != outputs_root) {
                std::cerr << "output root is not same\n";
                err = true;
            }
            if (obj.output_size == outputs) {
                std::cerr << "outputs size is not same\n";
                err = true;
            }
        } else {
            std::cerr << "Wrong amount of data\n";
        }

    });
    if (err) {
        return {};
    } else {
        return obj;
    }
}


vec<str> transaction_db::txByBlock(const str& block_hash){
    vec<str> t;
    std::stringstream sql;
    sql << "SELECT TXID FROM " << TZ_TABLE << " WHERE BLOCK = '" << block_hash << "';";

    exec(sql.str(), [&t](int s, char** rows, char **cols){
        if(s == 1){
            t.emplace_back(rows[0]);
        }else{
            std::cerr << "Wrong amount of data\n";
        }
    });
    return t;
}