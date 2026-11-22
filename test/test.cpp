#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

#include "quicksort.h"

namespace {

void expectSorted(std::vector<int> arr) {
    auto expected = arr;
    std::sort(expected.begin(), expected.end());
    quicksort(arr);
    EXPECT_EQ(arr, expected);
}

} // namespace

TEST(Quicksort, Empty) { expectSorted({}); }

TEST(Quicksort, OneElement) {
    expectSorted({0});
    expectSorted({-5});
}

TEST(Quicksort, TwoElements) {
    expectSorted({0, 0});
    expectSorted({0, 1});
    expectSorted({1, 0});
    expectSorted({1, 1});
}

TEST(Quicksort, Sorted) {
    std::vector<int> arr(20);
    std::iota(arr.begin(), arr.end(), 0);
    expectSorted(arr);
}

TEST(Quicksort, Reversed) {
    std::vector<int> arr(20);
    std::iota(arr.rbegin(), arr.rend(), 0);
    expectSorted(arr);
}

TEST(Quicksort, Random) {
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(-100, 100);

    std::vector<int> arr(20);
    for (auto &x : arr) {
        x = dist(gen);
    }

    expectSorted(arr);
}
