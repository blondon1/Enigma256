#include "Parallelism.h"
#include <iostream>

// Function to apply a simple XOR-based SIMD operation
void Parallelism::applySIMD(std::vector<uint8_t>& block) {
    std::cout << "Entering applySIMD..." << std::endl;

    // XOR each byte with a simple, reversible value
    for (auto& byte : block) {
        byte ^= 0xFF;  // XOR with 0xFF as a reversible operation
    }

    std::cout << "Exiting applySIMD..." << std::endl;
}
