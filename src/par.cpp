#include "quicksort.h"

#include <cstddef>
#include <parlay/parallel.h>
#include <random>
#include <utility>

namespace {

void quicksort_impl(std::vector<int> &arr, std::ptrdiff_t from, std::ptrdiff_t to,
                    std::mt19937 &gen) {
    if (to - from <= 1) {
        return;
    }

    std::uniform_int_distribution<std::ptrdiff_t> dist(from, to - 1);
    int pivot = arr[dist(gen)];

    std::ptrdiff_t l = from;
    std::ptrdiff_t r = to;
    std::ptrdiff_t i = from;

    while (i < r) {
        if (arr[i] < pivot) {
            std::swap(arr[l], arr[i]);
            ++l;
            ++i;
        } else if (arr[i] > pivot) {
            --r;
            std::swap(arr[i], arr[r]);
        } else {
            ++i;
        }
    }

    auto size = std::max(l - from, to - r);
    if (size > 1'000'000) {
        std::mt19937 left_gen(gen());
        std::mt19937 right_gen(gen());
        parlay::par_do([&] { quicksort_impl(arr, from, l, left_gen); },
                       [&] { quicksort_impl(arr, r, to, right_gen); });
    } else {
        quicksort_impl(arr, from, l, gen);
        quicksort_impl(arr, r, to, gen);
    }
}

} // namespace

void quicksort_par(std::vector<int> &arr) {
    std::mt19937 gen(std::random_device{}());
    quicksort_impl(arr, 0, static_cast<std::ptrdiff_t>(arr.size()), gen);
}
