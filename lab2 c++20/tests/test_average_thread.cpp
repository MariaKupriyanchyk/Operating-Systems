#include "../include/average_thread.h"
#include <gtest/gtest.h>

TEST(AverageThread, CalculatesCorrectAverage) {
    std::vector<int> arr = { 2, 4, 6, 8 };
    find_average(&arr);
    EXPECT_DOUBLE_EQ(g_avg_result.value, 5.0);
}

TEST(AverageThread, AllEqualValues) {
    std::vector<int> arr = { 3, 3, 3 };
    find_average(&arr);
    EXPECT_DOUBLE_EQ(g_avg_result.value, 3.0);
}

TEST(AverageThread, SingleElement) {
    std::vector<int> arr = { 42 };
    find_average(&arr);
    EXPECT_DOUBLE_EQ(g_avg_result.value, 42.0);
}

TEST(AverageThread, HandlesNegativeNumbers) {
    std::vector<int> arr = { -5, -15, -10 };
    find_average(&arr);
    EXPECT_DOUBLE_EQ(g_avg_result.value, -10.0);
}

TEST(AverageThread, MixedPositiveAndNegative) {
    std::vector<int> arr = { -2, 4, -6, 8 };
    find_average(&arr);
    EXPECT_DOUBLE_EQ(g_avg_result.value, 1.0);
}
