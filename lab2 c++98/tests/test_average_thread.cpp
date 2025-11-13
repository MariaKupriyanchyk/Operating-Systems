#include "../include/average_thread.h"
#include <gtest/gtest.h>

extern CRITICAL_SECTION g_console_cs;

class GlobalTestEnvironment : public ::testing::Environment {
public:
    virtual void SetUp() {
        InitializeCriticalSection(&g_console_cs);
    }

    virtual void TearDown() {
        DeleteCriticalSection(&g_console_cs);
    }
};

static ::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobalTestEnvironment());

TEST(AverageThread, CalculatesCorrectAverage) {
    std::vector<int> arr;
    arr.push_back(2);
    arr.push_back(4);
    arr.push_back(6);
    arr.push_back(8);

    find_average(&arr);
    EXPECT_DOUBLE_EQ(g_avg_result.value, 5.0);
}

TEST(AverageThread, AllEqualValues) {
    std::vector<int> arr;
    arr.push_back(3);
    arr.push_back(3);
    arr.push_back(3);

    find_average(&arr);
    EXPECT_DOUBLE_EQ(g_avg_result.value, 3.0);
}

TEST(AverageThread, SingleElement) {
    std::vector<int> arr;
    arr.push_back(42);

    find_average(&arr);
    EXPECT_DOUBLE_EQ(g_avg_result.value, 42.0);
}

TEST(AverageThread, HandlesNegativeNumbers) {
    std::vector<int> arr;
    arr.push_back(-5);
    arr.push_back(-15);
    arr.push_back(-10);

    find_average(&arr);
    EXPECT_DOUBLE_EQ(g_avg_result.value, -10.0);
}

TEST(AverageThread, MixedPositiveAndNegative) {
    std::vector<int> arr;
    arr.push_back(-2);
    arr.push_back(4);
    arr.push_back(-6);
    arr.push_back(8);

    find_average(&arr);
    EXPECT_DOUBLE_EQ(g_avg_result.value, 1.0);
}
