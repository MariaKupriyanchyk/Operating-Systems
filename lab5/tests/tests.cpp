#include <gtest/gtest.h>
#include "employee.h"
#include <sstream>
#include <cstring>

class CinRedirect {
public:
    CinRedirect(std::istream& new_input)
        : old(std::cin.rdbuf(new_input.rdbuf())) {}
    ~CinRedirect() {
        std::cin.rdbuf(old);
    }
private:
    std::streambuf* old;
};

//employee struct
TEST(EmployeeStructTest, AssignValues) {
    employee e{};
    e.num = 1;
    strcpy_s(e.name, "Ivan");
    e.hours = 12.5;

    EXPECT_EQ(e.num, 1);
    EXPECT_STREQ(e.name, "Ivan");
    EXPECT_DOUBLE_EQ(e.hours, 12.5);
}

//read_int
TEST(ReadIntTest, ValidInt) {
    std::istringstream input("123\n");
    CinRedirect redirect(input);

    int value = 0;
    EXPECT_TRUE(read_int(value));
    EXPECT_EQ(value, 123);
}

TEST(ReadIntTest, RejectLetters) {
    std::istringstream input("abc\n");
    CinRedirect redirect(input);

    int value = 0;
    EXPECT_FALSE(read_int(value));
}

TEST(ReadIntTest, RejectExpression) {
    std::istringstream input("2/1\n");
    CinRedirect redirect(input);

    int value = 0;
    EXPECT_FALSE(read_int(value));
}

TEST(ReadIntTest, RejectNegative) {
    std::istringstream input("-5\n");
    CinRedirect redirect(input);

    int value = 0;
    EXPECT_FALSE(read_int(value));
}

//read_double
TEST(ReadDoubleTest, ValidInteger) {
    std::istringstream input("10\n");
    CinRedirect redirect(input);

    double value = 0;
    EXPECT_TRUE(read_double(value));
    EXPECT_DOUBLE_EQ(value, 10.0);
}

TEST(ReadDoubleTest, ValidFraction) {
    std::istringstream input("10.5\n");
    CinRedirect redirect(input);

    double value = 0;
    EXPECT_TRUE(read_double(value));
    EXPECT_DOUBLE_EQ(value, 10.5);
}

TEST(ReadDoubleTest, RejectLetters) {
    std::istringstream input("abc\n");
    CinRedirect redirect(input);

    double value = 0;
    EXPECT_FALSE(read_double(value));
}

TEST(ReadDoubleTest, RejectExpression) {
    std::istringstream input("2/1\n");
    CinRedirect redirect(input);

    double value = 0;
    EXPECT_FALSE(read_double(value));
}

TEST(ReadDoubleTest, RejectNegative) {
    std::istringstream input("-3\n");
    CinRedirect redirect(input);

    double value = 0;
    EXPECT_FALSE(read_double(value));
}

//input_name
TEST(InputNameTest, ValidName) {
    std::istringstream input("Ivan\n");
    CinRedirect redirect(input);

    char name[10]{};
    input_name(name);

    EXPECT_STREQ(name, "Ivan");
}

TEST(InputNameTest, RejectDigitsThenAccept) {
    std::istringstream input("Ivan123\nVasya\n");
    CinRedirect redirect(input);

    char name[10]{};
    input_name(name);

    EXPECT_STREQ(name, "Vasya");
}

TEST(InputNameTest, RejectTooLongThenAccept) {
    std::istringstream input("VeryLongName\nAnya\n");
    CinRedirect redirect(input);

    char name[10]{};
    input_name(name);

    EXPECT_STREQ(name, "Anya");
}

//input_hours
TEST(InputHoursTest, ValidHours) {
    std::istringstream input("10.5\n");
    CinRedirect redirect(input);

    double hours = 0;
    input_hours(hours);

    EXPECT_DOUBLE_EQ(hours, 10.5);
}

TEST(InputHoursTest, RejectInvalidThenAccept) {
    std::istringstream input("abc\n-3\n5\n");
    CinRedirect redirect(input);

    double hours = 0;
    input_hours(hours);

    EXPECT_DOUBLE_EQ(hours, 5.0);
}

//input_employee
TEST(InputEmployeeTest, FullEmployeeInput) {
    std::istringstream input(
        "2\n"
        "Ivan\n"
        "8.5\n"
    );
    CinRedirect redirect(input);

    employee e{};
    input_employee(e);

    EXPECT_EQ(e.num, 2);
    EXPECT_STREQ(e.name, "Ivan");
    EXPECT_DOUBLE_EQ(e.hours, 8.5);
}
