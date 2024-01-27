#ifndef FCOIN_DB_H
#define FCOIN_DB_H

#include <sqlite3.h>
#include <iostream>
#include <functional>
#include <utility>
#include <filesystem>
#include "../constants.h"

namespace db_internal {
    std::function<void(int, char **, char **)> fn;

    int db_callback(void *, int s, char **rows, char **cols) {
        if (fn) {
            fn(s, rows, cols);
        }
        return SQLITE_OK;
    }
}

template<class T>
class db{
public:

    explicit db(const str& db_name){
        sqlite3_open(db_name.c_str(),&db_handle);
    }
    ~db(){
        sqlite3_close(db_handle);
    }

    virtual void init() = 0;
    virtual void put(const T& obj) = 0;
    virtual T pull(const str& hash) = 0;
    virtual void clear() = 0;

    void newTx(){
        tx_mode = true;
    }
    void pushTx(const str& input){
        txStream << input;
    }
    void commit(const std::function<void(int, char **, char **)> &callback = nullptr){
        tx_mode = false;
        exec(txStream.str(),callback);
        txStream.clear();
    }

    void exec(const str& sql,const std::function<void(int, char **, char **)> &callback){
    //    std::cout << "SQL = " << sql << "\n";
        db_internal::fn = callback;
        int op = sqlite3_exec(db_handle,sql.c_str(), db_internal::db_callback , nullptr, null);
        if(op != 0){
            std::cerr << "Error (" << op << "): " << sqlite3_errmsg(db_handle) << '\n';
        }
    }

    bool isTableExist(const str& table){
        bool res = false;
        auto sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='" + table + "';";
        exec(sql,[&res, &table](int s, char ** row, char **){
            res = (s == 1) && (table == row[0]);
        });
        return res;
    }

    bool isTransaction(){
        return tx_mode;
    }

private:
    sqlite3 *db_handle = nullptr;
    bool tx_mode = false;
    std::stringstream txStream;
};

#endif //FCOIN_DB_H
