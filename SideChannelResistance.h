#ifndef SIDECHANNELRESISTANCE_H
#define SIDECHANNELRESISTANCE_H

#include <vector>
#include <cstdint>

class SideChannelResistance {
public:
    void applyRandomization(std::vector<uint8_t>& block);
    void removeRandomization(std::vector<uint8_t>& block);  // Add this line
};

#endif

