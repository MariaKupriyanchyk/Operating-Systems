#pragma once
#ifndef AVERAGE_THREAD_H
#define AVERAGE_THREAD_H
#define NOMINMAX

#include <windows.h>
#include <vector>
#include <iostream>

struct AverageResult {
    double value;
    AverageResult() : value(0.0) {}
};

DWORD WINAPI find_average(LPVOID param);

extern AverageResult g_avg_result;
extern CRITICAL_SECTION g_console_cs;

#endif