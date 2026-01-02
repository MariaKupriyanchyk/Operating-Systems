#include <gtest/gtest.h>
#include <regex>
#include <string>
#include "file_queue.h"

static bool is_valid_positive_uint(const std::string& input) {
    static std::regex reg("^[1-9][0-9]*$");
    return std::regex_match(input, reg);
}

//input tests
TEST(InputValidationTest, ValidNumbers) {
    EXPECT_TRUE(is_valid_positive_uint("1"));
    EXPECT_TRUE(is_valid_positive_uint("10"));
    EXPECT_TRUE(is_valid_positive_uint("999"));
}

TEST(InputValidationTest, RejectZero) {
    EXPECT_FALSE(is_valid_positive_uint("0"));
}

TEST(InputValidationTest, RejectNegative) {
    EXPECT_FALSE(is_valid_positive_uint("-1"));
    EXPECT_FALSE(is_valid_positive_uint("-100"));
}

TEST(InputValidationTest, RejectLetters) {
    EXPECT_FALSE(is_valid_positive_uint("abc"));
    EXPECT_FALSE(is_valid_positive_uint("12a"));
}

TEST(InputValidationTest, RejectExpressions) {
    EXPECT_FALSE(is_valid_positive_uint("2/1"));
    EXPECT_FALSE(is_valid_positive_uint("1+2"));
}

TEST(InputValidationTest, RejectFractional) {
    EXPECT_FALSE(is_valid_positive_uint("1.5"));
    EXPECT_FALSE(is_valid_positive_uint("0.15"));
}

TEST(InputValidationTest, RejectEmptyString) {
    EXPECT_FALSE(is_valid_positive_uint(""));
}

//fileQueue tests
TEST(FileQueueTest, ValidMessage) {
    FileQueue q("test_valid.bin", 2);
    q.push("hello");
    EXPECT_EQ(q.pop(), "hello");
}

TEST(FileQueueTest, MaxLengthMessage) {
    FileQueue q("test_len.bin", 2);
    q.push("12345678901234567890");
    EXPECT_EQ(q.pop(), "12345678901234567890");
}

TEST(FileQueueTest, TooLongMessage) {
    FileQueue q("test_error.bin", 2);
    EXPECT_THROW(q.push("123456789012345678901"), std::runtime_error);
}

TEST(FileQueueTest, EmptyMessage) {
    FileQueue q("test_empty.bin", 2);
    EXPECT_THROW(q.push(""), std::runtime_error);
}
