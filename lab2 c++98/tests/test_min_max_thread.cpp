#include "../include/min_max_thread.h"
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

TEST(MinMaxThread, FindsCorrectValues) {
    std::vector<int> arr;
    arr.push_back(5);
    arr.push_back(1);
    arr.push_back(9);
    arr.push_back(2);

    find_min_max(&arr);
    EXPECT_EQ(g_minmax_result.min, 1);
    EXPECT_EQ(g_minmax_result.max, 9);
}

TEST(MinMaxThread, AllElementsEqual) {
    std::vector<int> arr;
    arr.push_back(7);
    arr.push_back(7);
    arr.push_back(7);
    arr.push_back(7);

    find_min_max(&arr);
    EXPECT_EQ(g_minmax_result.min, 7);
    EXPECT_EQ(g_minmax_result.max, 7);
}

TEST(MinMaxThread, SingleElement) {
    std::vector<int> arr;
    arr.push_back(42);

    find_min_max(&arr);
    EXPECT_EQ(g_minmax_result.min, 42);
    EXPECT_EQ(g_minmax_result.max, 42);
}

TEST(MinMaxThread, HandlesNegativeNumbers) {
    std::vector<int> arr;
    arr.push_back(-5);
    arr.push_back(-1);
    arr.push_back(-10);
    arr.push_back(-3);

    find_min_max(&arr);
    EXPECT_EQ(g_minmax_result.min, -10);
    EXPECT_EQ(g_minmax_result.max, -1);
}

TEST(MinMaxThread, MixedPositiveAndNegative) {
    std::vector<int> arr;
    arr.push_back(-8);
    arr.push_back(0);
    arr.push_back(15);
    arr.push_back(-2);
    arr.push_back(9);

    find_min_max(&arr);
    EXPECT_EQ(g_minmax_result.min, -8);
    EXPECT_EQ(g_minmax_result.max, 15);
}
