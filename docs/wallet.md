## Wallet

 Wallet implement generating address from public key hash.   
 Algorithm to create address from public key:  
 - Receive public key
 - Take ripend160 hash from Y point (name is rh)
 - Take sha256 hash from rh (name it sh)
 - Concatenate rh and sh and take sha384 hash from it
 - Append 'fc' to the beginning of this hash
 
 Code : 

 ```C++
    str address(const pubkey& pk){
        auto y = pk.y;
        auto a = ripemd160::fast(y.to_string());
        auto b = sha256::fast(a);
        return "fc" + sha384::fast(a + b);
    }
 ```
