#ifndef FCOIN_DB_H
#define FCOIN_DB_H

#include "constants.h"
#include "interface/serializable.h"

#include <type_traits>
#include <leveldb/db.h>
#include <optional>
#include <typeinfo>

template<class T>
class db {
public:
    db() = default;
    explicit db(const str& dir){
        if(!std::is_base_of<serializable,T>::value){
            Log::e << "Type " << typeid(T).name() << " must implement serializable interface" << endl;
        }
        this->options.create_if_missing = true;
        auto status = leveldb::DB::Open(options,dir,&this->_db);
        if(!status.ok()){
            Log::e << status.ToString() << endl;
        }
    }
    ~db(){
        delete _db;
    }

    void push(const str& id,const T& item) const{
        if(std::is_base_of<serializable,T>::value){
            auto status = _db->Put(leveldb::WriteOptions{},id,item.serialize().string());
            if(!status.ok()){
                Log::e << status.ToString() << endl;
            }
        }else{
            Log::e << "Type " << typeid(T).name() << " must implement serializable interface" << endl;
        }
    }

    std::optional<T> pull(const str& id) const{
        std::optional<T> item;
        if(std::is_base_of<serializable,T>::value){
            str temp;
            auto status = _db->Get(leveldb::ReadOptions{},id,&temp);
            if(!status.ok()){
                Log::e << status.ToString() << id << endl;
                item.reset();
            }else {
                T object;
                bytebuff b(temp);
                object.deserialize(b);
                item = object;
            }
        }else{
            Log::e << "Type " << typeid(T).name() <<  " must implement serializable interface" << endl;
            item.reset();
        }
        return item;
    }

    void remove(const str& id) const{
        if(std::is_base_of<serializable,T>::value){
            auto status = _db->Delete(leveldb::WriteOptions{},id);
            if(!status.ok()){
                Log::e << status.ToString() << endl;
            }
        }else{
            Log::e << "Type " << typeid(T).name() << " must implement serializable interface" << endl;
        }
    }

    [[nodiscard]] bool exist(const str& id) const{
        return pull(id) != null;
    }

    db(const db<T>&) = delete;
private:
    leveldb::Options options;
    leveldb::DB* _db {};
};

#endif //FCOIN_DB_H
