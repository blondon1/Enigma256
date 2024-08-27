#include "EncryptionAlgorithm.h"
#include "Config.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

EncryptionAlgorithm::EncryptionAlgorithm(int keySize, EncryptionMode::Mode mode)
    : keyManagement(keySize), encryptionMode(mode, keyManagement.generateRandomKey()) {
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

    block = encryptionMode.encrypt(block, roundKeys);
    std::cout << "Completed encryption rounds. Data: ";
    for (auto byte : block) std::cout << std::hex << static_cast<int>(byte) << " ";
    std::cout << std::endl;

    return block;
}

std::vector<uint8_t> EncryptionAlgorithm::decrypt(const std::vector<uint8_t>& data) {
    std::cout << "Entering decrypt function..." << std::endl;
    std::vector<uint8_t> block = data;

    block = encryptionMode.decrypt(block, roundKeys);
    std::cout << "Completed decryption rounds. Data: ";
    for (auto byte : block) std::cout << std::hex << static_cast<int>(byte) << " ";
    std::cout << std::endl;

    sideChannelResistance.removeRandomization(block);
    std::cout << "Removed randomization. Data: ";
    for (auto byte : block) std::cout << std::hex << static_cast<int>(byte) << " ";
    std::cout << std::endl;

    return block;
}

void EncryptionAlgorithm::applyRounds(std::vector<uint8_t>& block, bool encrypting) {
    std::cout << "Starting applyRounds..." << std::endl;
    int numRounds = roundKeys.size();

    auto processRound = [&](int round, std::vector<uint8_t>& localBlock) {
        if (encrypting) {
            std::cout << "Applying round " << round << " with key: ";
        } else {
            std::cout << "Reversing round " << round << " with key: ";
        }

        for (auto byte : roundKeys[round]) {
            std::cout << std::hex << static_cast<int>(byte) << " ";
        }
        std::cout << std::endl;

        mixingFunction.applyMixingFunction(localBlock);
        parallelism.applySIMD(localBlock);

        if (encrypting) {
            std::cout << "Round " << round << " result: ";
        } else {
            std::cout << "Round " << round << " reversed result: ";
        }

        for (auto byte : localBlock) {
            std::cout << std::hex << static_cast<int>(byte) << " ";
        }
        std::cout << std::endl;
    };

    std::vector<std::thread> threads;
    std::mutex outputMutex;

    if (encrypting) {
        for (int round = 0; round < numRounds; ++round) {
            threads.emplace_back([&, round] {
                std::lock_guard<std::mutex> guard(outputMutex);
                processRound(round, block);
            });
        }
    } else {
        for (int round = numRounds - 1; round >= 0; --round) {
            threads.emplace_back([&, round] {
                std::lock_guard<std::mutex> guard(outputMutex);
                processRound(round, block);
            });
        }
    }

    // Join all threads to ensure completion
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Completed applyRounds." << std::endl;
}
