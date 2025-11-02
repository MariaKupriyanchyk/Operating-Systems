#include "include/fibonacci.h"
#include <vector>
#include <stdexcept>
#include <iostream>

std::vector<unsigned long long> first_n_fibonacci(int n) {
    if (n <= 0) {
        throw std::invalid_argument("n must be >= 1");
    }

    std::vector<unsigned long long> result;
    result.reserve(n);

    result.push_back(1);
    if (n == 1) {
        return result;
    }

    result.push_back(1);
    for (size_t i = 2; i < n; ++i) {
        unsigned long long first_num = result[i - 2];
        unsigned long long second_num = result[i - 1];
        if (first_num > ULLONG_MAX - second_num) {
            throw std::overflow_error("Fibonacci overflow for requested n");
        }
        result.push_back(first_num + second_num);
    }
    return result;
}

int read_positive_int() {
    int n;
    std::cin >> n;
    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Input must be a valid integer");
    }
    if (n <= 0) {
        throw std::invalid_argument("Number must be positive");
    }
    return n;
}
