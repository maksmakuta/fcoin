## DB
 This project uses SQLite for storing data  
 Main objects for blockchain to store is:

 - block
 - transaction
 - transaction_input
 - transaction_output

### Define classes

    block(
        id INTEGER [PRIMARY KEY],
        hash TEXT,
        prev_hash TEXT,
        merkle_root TEXT,
        time TIMESTAMP,
        transactions INTEGER
    )

    transaction{
        id INTEGER [PRIMARY KEY], 
        txid TEXT,
        block TEXT, // link to block by hash
        time TIMESTAMP,
        inputs INTEGER, // count of transaction_input
        outputs INTEGER, // count of transaction_output
    }

    transaction_input{
        id INTEGER [PRIMARY KEY], 
        output TEXT // hash of output
        sign TEXT,
        txid TEXT
    }

    transaction_output{
        id INTEGER [PRIMARY KEY], 
        hash TEXT,
        sender TEXT,
        receiver TEXT,
        amount INTEGER,
        txid TEXT
    }