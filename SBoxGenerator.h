#ifndef SBOX_GENERATOR_H
#define SBOX_GENERATOR_H

#include <vector>
#include <cstdint>

// S-Box Generator for Enigma256

class SBoxGenerator {
public:
    // Function to generate a dynamic S-box based on the key or input data
    std::vector<uint8_t> generateSBox(const std::vector<uint8_t>& key);

private:
    // Helper function to initialize the S-box
    void initializeSBox(std::vector<uint8_t>& sbox);

    // Helper function to shuffle the S-box using the key
    void shuffleSBox(std::vector<uint8_t>& sbox, const std::vector<uint8_t>& key);
};

#endif // SBOX_GENERATOR_H
