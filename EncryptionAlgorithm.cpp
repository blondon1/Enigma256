#include "EncryptionAlgorithm.h"
#include "Timer.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>
#include <vector>
#include "Config.h"

EncryptionAlgorithm::EncryptionAlgorithm(int keySize, EncryptionMode::Mode mode)
    : keyManagement(keySize), mode(mode, keyManagement.generateRandomKey()), logger(LogLevel::DEBUG) { // Initialize Logger
    std::vector<uint8_t> key = keyManagement.generateRandomKey();
    initialize(key);
}

void EncryptionAlgorithm::initialize(const std::vector<uint8_t>& key) {
    logger.log(LogLevel::INFO, "Initializing encryption algorithm with the provided key...");

    sbox = sboxGenerator.generateSBox(key);
    logger.log(LogLevel::DEBUG, "Dynamic S-box generated.");

    int numRounds = MIN_ROUNDS + (key.size() * 8 / DEFAULT_KEY_SIZE) * (MAX_ROUNDS - MIN_ROUNDS);
    roundKeys = keyManagement.expandKey(key, numRounds);
    logger.log(LogLevel::DEBUG, "Key expanded for " + std::to_string(numRounds) + " rounds.");
}

std::vector<uint8_t> EncryptionAlgorithm::encrypt(const std::vector<uint8_t>& data) {
    Timer timer; 
    logger.log(LogLevel::INFO, "Entering encrypt function...");
    std::vector<uint8_t> block = data;

    sideChannelResistance.applyRandomization(block);
    applyRounds(block, true);

    double timeTaken = timer.elapsed(); 
    logger.log(LogLevel::INFO, "Encryption completed in " + std::to_string(timeTaken) + " ms.");

    return block;
}

std::vector<uint8_t> EncryptionAlgorithm::decrypt(const std::vector<uint8_t>& data) {
    Timer timer;
    logger.log(LogLevel::INFO, "Entering decrypt function...");
    std::vector<uint8_t> block = data;

    applyRounds(block, false);

    double timeTaken = timer.elapsed(); 
    logger.log(LogLevel::INFO, "Decryption completed in " + std::to_string(timeTaken) + " ms.");

    sideChannelResistance.removeRandomization(block);
    return block;
}

void EncryptionAlgorithm::applyRounds(std::vector<uint8_t>& block, bool encrypting) {
    logger.log(LogLevel::INFO, "Starting applyRounds...");
    int numRounds = roundKeys.size();

    SIMDLevel simdLevel = parallelism.detectBestSIMD(); 

    auto processRound = [&](int round, std::vector<uint8_t>& localBlock) {
        if (encrypting) {
            logger.log(LogLevel::DEBUG, "Applying round " + std::to_string(round) + " with key: ");
        } else {
            logger.log(LogLevel::DEBUG, "Reversing round " + std::to_string(round) + " with key: ");
        }

        for (auto byte : roundKeys[round]) {
            std::cout << std::hex << static_cast<int>(byte) << " ";
        }
        std::cout << std::endl;

        mixingFunction.applyMixingFunction(localBlock);
        parallelism.applySIMD(localBlock, simdLevel);

        if (encrypting) {
            logger.log(LogLevel::DEBUG, "Round " + std::to_string(round) + " result: ");
        } else {
            logger.log(LogLevel::DEBUG, "Round " + std::to_string(round) + " reversed result: ");
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

    for (auto& t : threads) {
        t.join();
    }

    logger.log(LogLevel::INFO, "Completed applyRounds.");
}
