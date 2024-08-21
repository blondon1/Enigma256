#include "EncryptionAlgorithm.h"
#include "Config.h"
#include <iostream>
#include <functional>

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

    parallelism.parallelizeRounds(block, roundKeys.size(), [this](std::vector<uint8_t>& block, int round) {
        this->mixingFunction.applyMixingFunction(block);
        this->parallelism.applySIMD(block);
        std::cout << "Round " << round << " result: ";
        for (auto byte : block) std::cout << std::hex << static_cast<int>(byte) << " ";
        std::cout << std::endl;
    });
    std::cout << "Completed encryption rounds. Data: ";
    for (auto byte : block) std::cout << std::hex << static_cast<int>(byte) << " ";
    std::cout << std::endl;

    return block;
}

std::vector<uint8_t> EncryptionAlgorithm::decrypt(const std::vector<uint8_t>& data) {
    std::cout << "Entering decrypt function..." << std::endl;
    std::vector<uint8_t> block = data;

    parallelism.parallelizeRounds(block, roundKeys.size(), [this](std::vector<uint8_t>& block, int round) {
        this->parallelism.applySIMD(block);
        this->mixingFunction.applyMixingFunction(block);
        std::cout << "Round " << round << " result: ";
        for (auto byte : block) std::cout << std::hex << static_cast<int>(byte) << " ";
        std::cout << std::endl;
    });

    std::cout << "Completed decryption rounds. Data: ";
    for (auto byte : block) std::cout << std::hex << static_cast<int>(byte) << " ";
    std::cout << std::endl;

    sideChannelResistance.removeRandomization(block);
    std::cout << "Removed randomization. Data: ";
    for (auto byte : block) std::cout << std::hex << static_cast<int>(byte) << " ";
    std::cout << std::endl;

    return block;
}
