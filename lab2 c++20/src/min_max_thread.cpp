#include "../include/min_max_thread.h"
#include <thread>

MinMaxResult g_minmax_result;
std::mutex g_console_mutex;

DWORD WINAPI find_min_max(LPVOID param) {
    auto* arr = static_cast<std::vector<long long>*>(param);
    if (!arr || arr->empty()) {
        return 1;
    }

    long long minVal = (*arr)[0];
    long long maxVal = (*arr)[0];

    for (size_t i = 1; i < arr->size(); ++i) {
        minVal = (std::min)(minVal, (*arr)[i]);
        maxVal = (std::max)(maxVal, (*arr)[i]);
        Sleep(7);
    }

    g_minmax_result = { minVal, maxVal };

    std::lock_guard lock(g_console_mutex);
    std::cout << "Min = " << minVal << "\n";
    std::cout << "Max = " << maxVal << "\n";

    return 0;
}
