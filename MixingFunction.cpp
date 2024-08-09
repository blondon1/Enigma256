#include "MixingFunction.h"
#include <iostream>

// Function to apply a simple XOR-based mixing function
void MixingFunction::applyMixingFunction(std::vector<uint8_t>& block) {
    std::cout << "Entering applyMixingFunction..." << std::endl;

    // XOR each byte with a simple, reversible value
    for (auto& byte : block) {
        byte ^= 0xA5;  // XOR with 0xA5 as a reversible operation
    }

    std::cout << "Exiting applyMixingFunction..." << std::endl;
}

