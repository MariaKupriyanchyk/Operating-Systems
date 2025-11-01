#include "include/palindrome.h"
#include <limits>

bool is_palindrome_number(long long x) noexcept {
    if (x < 0) return false;
    if (x < 10) return true;

    unsigned long long original = static_cast<unsigned long long>(x);
    unsigned long long reversed = 0;
    unsigned long long temp = original;

    while (temp != 0) {
        unsigned digit = static_cast<unsigned>(temp % 10);
        if (reversed > (std::numeric_limits<unsigned long long>::max() - digit) / 10) {
            return false;
        }
        reversed = reversed * 10 + digit;
        temp /= 10;
    }
    return reversed == original;
}