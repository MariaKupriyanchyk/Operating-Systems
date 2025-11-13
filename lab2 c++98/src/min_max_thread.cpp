#include "../include/min_max_thread.h"
#include <algorithm>

MinMaxResult g_minmax_result;

DWORD WINAPI find_min_max(LPVOID param) {
    std::vector<int>* arr = static_cast<std::vector<int>*>(param);
    if (arr == NULL || arr->empty()) {
        return 1;
    }

    long minVal = (*arr)[0];
    long maxVal = (*arr)[0];

    for (size_t i = 1; i < arr->size(); ++i) {
        if ((*arr)[i] < minVal) minVal = (*arr)[i];
        if ((*arr)[i] > maxVal) maxVal = (*arr)[i];
        Sleep(7);
    }

    g_minmax_result.min = minVal;
    g_minmax_result.max = maxVal;

    EnterCriticalSection(&g_console_cs);
    std::cout << "Min = " << minVal << std::endl;
    std::cout << "Max = " << maxVal << std::endl;
    LeaveCriticalSection(&g_console_cs);

    return 0;
}