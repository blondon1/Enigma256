#ifndef KEY_MANAGEMENT_H
#define KEY_MANAGEMENT_H

#include <vector>
#include <cstdint>

// Key Management for Enigma256

class KeyManagement {
public:
    // Constructor to initialize key management with a given key size
    KeyManagement(int keySize);

    // Function to generate a random key
    std::vector<uint8_t> generateRandomKey();

    // Function to expand the key for all encryption rounds
    std::vector<std::vector<uint8_t>> expandKey(const std::vector<uint8_t>& key, int numRounds);

private:
    int keySize; // Size of the key in bits
};

#endif // KEY_MANAGEMENT_H
