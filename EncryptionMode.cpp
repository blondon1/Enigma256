#include "EncryptionMode.h"
#include <algorithm>
#include <vector>

EncryptionMode::EncryptionMode(Mode mode, const std::vector<uint8_t>& key)
    : mode(mode), key(key) {}

// Example encryption function
std::vector<uint8_t> EncryptionMode::encrypt(const std::vector<uint8_t>& data, const std::vector<std::vector<uint8_t>>& roundKeys) {
    std::vector<uint8_t> block = data;

    // Apply XOR operation for demonstration purposes
    std::transform(block.begin(), block.end(), block.begin(), [](uint8_t byte) {
        return byte ^ 0xFF;  // Replace 0xFF with the desired value for encryption
    });

    // Add your encryption logic here using `roundKeys`

    return block;
}

// Example decryption function
std::vector<uint8_t> EncryptionMode::decrypt(const std::vector<uint8_t>& data, const std::vector<std::vector<uint8_t>>& roundKeys) {
    std::vector<uint8_t> block = data;

    // Apply XOR operation for demonstration purposes (reverse operation)
    std::transform(block.begin(), block.end(), block.begin(), [](uint8_t byte) {
        return byte ^ 0xFF;  // Replace 0xFF with the same value used in encryption
    });

    // Add your decryption logic here using `roundKeys`

    return block;
}
