#include "employee.h"
#include <iomanip>
#include <iostream>
#include <regex>

double calculateSalary(const employee& e, double payRate) {
	return e.hours * payRate;
}

int getValidId() {
    std::string input;
    std::regex rgx("^[0-9]+$");
    while (true) {
        std::cout << "ID: ";
        std::cin >> input;
        if (std::regex_match(input, rgx)) {
            return std::stoi(input);
        }
        else {
            std::cout << "Invalid ID. Only digits allowed.\n";
        }
    }
}

void getValidName(char* name) {
    std::string input;
    std::regex pattern("^[A-Za-z]{1,9}$");
    while (true) {
        std::cout << "Name: ";
        std::cin >> input;
        if (std::regex_match(input, pattern)) {
            std::strncpy(name, input.c_str(), 9);
            name[9] = '\0';
            return;
        }
        else {
            std::cout << "Invalid name. Only letters (max 9).\n";
        }
    }
}

double getValidHours() {
    std::string input;
    std::regex rgx("^[0-9]+(\\.[0-9]+)?$");
    while (true) {
        std::cout << "Hours: ";
        std::cin >> input;
        if (std::regex_match(input, rgx)) {
            double val = std::stod(input);
            if (val >= 0) return val;
        }
        std::cout << "Invalid hours. Must be non-negative number.\n";
    }
}
