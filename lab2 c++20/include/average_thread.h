#pragma once
#include <windows.h>
#include <vector>
#include <iostream>
#include <mutex>

struct AverageResult {
    double value = 0.0;
};

DWORD WINAPI find_average(LPVOID param);
extern AverageResult g_avg_result;
extern std::mutex g_console_mutex;