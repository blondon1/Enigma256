#include "SideChannelResistance.h"
#include <iostream>

// Function to apply randomization for side-channel resistance
void SideChannelResistance::applyRandomization(std::vector<uint8_t>& block) {
    std::cout << "Applying randomization..." << std::endl;

    // Apply a simple XOR with a fixed value for now (example: 0xAA)
    for (auto& byte : block) {
        byte ^= 0xAA;
    }

    std::cout << "Randomized Data: ";
    for (const auto& byte : block) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;
}

// Function to remove randomization (must exactly reverse the above)
void SideChannelResistance::removeRandomization(std::vector<uint8_t>& block) {
    std::cout << "Removing randomization..." << std::endl;

    // Reverse the XOR with the same value (example: 0xAA)
    for (auto& byte : block) {
        byte ^= 0xAA;
    }

    std::cout << "De-randomized Data: ";
    for (const auto& byte : block) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;
}



