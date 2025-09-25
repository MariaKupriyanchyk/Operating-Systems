#include "employee.h"
#include <iomanip>
#include <iostream>

void printEmployee(const employee& e, double payRate) {
	double salary = calculateSalary(e, payRate);

	std::cout << "ID: " << e.num << "\t";
	std::cout << "Name: " << e.name << "\t";
	std::cout << "Hours: " << e.hours << "\t";
	std::cout << "Salary: " << salary << "\n";
}

double calculateSalary(const employee& e, double payRate) {
	return e.hours * payRate;
}