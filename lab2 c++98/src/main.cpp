#define NOMINMAX

#include "../include/array_utils.h"
#include "../include/min_max_thread.h"
#include "../include/average_thread.h"

#include <windows.h>
#include <iostream>
#include <stdexcept>

extern CRITICAL_SECTION g_console_cs;

int main() {
    try {
        InitializeCriticalSection(&g_console_cs);

        std::vector<int> arr = read_array_from_console();

        HANDLE hMinMax = CreateThread(NULL, 0, find_min_max, &arr, 0, NULL);
        HANDLE hAverage = CreateThread(NULL, 0, find_average, &arr, 0, NULL);

        if (hMinMax == NULL || hAverage == NULL) {
            throw std::runtime_error("Failed to create threads");
        }

        WaitForSingleObject(hMinMax, INFINITE);
        WaitForSingleObject(hAverage, INFINITE);

        CloseHandle(hMinMax);
        CloseHandle(hAverage);

        std::cout << std::endl << "All threads completed." << std::endl;

        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i] == g_minmax_result.min || arr[i] == g_minmax_result.max) {
                arr[i] = static_cast<int>(g_avg_result.value);
            }
        }

        std::cout << "Array after replacement: ";
        print_array(arr);

        DeleteCriticalSection(&g_console_cs);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}