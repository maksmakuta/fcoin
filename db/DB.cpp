#include "DB.h"

DB::DB(const str& filename){
    this->db_name = filename;
    op = sqlite3_open(this->db_name.c_str(),&db);
}

sqlite3_stmt* DB::run(const str& sql){
    if(db) {
        char *err = null;
        op = sqlite3_exec(db, sql.c_str(), null, null, &err);
        if (op != SQLITE_OK) {
            printf("ERROR : %s\n", err);
        }
    }else{
        printf("ERROR : db is not init yet\n");
    }
    return null;
}

void DB::close(){
    if(db != null){
        sqlite3_close(db);
    }
}