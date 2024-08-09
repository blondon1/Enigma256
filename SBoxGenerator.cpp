#include "SBoxGenerator.h"
#include <algorithm>
#include <numeric>

// Function to generate a dynamic S-box based on the key or input data
std::vector<uint8_t> SBoxGenerator::generateSBox(const std::vector<uint8_t>& key) {
    std::vector<uint8_t> sbox(256);
    initializeSBox(sbox);
    shuffleSBox(sbox, key);
    return sbox;
}

// Helper function to initialize the S-box
void SBoxGenerator::initializeSBox(std::vector<uint8_t>& sbox) {
    // Fill the S-box with values from 0 to 255
    std::iota(sbox.begin(), sbox.end(), 0);
}

// Helper function to shuffle the S-box using the key
void SBoxGenerator::shuffleSBox(std::vector<uint8_t>& sbox, const std::vector<uint8_t>& key) {
    // Use the key to shuffle the S-box
    size_t j = 0;
    for (size_t i = 0; i < sbox.size(); ++i) {
        j = (j + sbox[i] + key[i % key.size()]) % sbox.size();
        std::swap(sbox[i], sbox[j]);
    }
}
