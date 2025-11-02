#include <iostream>
#include "include/fibonacci.h"
#include "include/palindrome.h"
#include "include/linked_list.h"

int main() {
    try {
        //Fibonacci
        std::cout << "Enter the first n elements of the Fibonacci numbers:\n";
        int num_first_fibonacci = read_positive_int();

        std::cout << "Fibonacci sequence (first " << num_first_fibonacci << "): ";

        auto fib = first_n_fibonacci(num_first_fibonacci);
        for (auto x : fib) {
            std::cout << x << " ";
        }
        std::cout << "\n";

        //Palindrome
        std::cout << "Enter a number to check it for a palindrome:\n";
        std::string numb_check_palindrome;
        std::cin >> numb_check_palindrome;

        if (is_palindrome_number(numb_check_palindrome)) {
            std::cout << numb_check_palindrome << " is a palindrome\n";
        }
        else {
            std::cout << numb_check_palindrome << " is not a palindrome\n";
        }

        //Linked List
        std::cout << "Enter number of elements for linked list:\n";
        int num_linked_list = read_positive_int();

        LinkedList<int> list;
        list.fill_sequential(num_linked_list);
        list.reverse_iterative();

        std::cout << "Reversed list: ";
        for (auto x : list.to_vector()) {
            std::cout << x << " ";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
