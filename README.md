Save World Blockchain 🌍

A simple blockchain implementation in C++ called "Save World", created by Rana Ammar Yasir.  
It demonstrates fundamental blockchain concepts such as Proof of Work (PoW), hashing with OpenSSL's SHA256, and an experimental Proof of Action (PoA) mechanism for additional validation based on block data.

Features

- ✅ Written in modern C++
- 🔐 Uses OpenSSL's `SHA256` for cryptographic hashing
- ⛏️ Proof of Work mining with adjustable difficulty
- 🧪 Proof of Action (PoA): Adds an extra layer of block validation
- 🌱 Environment-themed sample transactions (e.g., tree planting, recycling)
- 📜 Clean and readable code with comments

  Build Instructions

  Requirements

 C++ compiler (g++, clang++, etc.)
 OpenSSL libraries (`libssl-dev` or equivalent)

 🧪 Compile & Run

  bash
g++ SaveWorldBlockchain.cpp -o SaveWorldBlockchain -lssl -lcrypto
./SaveWorldBlockchain
