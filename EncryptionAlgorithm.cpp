#include "EncryptionAlgorithm.h"
#include "Config.h"
#include <iostream>

EncryptionAlgorithm::EncryptionAlgorithm(int keySize) 
    : keyManagement(keySize) {
    std::vector<uint8_t> key = keyManagement.generateRandomKey();
    initialize(key);
}

void EncryptionAlgorithm::initialize(const std::vector<uint8_t>& key) {
    std::cout << "Initializing encryption algorithm with the provided key..." << std::endl;

    sbox = sboxGenerator.generateSBox(key);
    std::cout << "Dynamic S-box generated." << std::endl;

    int numRounds = MIN_ROUNDS + (key.size() * 8 / DEFAULT_KEY_SIZE) * (MAX_ROUNDS - MIN_ROUNDS);
    roundKeys = keyManagement.expandKey(key, numRounds);
    std::cout << "Key expanded for " << numRounds << " rounds." << std::endl;
}

std::vector<uint8_t> EncryptionAlgorithm::encrypt(const std::vector<uint8_t>& data) {
    std::cout << "Entering encrypt function..." << std::endl;
    std::vector<uint8_t> block = data;

    std::cout << "Original Data: ";
    for (auto byte : block) std::cout << std::hex << static_cast<int>(byte) << " ";
    std::cout << std::endl;

    sideChannelResistance.applyRandomization(block);
    std::cout << "Applied randomization. Data: ";
    for (auto byte : block) std::cout << std::hex << static_cast<int>(byte) << " ";
    std::cout << std::endl;

    applyRounds(block, true);
    std::cout << "Completed encryption rounds. Data: ";
    for (auto byte : block) std::cout << std::hex << static_cast<int>(byte) << " ";
    std::cout << std::endl;

    return block;
}

std::vector<uint8_t> EncryptionAlgorithm::decrypt(const std::vector<uint8_t>& data) {
    std::cout << "Entering decrypt function..." << std::endl;
    std::vector<uint8_t> block = data;

    applyRounds(block, false);
    std::cout << "Completed decryption rounds. Data: ";
    for (auto byte : block) std::cout << std::hex << static_cast<int>(byte) << " ";
    std::cout << std::endl;

    sideChannelResistance.applyRandomization(block);
    std::cout << "Removed randomization. Data: ";
    for (auto byte : block) std::cout << std::hex << static_cast<int>(byte) << " ";
    std::cout << std::endl;

    return block;
}

void EncryptionAlgorithm::applyRounds(std::vector<uint8_t>& block, bool encrypting) {
    std::cout << "Starting applyRounds..." << std::endl;
    int numRounds = roundKeys.size();

    if (encrypting) {
        for (int round = 0; round < numRounds; ++round) {
            std::cout << "Applying round " << round << " with key: ";
            for (auto byte : roundKeys[round]) {
                std::cout << std::hex << static_cast<int>(byte) << " ";
            }
            std::cout << std::endl;
            mixingFunction.applyMixingFunction(block);
            parallelism.applySIMD(block);
            std::cout << "Round " << round << " result: ";
            for (auto byte : block) std::cout << std::hex << static_cast<int>(byte) << " ";
            std::cout << std::endl;
        }
    } else {
        for (int round = numRounds - 1; round >= 0; --round) {
            std::cout << "Reversing round " << round << " with key: ";
            for (auto byte : roundKeys[round]) {
                std::cout << std::hex << static_cast<int>(byte) << " ";
            }
            std::cout << std::endl;
            parallelism.applySIMD(block);
            std::cout << "Completed SIMD for round " << round << std::endl;
            mixingFunction.applyMixingFunction(block);
            std::cout << "Completed Mixing Function for round " << round << std::endl;
            std::cout << "Round " << round << " result: ";
            for (auto byte : block) std::cout << std::hex << static_cast<int>(byte) << " ";
            std::cout << std::endl;
        }
    }

    std::cout << "Completed applyRounds." << std::endl;
}

