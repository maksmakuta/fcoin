## transaction

Every transactions consist of:
- inputs
- outputs
- txid
- time
- block hash

TXID is a hash of all transaction that builds:

```c++
    auto inputs = to_string(inputs.size());
    auto outputs = to_string(outputs.size());
    auto input_root = merkle_tree::fast(hash of every input);
    auto output_root = merkle_tree::fast(hash of every output);
    return sha256::fast(inputs + input_root + time + output_root + outputs)
```

Every wallet have UTXO (unspend transactions outputs) list that used for creating new transactions.  
For example you have 5 UTXO:
- 0.3
- 0.1
- 0.15
- 0.9
- 1.5

And you want to send 0.2 coins to someone, but there is no UTXO that have 0.2 coins. So we sort UTXO's in increasing order and take first n UTXO's that bigger than 0.2
- 0.1 (take this)
- 0.15 (and this)
- 0.3
- 0.9
- 1.5

Now we create transaction with 2 inputs and 2 outputs  
inputs (total 0.25):
- 0.1
- 0.15  
  outputs (total 0.25);
- 0.2  (sends to someone else)
- 0.05 (your change)

That's all.

If you want to send 0.3 coins and you have UTXO with exactly same amount of coins, so we just send it without any calculations
