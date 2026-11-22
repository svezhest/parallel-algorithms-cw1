#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <random>
#include <vector>

#include "quicksort.h"

namespace {

using SortFn = void (*)(std::vector<int> &);

void expectSorted(SortFn sort, std::vector<int> arr) {
    auto expected = arr;
    std::sort(expected.begin(), expected.end());
    sort(arr);
    EXPECT_EQ(arr, expected);
}

void expectSortedByBoth(std::vector<int> arr) {
    expectSorted(quicksort_seq, arr);
    expectSorted(quicksort_par, arr);
}

} // namespace

TEST(Quicksort, Empty) { expectSortedByBoth({}); }

TEST(Quicksort, OneElement) {
    expectSortedByBoth({0});
    expectSortedByBoth({-5});
}

TEST(Quicksort, TwoElements) {
    expectSortedByBoth({0, 0});
    expectSortedByBoth({0, 1});
    expectSortedByBoth({1, 0});
    expectSortedByBoth({1, 1});
}

TEST(Quicksort, Sorted) {
    std::vector<int> arr(20);
    std::iota(arr.begin(), arr.end(), 0);
    expectSortedByBoth(arr);
}

TEST(Quicksort, Reversed) {
    std::vector<int> arr(20);
    std::iota(arr.rbegin(), arr.rend(), 0);
    expectSortedByBoth(arr);
}

TEST(Quicksort, AllEqual) { expectSortedByBoth(std::vector<int>(100, 7)); }

TEST(Quicksort, Random) {
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(-100, 100);

    std::vector<int> arr(20);
    for (auto &x : arr) {
        x = dist(gen);
    }

    expectSortedByBoth(arr);
}

TEST(Quicksort, RandomLargeWithDuplicates) {
    std::mt19937 gen(7);
    std::uniform_int_distribution<int> dist(-1000, 1000);

    std::vector<int> arr(100'000);
    for (auto &x : arr) {
        x = dist(gen);
    }

    expectSortedByBoth(arr);
}

TEST(Quicksort, Huge) {
    std::mt19937 gen(123);
    std::vector<int> arr(20'000'000);
    for (auto &x : arr) {
        x = static_cast<int>(gen());
    }

    expectSortedByBoth(arr);
}
