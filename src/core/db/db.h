#ifndef FCOIN_DB_H
#define FCOIN_DB_H

#include <sqlite3.h>
#include <iostream>
#include <functional>
#include <utility>
#include <filesystem>
#include "../constants.h"

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

    void exec(const str& sql,const std::function<void(int, char **, char **)> &f){
        this->fn = f;
        int op = sqlite3_exec(
                db_handle,
                sql.c_str(),
                [](void* data,int argc, char **argv, char **argvCol){
                    static_cast<db*>(data)->fn(argc,argv,argvCol);
                    return 0;
                },
                this,
                null);
        if(op != 0){
            std::cerr << "Error (" << op << "): " << sqlite3_errmsg(db_handle) << '\n';
        }
        this->fn = null;
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
    std::function<void(int, char **, char **)> fn = null;
};

#endif //FCOIN_DB_H
