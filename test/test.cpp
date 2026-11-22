#include <gtest/gtest.h>
#include <parlay/parallel.h>
#include <atomic>

TEST(Test, Test) {
    std::atomic<int> counter = 0;

    parlay::parallel_for(0, 4, [&counter](int _) {
        ++counter;
    });

    ASSERT_EQ(counter, 4);
}

TEST(Failme, Test) {
    std::atomic<int> counter = 0;

    parlay::parallel_for(0, 4, [&counter](int _) {
        ++counter;
    });

    ASSERT_EQ(counter, 3);
}