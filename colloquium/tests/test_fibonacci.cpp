#include "fibonacci.h"
#include <gtest/gtest.h>

TEST(FibonacciTests, CorrectValues) {
    std::vector<uint64_t> expected = { 1, 1, 2, 3, 5 };
    EXPECT_EQ(first_n_fibonacci(5), expected);
}

TEST(FibonacciTests, ZeroThrows) {
    EXPECT_THROW(first_n_fibonacci(0), std::invalid_argument);
}