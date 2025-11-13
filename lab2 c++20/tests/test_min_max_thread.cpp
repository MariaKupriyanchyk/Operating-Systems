#include "../include/min_max_thread.h"
#include <gtest/gtest.h>

TEST(MinMaxThread, FindsCorrectValues) {
    std::vector<int> arr = { 5, 1, 9, 2 };
    find_min_max(&arr);
    EXPECT_EQ(g_minmax_result.min, 1);
    EXPECT_EQ(g_minmax_result.max, 9);
}

TEST(MinMaxThread, AllElementsEqual) {
    std::vector<int> arr = { 7, 7, 7, 7 };
    find_min_max(&arr);
    EXPECT_EQ(g_minmax_result.min, 7);
    EXPECT_EQ(g_minmax_result.max, 7);
}

TEST(MinMaxThread, SingleElement) {
    std::vector<int> arr = { 42 };
    find_min_max(&arr);
    EXPECT_EQ(g_minmax_result.min, 42);
    EXPECT_EQ(g_minmax_result.max, 42);
}

TEST(MinMaxThread, HandlesNegativeNumbers) {
    std::vector<int> arr = { -5, -1, -10, -3 };
    find_min_max(&arr);
    EXPECT_EQ(g_minmax_result.min, -10);
    EXPECT_EQ(g_minmax_result.max, -1);
}

TEST(MinMaxThread, MixedPositiveAndNegative) {
    std::vector<int> arr = { -8, 0, 15, -2, 9 };
    find_min_max(&arr);
    EXPECT_EQ(g_minmax_result.min, -8);
    EXPECT_EQ(g_minmax_result.max, 15);
}
