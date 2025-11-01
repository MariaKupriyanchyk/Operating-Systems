#include "include/fibonacci.h"
#include <limits>
#include <vector>
#include <stdexcept>

std::vector<std::uint64_t> first_n_fibonacci(std::size_t n) {
    if (n == 0) {
        throw std::invalid_argument("n must be >= 1");
    }

    std::vector<std::uint64_t> result;
    result.reserve(n);

    const auto MAX = std::numeric_limits<std::uint64_t>::max();

    result.push_back(1);
    if (n == 1) return result;

    result.push_back(1);
    for (std::size_t i = 2; i < n; ++i) {
        std::uint64_t a = result[i - 2];
        std::uint64_t b = result[i - 1];
        if (a > MAX - b) {
            throw std::overflow_error("Fibonacci overflow for requested n");
        }
        result.push_back(a + b);
    }
    return result;
}