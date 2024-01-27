## DB
 This project uses SQLite for storing data.  
 SQLite provides C API for working with databases and its simple, fast and provide local access to database.

 Main objects for blockchain to store is:
 - block
 - transaction
 - transaction_input
 - transaction_output

 Every object_db provide 2 operations with DB:
 - push (insert object into DB)
 - pop (read object from DB)

 Update and delete objects is necessary for blockchain applications

### Define tables

    block(
        hash TEXT,
        phash TEXT,
        time TIMESTAMP,
        tz_root TEXT,
        tz_count INTEGER
    )

    transaction{
        txid TEXT,
        block TEXT, // link to block by hash
        time TIMESTAMP,
        inputs INTEGER, // count of transaction_input
        inputs_root TEXT,
        outputs INTEGER, // count of transaction_output
        outputs_root TEXT,    
    }

    transaction_input{
        hash TEXT,
        output TEXT // hash of output
        sign TEXT,
        txid TEXT
    }

    transaction_output{
        hash TEXT,
        sender TEXT,
        receiver TEXT,
        amount INTEGER,
        txid TEXT
    }