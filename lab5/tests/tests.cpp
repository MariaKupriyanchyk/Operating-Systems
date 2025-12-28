#include <gtest/gtest.h>
#include "employee.h"

TEST(EmployeeTest, NameLimit) {
    employee e{};
    strcpy_s(e.name, "123456789");
    EXPECT_EQ(strlen(e.name), 9u);
}

TEST(EmployeeTest, HoursValid) {
    employee e{};
    e.hours = 10.5;
    EXPECT_GT(e.hours, 0);
}