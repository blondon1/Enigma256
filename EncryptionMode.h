#ifndef ENCRYPTION_MODE_H
#define ENCRYPTION_MODE_H

#include <vector>
#include <cstdint>

class EncryptionMode {
public:
    enum Mode { ECB, CBC }; // Example modes

    EncryptionMode(Mode mode, const std::vector<uint8_t>& key);

    // Encryption function (implement your mode-specific encryption logic here)
    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& data, const std::vector<std::vector<uint8_t>>& roundKeys);

    // Decryption function (implement your mode-specific decryption logic here)
    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& data, const std::vector<std::vector<uint8_t>>& roundKeys);

private:
    Mode mode;
    std::vector<uint8_t> key;
};

#endif // ENCRYPTION_MODE_H
