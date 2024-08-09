#include "MixingFunction.h"
#include <array>
#include <numeric>

// Function to apply the mixing function to a data block
void MixingFunction::applyMixingFunction(std::vector<uint8_t>& block) {
    // Apply the matrix multiplication or other complex mixing operation
    matrixMultiply(block);
}

// Helper function to perform matrix multiplication (or other complex mixing)
void MixingFunction::matrixMultiply(std::vector<uint8_t>& block) {
    const std::array<std::array<uint8_t, 4>, 4> matrix = {{
        {0x02, 0x03, 0x01, 0x01},
        {0x01, 0x02, 0x03, 0x01},
        {0x01, 0x01, 0x02, 0x03},
        {0x03, 0x01, 0x01, 0x02}
    }};
    
    std::vector<uint8_t> mixedBlock(block.size(), 0);

    // Perform matrix multiplication (assuming block is 16 bytes for simplicity)
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            for (size_t k = 0; k < 4; ++k) {
                mixedBlock[i * 4 + j] ^= matrix[i][k] * block[k * 4 + j];
            }
        }
    }

    block = mixedBlock;
}
