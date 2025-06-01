#pragma once
#include <string>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>

class Wallet {
public:
    Wallet();
    ~Wallet();

    std::string getPublicKey() const;
    std::string getAddress() const;
    std::string sign(const std::string& message) const;
    static bool verifySignature(const std::string& message, const std::string& signature, const std::string& pubKeyHex);

private:
    EC_KEY* key;
};
