#include "MixingFunction.h"
#include <iostream>

void MixingFunction::applyMixingFunction(std::vector<uint8_t>& block) {
    std::cout << "Entering applyMixingFunction with block size: " << block.size() << std::endl;

    for (auto& byte : block) {
        byte ^= 0xA5;
    }

    std::cout << "Exiting applyMixingFunction..." << std::endl;
}
