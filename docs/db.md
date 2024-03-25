## DB

 This project uses LevelDB for storing data.  
 LevelDB provides C/C++ API for working with databases and its simple, fast and provide local access to database.

 Main objects for blockchain to store is:
 - block
 - transaction
 - transaction_input
 - transaction_output
 - utxo (unspent transaction output)

 Every object_db provide 3 operations with DB:
 - push (insert object into DB)
 - pop (read object from DB)
 - delete (delete object from DB)

 Update objects is necessary for blockchain applications

### How data is stored

 Every object can be found with hash, and data is stored in binary string format used bytebuff.h (like hex data in string)  
 Every object saved with own database to provide fast and secure storing  
 But for every type we append special prefix to key.
 
 | type               | prefix (char) | hash size (bits) |
 |--------------------|---------------|------------------|
 | block              | B             | 256              |
 | transaction        | T             | 512              |
 | transaction_input  | I             | 384              |
 | transaction_output | O             | 384              |
 | utxo               | U             | 384              |