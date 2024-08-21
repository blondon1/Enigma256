#include "Parallelism.h"
#include <iostream>
#include <mutex>

std::mutex mtx;

void Parallelism::applySIMD(std::vector<uint8_t>& block) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Entering applySIMD with block size: " << block.size() << std::endl;

    for (auto& byte : block) {
        byte ^= 0xFF;
    }

    std::cout << "Exiting applySIMD..." << std::endl;
}

void Parallelism::parallelizeRounds(std::vector<uint8_t>& block, int numRounds, std::function<void(std::vector<uint8_t>&, int)> roundFunction) {
    std::vector<std::thread> threads;

    for (int round = 0; round < numRounds; ++round) {
        threads.emplace_back([&block, round, &roundFunction]() {
            {
                std::lock_guard<std::mutex> lock(mtx);
                std::cout << "Starting round " << round << " with block size: " << block.size() << std::endl;
            }
            roundFunction(block, round);
            {
                std::lock_guard<std::mutex> lock(mtx);
                std::cout << "Completed round " << round << std::endl;
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }
}
