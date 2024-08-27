#ifndef ENCRYPTION_MODE_H
#define ENCRYPTION_MODE_H

#include <vector>
#include <cstdint>

class EncryptionMode {
public:
    enum class Mode {
        ECB,
        CBC,
        CFB,
        OFB
        // Add other modes as needed
    };

    EncryptionMode(Mode mode, const std::vector<uint8_t>& key);

    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& data, const std::vector<std::vector<uint8_t>>& roundKeys);
    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& data, const std::vector<std::vector<uint8_t>>& roundKeys);

private:
    Mode mode;
    std::vector<uint8_t> key;
};

#endif // ENCRYPTION_MODE_H
