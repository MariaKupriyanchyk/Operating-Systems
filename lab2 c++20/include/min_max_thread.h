#pragma once
#include <windows.h>
#include <vector>
#include <iostream>
#include <mutex>

struct MinMaxResult {
    long long min = 0;
    long long max = 0;
};

DWORD WINAPI find_min_max(LPVOID param);
extern MinMaxResult g_minmax_result;
extern std::mutex g_console_mutex;
