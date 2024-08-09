#ifndef SIDE_CHANNEL_RESISTANCE_H
#define SIDE_CHANNEL_RESISTANCE_H

#include <vector>
#include <cstdint>

// Side-Channel Resistance for Enigma256

class SideChannelResistance {
public:
    // Function to apply randomization to the encryption process
    void applyRandomization(std::vector<uint8_t>& data);

    // Function to apply masking to sensitive data
    void applyMasking(std::vector<uint8_t>& data, const std::vector<uint8_t>& mask);
    
    // Function to remove masking after processing
    void removeMasking(std::vector<uint8_t>& data, const std::vector<uint8_t>& mask);
};

#endif // SIDE_CHANNEL_RESISTANCE_H
