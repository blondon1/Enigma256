#include "KeyManagement.h"
#include "Config.h"
#include <random>

// Constructor to initialize key management with a given key size
KeyManagement::KeyManagement(int keySize) : keySize(keySize) {}

// Function to generate a random key
std::vector<uint8_t> KeyManagement::generateRandomKey() {
    std::vector<uint8_t> key(keySize / 8);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> dis(0, 255);

    for (auto& byte : key) {
        byte = dis(gen);
    }

    return key;
}

// Function to expand the key for all encryption rounds
std::vector<std::vector<uint8_t>> KeyManagement::expandKey(const std::vector<uint8_t>& key, int numRounds) {
    std::vector<std::vector<uint8_t>> roundKeys(numRounds, std::vector<uint8_t>(keySize / 8));

    // Basic example: repeat the original key for each round
    // (This is where you could implement a more complex key expansion algorithm)
    for (int i = 0; i < numRounds; ++i) {
        roundKeys[i] = key;
    }

    return roundKeys;
}
