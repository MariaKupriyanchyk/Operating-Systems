#include "palindrome.h"
#include <gtest/gtest.h>

TEST(PalindromeTests, BasicCases) {
    EXPECT_TRUE(is_palindrome_number(121));
    EXPECT_TRUE(is_palindrome_number(12321));
    EXPECT_FALSE(is_palindrome_number(123));
    EXPECT_FALSE(is_palindrome_number(-121));
}