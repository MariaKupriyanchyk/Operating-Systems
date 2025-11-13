#pragma once
#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <vector>
#include <stdexcept>
#include <iostream>

std::vector<int> read_array_from_console();
void print_array(const std::vector<int>& arr);

#endif