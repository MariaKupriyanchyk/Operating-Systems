#include "include/palindrome.h"
#include <limits>
#include <string>
#include <stdexcept>

bool is_palindrome_number(const std::string& input) {
    if (input.empty()) {
        throw std::invalid_argument("Input cannot be empty");
    }

    for (char c : input) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            throw std::invalid_argument("Input contains non-digit characters");
        }
    }

    int left = 0;
    int right = static_cast<int>(input.size()) - 1;
    while (left < right) {
        if (input[left] != input[right]) return false;
        ++left;
        --right;
    }
    return true;
}
