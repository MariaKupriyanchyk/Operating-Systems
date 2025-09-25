#pragma once
struct employee
{
	int num;
	char name[10];
	double hours;
};

void printEmployee(const employee& e, double payRate);
double calculateSalary(const employee& e, double payRate);