#include <iostream>
#include <vector>
#include <cassert>
#include "EncryptionAlgorithm.h"
#include "Config.h"

void testEncryptionDecryption() {
    // Example key size (256-bit)
    int keySize = DEFAULT_KEY_SIZE;

    // Initialize the Enigma256 encryption algorithm
    EncryptionAlgorithm enigma256(keySize, EncryptionMode::Mode::ECB);

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

    // Test: Decrypted data should match the original data
    assert(decryptedData == data);
    std::cout << "Test 1 passed: Encryption and decryption are consistent." << std::endl;
}

void testDifferentKeys() {
    // Example key sizes
    int keySize1 = 128;
    int keySize2 = 256;

    // Initialize the Enigma256 encryption algorithm with different key sizes
    EncryptionAlgorithm enigma256_1(keySize1, EncryptionMode::Mode::ECB);
    EncryptionAlgorithm enigma256_2(keySize2, EncryptionMode::Mode::ECB);

    // Example data to encrypt (must be 256 bits / 32 bytes in size)
    std::vector<uint8_t> data = {
        0x32, 0x88, 0x31, 0xE0, 0x43, 0x5A, 0x31, 0x37,
        0xF6, 0x30, 0x98, 0x07, 0xA8, 0x8D, 0xA2, 0x34,
        0x53, 0x32, 0x8F, 0xE0, 0xA5, 0x12, 0x0E, 0x03,
        0x6D, 0x6F, 0x41, 0xAF, 0x9F, 0x20, 0x23, 0x21
    };

    // Encrypt the data with both keys
    std::vector<uint8_t> encryptedData1 = enigma256_1.encrypt(data);
    std::vector<uint8_t> encryptedData2 = enigma256_2.encrypt(data);

    // Test: Encrypted data should be different with different keys
    assert(encryptedData1 != encryptedData2);
    std::cout << "Test 2 passed: Different keys produce different ciphertexts." << std::endl;
}

void runAllTests() {
    testEncryptionDecryption();
    testDifferentKeys();
}

int main() {
    runAllTests();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
