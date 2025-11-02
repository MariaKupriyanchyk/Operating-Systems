#include "palindrome.h"
#include <gtest/gtest.h>

TEST(PalindromeTest, ThrowsOnEmptyInput) {
    EXPECT_THROW(is_palindrome_number(""), std::invalid_argument);
}

TEST(PalindromeTest, ThrowsOnNonDigitInput) {
    EXPECT_THROW(is_palindrome_number("12a21"), std::invalid_argument);
    EXPECT_THROW(is_palindrome_number("-121"), std::invalid_argument);
    EXPECT_THROW(is_palindrome_number("jdhfkd"), std::invalid_argument);
    EXPECT_THROW(is_palindrome_number("abcba"), std::invalid_argument);
}

TEST(PalindromeTest, DetectsPalindromeCorrectly) {
    EXPECT_TRUE(is_palindrome_number("12321"));
    EXPECT_FALSE(is_palindrome_number("12345"));
}
