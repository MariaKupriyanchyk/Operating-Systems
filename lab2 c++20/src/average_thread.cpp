#include "../include/average_thread.h"
#include <numeric>

AverageResult g_avg_result;

DWORD WINAPI find_average(LPVOID param) {
    auto* arr = static_cast<std::vector<int>*>(param);
    if (!arr || arr->empty()) {
        return 1;
    }

    long long sum = 0;
    for (int x : *arr) {
        sum += x;
        Sleep(12);
    }

    double avg = static_cast<double>(sum) / arr->size();
    g_avg_result = { avg };

    std::lock_guard lock(g_console_mutex);
    std::cout << "Average = " << avg << "\n";
    return 0;
}
