## PoV - Proof of Vote

 Consensus algorithm, that wants to achieve fast speed and more security
 
### How it works?

 Every miner send seed and public key to network.  
 Seed - cryptographically secured random number with type u64  
 Then when registration time is over sort all miners by seed  
 And for every round   
 Take hash sha256 from seed || public_key, and find voted miner by modulo n 64 bits where n - number of round  
 If we found 1 miner with the biggest amount of votes - that's winner
 
 Pseudocode:
 
 ```c++
     struct Miner{
      pubkey pub;
      u64 seed;
      u64 votes = 0;
     }
   
     vec<Miner> miners;
   
     ...
     // register new miner
     miners.push_back({pub_key,miner_seed,0});
     ...
    
     // voting algorithm
     u64 round = 0;
     vec<pubkey> players = miners.getPubKey();
     while(players.size > 1){
         for(miner m : miners){
             if(players.contains(m.pub)){
                 hash256 h = sha256(to_string(m.seed) + to_string(m.pub));
                 // round % 4 - used because hash256 is a array of u64 = array<u64,4>
                 miners.find(m).votes++;
             }
         }
         u64 points = 0;
         for(miner m : miners){
             if(m.votes == points){
                 players.push_back(m.pub);
             }else if(m.votes > points){
                 points = m.votes;
                 players.clear();
                 players.push_back(m.pub);
             }
         }
     }
 ```