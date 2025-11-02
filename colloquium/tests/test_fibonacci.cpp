#include "fibonacci.h"
#include <gtest/gtest.h>

TEST(FibonacciLogicTest, ThrowsOnZeroOrNegative) {
    EXPECT_THROW(first_n_fibonacci(0), std::invalid_argument);
    EXPECT_THROW(first_n_fibonacci(-5), std::invalid_argument);
}

TEST(FibonacciLogicTest, WorksForSmallNumbers) {
    auto result = first_n_fibonacci(5);
    std::vector<uint64_t> expected = { 1, 1, 2, 3, 5 };
    EXPECT_EQ(result, expected);
}

TEST(FibonacciInputTest, ThrowsOnNonNumericInput) {
    std::istringstream fakeInput("abc");
    std::cin.rdbuf(fakeInput.rdbuf());
    EXPECT_THROW(read_positive_int(), std::invalid_argument);
}

TEST(FibonacciInputTest, ThrowsOnZeroOrNegative) {
    std::istringstream fakeInput("0");
    std::cin.rdbuf(fakeInput.rdbuf());
    EXPECT_THROW(read_positive_int(), std::invalid_argument);

    std::istringstream fakeInput2("-10");
    std::cin.rdbuf(fakeInput2.rdbuf());
    EXPECT_THROW(read_positive_int(), std::invalid_argument);
}

TEST(FibonacciInputTest, ReadsValidPositiveNumber) {
    std::istringstream fakeInput("7");
    std::cin.rdbuf(fakeInput.rdbuf());
    EXPECT_NO_THROW({ int n = read_positive_int(); EXPECT_EQ(n, 7); });
}
