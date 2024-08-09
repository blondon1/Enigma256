#ifndef MIXING_FUNCTION_H
#define MIXING_FUNCTION_H

#include <vector>
#include <cstdint>

// Mixing Function for Enigma256

class MixingFunction {
public:
    // Function to apply the mixing function to a data block
    void applyMixingFunction(std::vector<uint8_t>& block);

private:
    // Helper function to perform matrix multiplication (or other complex mixing)
    void matrixMultiply(std::vector<uint8_t>& block);
};

#endif // MIXING_FUNCTION_H
