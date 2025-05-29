// SaveWorldBlockchain.cpp
// Author: Rana Ammar Yasir
// Description: Simple blockchain implementation "Save World" with Proof of Work and Proof of Action

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <openssl/sha.h> // For SHA256 hashing
#include <iomanip>

using namespace std;

// Utility: SHA256 hash function
string sha256(const string &input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input.c_str(), input.size(), hash);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// Block structure
struct Block {
    int index;
    time_t timestamp;
    string data;
    string prevHash;
    string hash;
    int nonce;

    // Constructor
    Block(int idx, const string &data, const string &prevHash)
        : index(idx), data(data), prevHash(prevHash), nonce(0) {
        timestamp = time(nullptr);
        hash = calculateHash();
    }

    // Calculate block hash based on contents
    string calculateHash() const {
        stringstream ss;
        ss << index << timestamp << data << prevHash << nonce;
        return sha256(ss.str());
    }

    // Proof of Work: simple mining with difficulty target
    void mineBlock(int difficulty) {
        string target(difficulty, '0'); // e.g., difficulty=4 means hash must start with "0000"
        do {
            nonce++;
            hash = calculateHash();
        } while(hash.substr(0, difficulty) != target);

        cout << "Block mined: " << hash << endl;
    }
};

// Blockchain class
class Blockchain {
private:
    vector<Block> chain;
    int difficulty;

public:
    Blockchain(int difficulty = 4) {
        this->difficulty = difficulty;
        // Create genesis block
        chain.push_back(createGenesisBlock());
    }

    Block createGenesisBlock() {
        return Block(0, "Genesis Block - Save World", "0");
    }

    Block getLatestBlock() const {
        return chain.back();
    }

    void addBlock(const string &data) {
        Block newBlock(chain.size(), data, getLatestBlock().hash);
        cout << "Mining block " << newBlock.index << " with data: " << data << endl;

        // Proof of Work mining
        newBlock.mineBlock(difficulty);

        // Custom Proof of Action (example): action based on data length mod 10
        if (proofOfAction(data)) {
            chain.push_back(newBlock);
            cout << "Block added to chain!" << endl;
        } else {
            cout << "Proof of Action failed, block rejected." << endl;
        }
    }

    // Proof of Action example: a simple function that approves block if data length mod 10 < 5
    bool proofOfAction(const string &data) {
        int val = data.length() % 10;
        cout << "Proof of Action check: data length mod 10 = " << val << endl;
        return val < 5;
    }

    void printChain() const {
        cout << "------- Blockchain: Save World -------" << endl;
        for (const auto &block : chain) {
            cout << "Block #" << block.index << endl;
            cout << "Timestamp: " << ctime(&block.timestamp);
            cout << "Data: " << block.data << endl;
            cout << "PrevHash: " << block.prevHash << endl;
            cout << "Hash: " << block.hash << endl;
            cout << "Nonce: " << block.nonce << endl;
            cout << "---------------------------" << endl;
        }
    }
};

// Main function to demonstrate blockchain usage
int main() {
    cout << "Save World Blockchain by Rana Ammar Yasir\n" << endl;

    Blockchain saveWorldChain(4); // Difficulty 4

    saveWorldChain.addBlock("Plant 100 trees in the city park");
    saveWorldChain.addBlock("Recycle 50kg of plastic waste");
    saveWorldChain.addBlock("Organize community clean-up event");
    saveWorldChain.addBlock("This data is longer than 15 chars and will fail Proof of Action"); // Should fail PoA

    saveWorldChain.printChain();

    return 0;
}
