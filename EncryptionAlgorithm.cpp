#include "EncryptionAlgorithm.h"
#include "Timer.h"
#include <iostream>
#include <thread>    // Include thread here
#include <mutex>     // Include mutex here
#include <algorithm> // Include algorithm here
#include <vector>    // Include vector here
#include "Config.h"



EncryptionAlgorithm::EncryptionAlgorithm(int keySize, EncryptionMode::Mode mode)
    : keyManagement(keySize), mode(mode, keyManagement.generateRandomKey()) {
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
    Timer timer; // Start the timer
    std::cout << "Entering encrypt function..." << std::endl;
    std::vector<uint8_t> block = data;

    // Perform encryption
    sideChannelResistance.applyRandomization(block);
    applyRounds(block, true);

    double timeTaken = timer.elapsed(); // Get elapsed time
    std::cout << "Encryption completed in " << timeTaken << " ms." << std::endl;

    return block;
}

std::vector<uint8_t> EncryptionAlgorithm::decrypt(const std::vector<uint8_t>& data) {
    Timer timer; // Start the timer
    std::cout << "Entering decrypt function..." << std::endl;
    std::vector<uint8_t> block = data;

    applyRounds(block, false);

    double timeTaken = timer.elapsed(); // Get elapsed time
    std::cout << "Decryption completed in " << timeTaken << " ms." << std::endl;

    sideChannelResistance.removeRandomization(block);
    return block;
}

void EncryptionAlgorithm::applyRounds(std::vector<uint8_t>& block, bool encrypting) {
    std::cout << "Starting applyRounds..." << std::endl;
    int numRounds = roundKeys.size();

    SIMDLevel simdLevel = parallelism.detectBestSIMD(); // Detect SIMD level

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
        parallelism.applySIMD(localBlock, simdLevel); // Pass SIMD level

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
