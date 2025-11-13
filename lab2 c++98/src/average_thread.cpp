#include "../include/average_thread.h"

AverageResult g_avg_result;
CRITICAL_SECTION g_console_cs;

DWORD WINAPI find_average(LPVOID param) {
    std::vector<int>* arr = static_cast<std::vector<int>*>(param);
    if (arr == NULL || arr->empty()) {
        return 1;
    }

    long sum = 0;
    for (size_t i = 0; i < arr->size(); ++i) {
        sum += (*arr)[i];
        Sleep(12);
    }

    double avg = static_cast<double>(sum) / arr->size();
    g_avg_result.value = avg;

    EnterCriticalSection(&g_console_cs);
    std::cout << "Average = " << avg << std::endl;
    LeaveCriticalSection(&g_console_cs);

    return 0;
}