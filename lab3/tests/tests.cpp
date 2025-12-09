#include <gtest/gtest.h>
#include "shared_array.h"

TEST(SharedArray, StartsWithZeros) {
    SharedArray a(5);
    auto snap = a.snapshot();
    for (int v : snap) EXPECT_EQ(v, 0);
}

TEST(SharedArray, MarksCorrectly) {
    SharedArray a(3);
    EXPECT_TRUE(a.try_mark(1, 2));
    EXPECT_FALSE(a.try_mark(1, 3));
    EXPECT_EQ(a.get(1), 2);
}

TEST(SharedArray, ClearsById) {
    SharedArray a(5);
    a.try_mark(0, 1);
    a.try_mark(2, 1);
    a.clear_by_id(1);
    EXPECT_EQ(a.get(0), 0);
    EXPECT_EQ(a.get(2), 0);
}