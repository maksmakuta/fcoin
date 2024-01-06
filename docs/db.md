## DB
 This project uses SQLite for storing data  
 Main objects to store is:

 - block
 - transaction
 - transaction_input
 - transaction_output

### Define classes

    block(
        height INTEGER,
        hash TEXT,
        prev_hash TEXT,
        merkle_root TEXT,
        time TIMESTAMP,
        transactions INTEGER
    )

    transaction{
        txid TEXT,
        block TEXT, // link to block by hash
        time TIMESTAMP,
        inputs INTEGER, // count of transaction_input
        outputs INTEGER, // count of transaction_output
    }

    transaction_input{
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