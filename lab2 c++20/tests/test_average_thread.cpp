#include "../include/average_thread.h"
#include <gtest/gtest.h>

TEST(AverageThread, CalculatesCorrectAverage) {
    std::vector<int> arr = { 2, 4, 6, 8 };
    find_average(&arr);
    EXPECT_DOUBLE_EQ(g_avg_result.value, 5.0);
}
