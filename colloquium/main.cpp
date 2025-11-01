#include <iostream>
#include "include/fibonacci.h"
#include "include/palindrome.h"
#include "include/linked_list.h"

int main() {
    try {
        std::cout << "Fibonacci sequence (first 10): ";
        auto fib = first_n_fibonacci(10);
        for (auto x : fib) std::cout << x << " ";
        std::cout << "\n";

        long long num = 12321;
        std::cout << "Is " << num << " a palindrome? "
            << (is_palindrome_number(num) ? "Yes" : "No") << "\n";

        SinglyLinkedList<int> list;
        for (int i = 1; i <= 5; ++i) list.push_back(i);
        list.reverse_iterative();

        std::cout << "Reversed list: ";
        for (auto x : list.to_vector()) std::cout << x << " ";
        std::cout << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}