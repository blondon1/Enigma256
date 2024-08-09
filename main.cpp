#include <iostream>
#include <vector>
#include "EncryptionAlgorithm.h"
#include "Config.h"

int main() {
    // Example key size (256-bit)
    int keySize = DEFAULT_KEY_SIZE;

    // Initialize the Enigma256 encryption algorithm
    EncryptionAlgorithm enigma256(keySize);

    // Example data to encrypt (must be 256 bits / 32 bytes in size)
    std::vector<uint8_t> data = {
        0x32, 0x88, 0x31, 0xE0, 0x43, 0x5A, 0x31, 0x37,
        0xF6, 0x30, 0x98, 0x07, 0xA8, 0x8D, 0xA2, 0x34,
        0x53, 0x32, 0x8F, 0xE0, 0xA5, 0x12, 0x0E, 0x03,
        0x6D, 0x6F, 0x41, 0xAF, 0x9F, 0x20, 0x23, 0x21
    };

    // Encrypt the data
    std::vector<uint8_t> encryptedData = enigma256.encrypt(data);

    // Decrypt the data
    std::vector<uint8_t> decryptedData = enigma256.decrypt(encryptedData);

    // Output the results
    std::cout << "Original Data: ";
    for (auto byte : data) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

    std::cout << "Encrypted Data: ";
    for (auto byte : encryptedData) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

    std::cout << "Decrypted Data: ";
    for (auto byte : decryptedData) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

    return 0;
}