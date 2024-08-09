#include "SideChannelResistance.h"
#include <random>

// Function to apply randomization to the encryption process
void SideChannelResistance::applyRandomization(std::vector<uint8_t>& data) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> dis(0, 255);

    for (auto& byte : data) {
        byte ^= dis(gen); // XOR with a random byte to randomize data
    }
}

// Function to apply masking to sensitive data
void SideChannelResistance::applyMasking(std::vector<uint8_t>& data, const std::vector<uint8_t>& mask) {
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] ^= mask[i % mask.size()]; // XOR data with mask
    }
}

// Function to remove masking after processing
void SideChannelResistance::removeMasking(std::vector<uint8_t>& data, const std::vector<uint8_t>& mask) {
    applyMasking(data, mask); // Reapplying the same mask removes it
}
