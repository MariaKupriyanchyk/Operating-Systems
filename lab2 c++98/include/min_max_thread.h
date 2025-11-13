#pragma once
#ifndef MIN_MAX_THREAD_H
#define MIN_MAX_THREAD_H
#define NOMINMAX

#include <windows.h>
#include <vector>
#include <iostream>

struct MinMaxResult {
    long min;
    long max;
    MinMaxResult() : min(0), max(0) {}
};

DWORD WINAPI find_min_max(LPVOID param);

extern MinMaxResult g_minmax_result;
extern CRITICAL_SECTION g_console_cs;

#endif