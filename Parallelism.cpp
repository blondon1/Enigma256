#include "Parallelism.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cpuid.h>  // Include cpuid header for detecting SIMD support

// Function to apply SIMD instructions to a block of data
void Parallelism::applySIMD(std::vector<uint8_t>& block, SIMDLevel simdLevel) {
    if (simdLevel == SIMDLevel::NONE) {
        // No SIMD instructions applied
        std::cout << "No SIMD instructions applied." << std::endl;
    } else if (simdLevel == SIMDLevel::SSE2) {  // Corrected to SSE2
        // Apply SSE2-specific operations
        std::cout << "Applying SSE2 SIMD instructions." << std::endl;
        // Example operation using SSE2 (this is a placeholder for actual SIMD code)
        for (auto& byte : block) {
            byte ^= 0x55; // Simple XOR operation as a placeholder
        }
    } else if (simdLevel == SIMDLevel::AVX2) {
        // Apply AVX2-specific operations
        std::cout << "Applying AVX2 SIMD instructions." << std::endl;
        // Example operation using AVX2 (this is a placeholder for actual SIMD code)
        for (auto& byte : block) {
            byte ^= 0xAA; // Simple XOR operation as a placeholder
        }
    }
}

// Function to detect the best SIMD level supported by the CPU
SIMDLevel Parallelism::detectBestSIMD() {
    int cpuInfo[4] = {0, 0, 0, 0};
    
    // Detect if the CPU supports AVX2
    __cpuid(7, cpuInfo[0], cpuInfo[1], cpuInfo[2], cpuInfo[3]);
    if (cpuInfo[1] & (1 << 5)) {  // Check if AVX2 is supported
        return SIMDLevel::AVX2;
    }

    // Detect if the CPU supports SSE2
    __cpuid(1, cpuInfo[0], cpuInfo[1], cpuInfo[2], cpuInfo[3]);
    if (cpuInfo[3] & (1 << 26)) {  // Check if SSE2 is supported
        return SIMDLevel::SSE2;
    }

    // No SIMD support found
    return SIMDLevel::NONE;
}
