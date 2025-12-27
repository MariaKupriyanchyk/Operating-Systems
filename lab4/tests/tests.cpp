#include <gtest/gtest.h>
#include "file_queue.h"

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
