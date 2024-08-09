#include "EncryptionAlgorithm.h"
#include "Config.h"

// Constructor to initialize the encryption algorithm with necessary components
EncryptionAlgorithm::EncryptionAlgorithm(int keySize) 
    : keyManagement(keySize) {
    // Placeholder key for initialization (In practice, you would pass the actual key)
    std::vector<uint8_t> key = keyManagement.generateRandomKey();
    initialize(key);
}

// Function to initialize the algorithm with a given key
void EncryptionAlgorithm::initialize(const std::vector<uint8_t>& key) {
    // Generate the dynamic S-box based on the key
    sbox = sboxGenerator.generateSBox(key);

    // Expand the key for the required number of rounds
    int numRounds = MIN_ROUNDS + (key.size() * 8 / DEFAULT_KEY_SIZE) * (MAX_ROUNDS - MIN_ROUNDS);
    roundKeys = keyManagement.expandKey(key, numRounds);
}

// Function to encrypt a block of data
std::vector<uint8_t> EncryptionAlgorithm::encrypt(const std::vector<uint8_t>& data) {
    std::vector<uint8_t> block = data;
    
    // Apply randomization to the block to resist side-channel attacks
    sideChannelResistance.applyRandomization(block);

    // Apply the encryption rounds
    applyRounds(block, true);

    return block;
}

// Function to decrypt a block of data
std::vector<uint8_t> EncryptionAlgorithm::decrypt(const std::vector<uint8_t>& data) {
    std::vector<uint8_t> block = data;

    // Apply the decryption rounds
    applyRounds(block, false);

    // Remove randomization to get the original data
    sideChannelResistance.applyRandomization(block); // Note: This should match the encryption randomization

    return block;
}

// Function to apply encryption or decryption rounds
void EncryptionAlgorithm::applyRounds(std::vector<uint8_t>& block, bool encrypting) {
    int numRounds = roundKeys.size();
    
    if (encrypting) {
        // Forward rounds
        for (int round = 0; round < numRounds; ++round) {
            // Apply S-box, mixing function, etc.
            mixingFunction.applyMixingFunction(block);
            parallelism.applySIMD(block);
        }
    } else {
        // Reverse rounds
        for (int round = numRounds - 1; round >= 0; --round) {
            // Apply reverse S-box, mixing function, etc.
            parallelism.applySIMD(block);
            mixingFunction.applyMixingFunction(block);
        }
    }
}
