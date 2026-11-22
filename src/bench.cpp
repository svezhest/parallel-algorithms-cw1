#include "quicksort.h"

#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include <parlay/parallel.h>

namespace {

constexpr int kRuns = 5;

using SortFn = void (*)(std::vector<int> &);

double timeSort(SortFn sort, std::vector<int> &arr) {
    auto start = std::chrono::steady_clock::now();
    sort(arr);
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

void bench(const char *title, SortFn sort, const std::vector<int> &base) {
    std::cout << "## " << title << "\n\n";

    double total = 0.0;
    for (int run = 1; run <= kRuns; ++run) {
        std::vector<int> work = base;
        double seconds = timeSort(sort, work);
        total += seconds;
        std::cout << "run " << run << ": " << std::fixed << std::setprecision(4) << seconds
                  << " s\n";
    }

    std::cout << "average: " << std::fixed << std::setprecision(4) << total / kRuns << " s\n\n";
}

} // namespace

int main() {
    const std::size_t n = 100'000'000;
    
    if (parlay::num_workers() != 4) {
        std::cerr << "expected 4 workers, got " << parlay::num_workers() << "\n";
        return 1;
    }

    std::mt19937 gen(std::random_device{}());
    std::vector<int> base(n);
    for (auto &x : base) {
        x = static_cast<int>(gen());
    }

    bench("Sequential", quicksort_seq, base);
    bench("Parallel", quicksort_par, base);
}
