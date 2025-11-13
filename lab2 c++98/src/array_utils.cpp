#include "../include/array_utils.h"

std::vector<int> read_array_from_console() {
    int n;
    std::cout << "Enter number of elements: ";
    if (!(std::cin >> n) || n <= 0) {
        throw std::invalid_argument("Invalid array size");
    }

    std::vector<int> arr(n);
    std::cout << "Enter " << n << " integers:\n";
    for (size_t i = 0; i < arr.size(); ++i) {
        if (!(std::cin >> arr[i])) {
            throw std::invalid_argument("Invalid input");
        }
    }

    return arr;
}

void print_array(const std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}