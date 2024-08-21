#ifndef PARALLELISM_H
#define PARALLELISM_H

#include <vector>
#include <cstdint>
#include <thread>
#include <functional>

// Parallelism and Optimization for Enigma256

class Parallelism {
public:
    // Function to apply SIMD instructions to a block of data
    void applySIMD(std::vector<uint8_t>& block);

    // Function to parallelize encryption rounds using multi-threading
    void parallelizeRounds(std::vector<uint8_t>& block, int numRounds, std::function<void(std::vector<uint8_t>&, int)> roundFunction);
};

#endif // PARALLELISM_H
