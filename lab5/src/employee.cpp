#include "employee.h"
#include <iostream>
#include <regex>
#include <iomanip>

void input_id(int& id) {
    while (true) {
        std::cin >> id;

        if (std::cin.fail() || id <= 0) {
            std::cout << "Invalid ID. Try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}

void input_name(char name[10]) {
    while (true) {
        std::cin >> std::setw(10) >> name;

        bool overflow = false;
        if (!std::cin.fail() && std::cin.peek() != '\n') {
            overflow = true;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        bool ok = true;
        int len = std::strlen(name);

        if (len == 0 || len > 9 || overflow)
            ok = false;

        for (int i = 0; i < len && ok; ++i) {
            if (!std::isalpha(static_cast<unsigned char>(name[i])))
                ok = false;
        }

        if (!ok) {
            std::cout << "Name (letters only, <=9 chars): ";
        }
        else {
            break;
        }
    }
}

void input_hours(double& hours) {
    while (true) {
        std::cin >> hours;

        if (std::cin.fail() || hours < 0) {
            std::cout << "Invalid hours. Try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}

void input_employee(employee& emp) {
    std::cout << "ID: ";
    while (!read_int(emp.num) || emp.num <= 0) {
        std::cout << "Invalid ID. Try again: ";
    }

    std::cout << "Name (letters only, <=9 chars): ";
    input_name(emp.name);

    std::cout << "Hours: ";
    while (!read_double(emp.hours) || emp.hours < 0) {
        std::cout << "Invalid hours. Try again: ";
    }
}

void input_employee_update(employee& emp) {
    std::cout << "Name (letters only, <=9 chars): ";
    input_name(emp.name);

    std::cout << "Hours: ";
    while (!read_double(emp.hours) || emp.hours < 0) {
        std::cout << "Invalid hours. Try again: ";
    }
}

bool read_int(int& value) {
    std::string line;
    std::getline(std::cin, line);

    static const std::regex int_regex(R"(^(0|[1-9]\d*)$)");

    if (!std::regex_match(line, int_regex))
        return false;

    try {
        value = std::stoi(line);
    }
    catch (...) {
        return false;
    }

    return true;
}

bool read_double(double& value) {
    std::string line;
    std::getline(std::cin, line);

    static const std::regex double_regex(
        R"(^(0|[1-9]\d*)(\.\d+)?$)"
    );

    if (!std::regex_match(line, double_regex))
        return false;

    try {
        value = std::stod(line);
    }
    catch (...) {
        return false;
    }

    return true;
}