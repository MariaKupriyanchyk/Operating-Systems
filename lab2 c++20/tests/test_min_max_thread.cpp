#include "../include/min_max_thread.h"
#include <gtest/gtest.h>

TEST(MinMaxThread, FindsCorrectValues) {
    std::vector<int> arr = { 5, 1, 9, 2 };
    find_min_max(&arr);
    EXPECT_EQ(g_minmax_result.min, 1);
    EXPECT_EQ(g_minmax_result.max, 9);
}