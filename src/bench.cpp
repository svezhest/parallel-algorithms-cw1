#include "quicksort.h"

#include <chrono>
#include <cstddef>
#include <iostream>
#include <random>
#include <vector>

int main() {
    constexpr std::size_t n = 100'000'000;
    constexpr int runs = 5;

    std::mt19937 gen(42);
    double total = 0.0;

    for (int run = 0; run < runs; ++run) {
        std::vector<int> arr(n);
        for (auto &x : arr) {
            x = static_cast<int>(gen());
        }

        auto start = std::chrono::steady_clock::now();
        quicksort(arr);
        auto end = std::chrono::steady_clock::now();

        double seconds = std::chrono::duration<double>(end - start).count();
        total += seconds;
        std::cout << "run " << run + 1 << ": " << seconds << " s\n";
    }

    std::cout << "average: " << total / runs << " s\n";
}
