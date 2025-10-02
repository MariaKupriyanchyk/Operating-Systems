#pragma once
struct employee
{
	int num;
	char name[10];
	double hours;
};

double calculateSalary(const employee& e, double payRate);

int getValidId();
void getValidName(char* name);
double getValidHours();
