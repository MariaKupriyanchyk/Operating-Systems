#include "linked_list.h"
#include "fibonacci.h"
#include <gtest/gtest.h>
#include <vector>

TEST(LinkedListInputTest, ThrowsOnNonNumericInput) {
    std::istringstream fakeInput("abc");
    std::cin.rdbuf(fakeInput.rdbuf());
    EXPECT_THROW(read_positive_int(), std::invalid_argument);
}

TEST(LinkedListInputTest, ThrowsOnZeroOrNegative) {
    std::istringstream fakeInput("0");
    std::cin.rdbuf(fakeInput.rdbuf());
    EXPECT_THROW(read_positive_int(), std::invalid_argument);

    std::istringstream fakeInput2("-5");
    std::cin.rdbuf(fakeInput2.rdbuf());
    EXPECT_THROW(read_positive_int(), std::invalid_argument);
}

TEST(LinkedListInputTest, ReadsPositiveNumberCorrectly) {
    std::istringstream fakeInput("7");
    std::cin.rdbuf(fakeInput.rdbuf());
    EXPECT_NO_THROW({ int n = read_positive_int(); EXPECT_EQ(n, 7); });
}
