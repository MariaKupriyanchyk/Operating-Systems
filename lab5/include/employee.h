#pragma once
#include <string>
#include <iostream>

struct employee {
    int num;
    char name[10];
    double hours;
};

void input_id(int& id);
void input_name(char name[10]);
void input_hours(double& hours);
void input_employee(employee& emp);
void input_employee_update(employee& emp);

bool read_int(int& value);
bool read_double(double& value);
