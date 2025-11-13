#include "../include/array_utils.h"
#include "../include/min_max_thread.h"
#include "../include/average_thread.h"

#include <windows.h>
#include <iostream>
#include <numeric>
#include <algorithm>

int main() {
    try {
        auto arr = read_array_from_console();

        HANDLE hMinMax = CreateThread(nullptr, 0, find_min_max, &arr, 0, nullptr);
        HANDLE hAverage = CreateThread(nullptr, 0, find_average, &arr, 0, nullptr);

        if (!hMinMax || !hAverage)
            throw std::runtime_error("Failed to create threads");

        WaitForSingleObject(hMinMax, INFINITE);
        WaitForSingleObject(hAverage, INFINITE);

        CloseHandle(hMinMax);
        CloseHandle(hAverage);

        std::cout << "\nAll threads completed.\n";

        for (auto& value : arr) {
            if (value == g_minmax_result.min || value == g_minmax_result.max)
                value = static_cast<int>(g_avg_result.value);
        }

        std::cout << "Array after replacement: ";
        print_array(arr);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
