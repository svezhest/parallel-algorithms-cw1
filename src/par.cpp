#include "quicksort.h"

#include <algorithm>
#include <cstddef>
#include <parlay/parallel.h>
#include <random>
#include <utility>

namespace {

std::mt19937 &rng() {
    thread_local std::mt19937 gen(std::random_device{}());
    return gen;
}

void quicksort_impl(std::vector<int> &arr, std::ptrdiff_t from, std::ptrdiff_t to) {
    if (to - from <= 1) {
        return;
    }

    std::uniform_int_distribution<std::ptrdiff_t> dist(from, to - 1);
    int pivot = arr[dist(rng())];

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
    if (size > 100'000) {
        parlay::par_do([&] { quicksort_impl(arr, from, l); },
                       [&] { quicksort_impl(arr, r, to); });
    } else {
        quicksort_impl(arr, from, l);
        quicksort_impl(arr, r, to);
    }
}

} // namespace

void quicksort_par(std::vector<int> &arr) {
    quicksort_impl(arr, 0, static_cast<std::ptrdiff_t>(arr.size()));
}
