## P2P network
 
 P2P network - network with multiple nodes (computers or apps) in network that communicate with each other.   
 Every computer can run multiple 1way apps (eg.: miner and wallet, but can't run 2 miners at the same time) and only one multiway app
 FCoin has 2 types of nodes - 1-way and multiway.  

 FCoin has few types of nodes:
  - FULL        (multiway)
  - MINER       (1-way)        
  - EXPLORER    (1-way)
  - WALLET      (1-way)

### Details about nodes
#### Full Node

 - communicate with other Full nodes in network
   - receive blocks
   - receive transactions
   - receive queries
   - verify data
 - communicate with 1-way nodes
   - processing queries (EXPLORER)
   - verify 
     - blocks  (MINER)
     - transactions (MINER and WALLET)

#### Miner Node

  - generate new blocks using PoV consensus algorithm
  - receive new transactions from Full nodes and processing it

#### Wallet Node

 - generate wallets
 - send coins 
   - generate transactions
   - sign transaction
   - broadcast to network

#### Explorer Node

 - query info from Full node about:
   - blocks
   - transactions
   - wallets
   - miner info

### Packets

 All packets consist of:

| name         | size (bytes) |
|--------------|--------------|
| command code | 1            |
| error code   | 1            |
| data         | any          |

 Response also contains command code to verify responses, because all data transferred in binary format.
 Check [commands.h](../src/core/commands.h) for more details