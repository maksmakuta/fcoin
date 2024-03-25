## Node

 Main app that connects to other nodes in network, sync from it, receive and verify new data.
 Also, he manages local copy of blockchain to serve as main server to other apps: miner, wallet, explorer.
 
### Help

    usage: node [--port] [--peer] [--peerlist]

    args:
    --port PORT                   specify port (DEFAULT: 8888)
    --peer ADDR:PORT              add peer to sync
    --peerlist /dir/to/peers.txt  add peers to sync

 Peerlist is a text file (.txt) that contains address and ip for other nodes to connect  
 For example (please, don't use this peerlist):
 
    192.168.0.1:8889
    192.168.0.1:8890
    192.168.0.1:8891
    192.168.0.1:8892
