#ifndef ENCRYPTION_ALGORITHM_H
#define ENCRYPTION_ALGORITHM_H

#include <vector>
#include <cstdint>
#include "KeyManagement.h"
#include "SBoxGenerator.h"
#include "MixingFunction.h"
#include "Parallelism.h"
#include "SideChannelResistance.h"
#include "EncryptionMode.h"

// Core Encryption Algorithm for Enigma256

class EncryptionAlgorithm {
public:
    // Constructor to initialize the encryption algorithm with necessary components
    EncryptionAlgorithm(int keySize, EncryptionMode::Mode mode);

    // Function to encrypt a block of data
    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& data);

    // Function to decrypt a block of data
    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& data);

private:
    KeyManagement keyManagement;
    SBoxGenerator sboxGenerator;
    MixingFunction mixingFunction;
    Parallelism parallelism;
    SideChannelResistance sideChannelResistance;
    EncryptionMode encryptionMode;

    std::vector<std::vector<uint8_t>> roundKeys; // Expanded keys for each round
    std::vector<uint8_t> sbox; // Dynamic S-box

    void initialize(const std::vector<uint8_t>& key); // Initialize the algorithm
    void applyRounds(std::vector<uint8_t>& block, bool encrypting); // Apply encryption or decryption rounds
};

#endif // ENCRYPTION_ALGORITHM_H
