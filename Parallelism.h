#ifndef PARALLELISM_H
#define PARALLELISM_H

#include <vector>
#include <cstdint>

enum class SIMDLevel {
    NONE,
    SSE2,  // Use SSE2 as the correct SIMD level
    AVX2
};

class Parallelism {
public:
    SIMDLevel detectBestSIMD();
    void applySIMD(std::vector<uint8_t>& block, SIMDLevel simdLevel);
};

#endif // PARALLELISM_H
