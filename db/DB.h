#ifndef FCOIN_DB_H
#define FCOIN_DB_H

#include <sqlite3.h>
#include "../core/constants.h"

class DB{
public:
    explicit DB(const str& filename);

    sqlite3_stmt* run(const str& sql);

    void close();
private:
    str db_name;
    i32 op = SQLITE_OK;
    sqlite3* db = null;
};


#endif //FCOIN_DB_H
