🌍 SaveWorld P2P Blockchain

A decentralized, peer-to-peer blockchain written in C++. Built for transparency, sustainability, and real-world impact. It features a full blockchain core, digital wallet signatures, proof-of-work mining, peer-to-peer networking, and custom consensus mechanisms like Proof of Action (PoA) for climate-based or mission-driven validation.

Features

- 🔐 Secure Transactions
  - Digital signature verification using public/private key cryptography
  - RSA encryption for message integrity
  - Coinbase transactions and customizable rewards

- ⛏️ Consensus Algorithms
  - Proof of Work (PoW)
  - Proof of Action (PoA) — enforce rules like required transaction count or behavior-based validation

- 🔄 Blockchain Core
  - Genesis block creation
  - Hash-based block chaining
  - Real-time difficulty adjustment
  - SHA-256 hashing (pluggable)

- 🌐 P2P Network Layer
  - Boost.Asio TCP server/client for node communication
  - Automatic longest-chain synchronization
  - Dynamic peer messaging

- Modular and Extensible
  - Pluggable signature and hashing algorithms
  - Easily configurable transaction structures and block rules

🧠 How It Works

1. Nodes start and connect to peers via TCP.
2. Wallets create transactions signed with private keys.
3. Nodes mine new blocks using PoW and validate them using PoA rules.
4. All nodes sync to the longest valid chain upon receiving updates.

Dependencies

- C++17 or higher
- Boost.Asio (for networking)
- OpenSSL (for cryptographic functions)

Install on Ubuntu/Debian

bash
sudo apt update
sudo apt install libboost-all-dev libssl-dev
📦 Build Instructions
Compile and Run
bash
g++ main.cpp -o SaveWorldP2PBlockchain -lboost_system -lssl -lcrypto -lpthread
./SaveWorldP2PBlockchain
🧪 Example Console Output
[✔] Node started on port 8080
[⛏] Mining Genesis Block...
[🔗] Connected to peer: 127.0.0.1:8081
[✓] Received longer chain from peer, replacing local chain
📄 Example Transaction Format
json
{
  "from": "PublicKey_A",
  "to": "PublicKey_B",
  "amount": 25,
  "signature": "0xF9A3C...",
  "timestamp": 1720023902
}
📂 Project Structure

SaveWorldP2PBlockchain/
├── main.cpp            # Application entry point
├── blockchain.h        # Blockchain data structure and logic
├── transaction.h       # Transaction structure and signing
├── wallet.h            # Key generation and digital signatures
├── network.h           # Boost.Asio P2P communication
├── utils.h             # Hashing and helper utilities
└── README.md           # Documentation
🌱 Use Cases
* Government-backed climate action funding
* Community governance tokens
* Transparent and traceable donation or subsidy systems
* Public ledger for local climate projects
* Research or academic simulation of blockchain technology
🛠️ Roadmap

* [ ] Proof-of-Stake (PoS) integration
* [ ] TLS-secured peer messaging
* [ ] Persistent local blockchain storage (LevelDB)
* [ ] GUI blockchain explorer (React + WebSocket)
* [ ] Smart contract scripting engine
🤝 Contribution

We welcome developers, activists, and researchers to collaborate.
Fork this project, build new modules, or propose consensus changes for your use case!
📜 License
MIT License – Free to use, modify, and distribute with attribution.
🧑‍💻 Author
Rana Ammar Yasir
Blockchain Developer & Climate Tech Advocate
https://www.linkedin.com/in/rana-ammar-yasir/
🌐 
Powered by Purpose

> This blockchain is part of the **Save World Initiative**, focused on using secure decentralized technologies to combat climate change, promote global cooperation, and empower transparent governance at scale.
