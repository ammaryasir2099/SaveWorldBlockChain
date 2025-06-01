#include "wallet.h"
#include <openssl/ecdsa.h>
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>

// Helper
std::string toHex(const unsigned char* data, size_t len) {
    std::ostringstream oss;
    for (size_t i = 0; i < len; ++i)
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)data[i];
    return oss.str();
}

Wallet::Wallet() {
    key = EC_KEY_new_by_curve_name(NID_secp256k1);
    if (!key || !EC_KEY_generate_key(key))
        throw std::runtime_error("Wallet key generation failed");
}

Wallet::~Wallet() {
    if (key) EC_KEY_free(key);
}

std::string Wallet::getPublicKey() const {
    const EC_POINT* pubKey = EC_KEY_get0_public_key(key);
    EC_GROUP* group = EC_GROUP_new_by_curve_name(NID_secp256k1);

    unsigned char* buf = NULL;
    size_t len = EC_POINT_point2buf(group, pubKey, POINT_CONVERSION_UNCOMPRESSED, &buf, NULL);
    std::string hex = toHex(buf, len);
    OPENSSL_free(buf);
    EC_GROUP_free(group);
    return hex;
}

std::string Wallet::getAddress() const {
    std::string pubKey = getPublicKey();

    // SHA256
    unsigned char sha256[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)pubKey.c_str(), pubKey.size(), sha256);

    // RIPEMD160
    unsigned char ripemd160[RIPEMD160_DIGEST_LENGTH];
    RIPEMD160(sha256, SHA256_DIGEST_LENGTH, ripemd160);

    return toHex(ripemd160, RIPEMD160_DIGEST_LENGTH);
}

std::string Wallet::sign(const std::string& message) const {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)message.c_str(), message.length(), hash);

    ECDSA_SIG* sig = ECDSA_do_sign(hash, SHA256_DIGEST_LENGTH, key);
    if (!sig) throw std::runtime_error("Failed to sign message");

    const BIGNUM* r;
    const BIGNUM* s;
    ECDSA_SIG_get0(sig, &r, &s);

    std::ostringstream oss;
    oss << BN_bn2hex(r) << ":" << BN_bn2hex(s);
    ECDSA_SIG_free(sig);
    return oss.str();
}

bool Wallet::verifySignature(const std::string& message, const std::string& signature, const std::string& pubKeyHex) {
    size_t colon = signature.find(':');
    if (colon == std::string::npos) return false;

    std::string rHex = signature.substr(0, colon);
    std::string sHex = signature.substr(colon + 1);

    BIGNUM* r = NULL;
    BIGNUM* s = NULL;
    BN_hex2bn(&r, rHex.c_str());
    BN_hex2bn(&s, sHex.c_str());

    ECDSA_SIG* sig = ECDSA_SIG_new();
    ECDSA_SIG_set0(sig, r, s);

    // Build public key
    EC_GROUP* group = EC_GROUP_new_by_curve_name(NID_secp256k1);
    EC_POINT* pubKey = EC_POINT_new(group);
    EC_POINT_hex2point(group, pubKeyHex.c_str(), pubKey, NULL);
    EC_KEY* pubECKey = EC_KEY_new_by_curve_name(NID_secp256k1);
    EC_KEY_set_public_key(pubECKey, pubKey);

    // Hash message
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)message.c_str(), message.length(), hash);

    bool valid = ECDSA_do_verify(hash, SHA256_DIGEST_LENGTH, sig, pubECKey);

    ECDSA_SIG_free(sig);
    EC_POINT_free(pubKey);
    EC_GROUP_free(group);
    EC_KEY_free(pubECKey);

    return valid;
}
