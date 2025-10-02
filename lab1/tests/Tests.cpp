#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <regex>
#include "../os_lab1/employee.h"

TEST(EmployeeTest, CalculateSalary) {
    employee e{ 123, "Ivan", 40.0 };
    EXPECT_DOUBLE_EQ(calculateSalary(e, 10.0), 400.0);
    EXPECT_DOUBLE_EQ(calculateSalary(e, 0.0), 0.0);
}

TEST(EmployeeValidation, ValidId) {
    std::string valid = "123";
    std::regex pattern("^[0-9]+$");
    EXPECT_TRUE(std::regex_match(valid, pattern));
    EXPECT_FALSE(std::regex_match("abc", pattern));
}

TEST(EmployeeValidation, ValidName) {
    std::string good = "Ivan";
    std::string bad = "Ivan123";
    std::regex pattern("^[A-Za-z]+$");
    EXPECT_TRUE(std::regex_match(good, pattern));
    EXPECT_FALSE(std::regex_match(bad, pattern));
}

TEST(EmployeeValidation, ValidHours) {
    std::string good1 = "10";
    std::string good2 = "12.5";
    std::string bad = "-5";
    std::regex pattern("^[0-9]+(\\.[0-9]+)?$");
    EXPECT_TRUE(std::regex_match(good1, pattern));
    EXPECT_TRUE(std::regex_match(good2, pattern));
    EXPECT_FALSE(std::regex_match(bad, pattern));
}

TEST(FileTest, CreateAndReadBinary) {
    const char* binFile = "test_employees.dat";

    {
        std::ofstream fout(binFile, std::ios::binary);
        employee e{ 1, "Ivan", 20.0 };
        fout.write(reinterpret_cast<char*>(&e), sizeof(employee));
    }

    std::ifstream fin(binFile, std::ios::binary);
    ASSERT_TRUE(fin.is_open());

    employee e;
    fin.read(reinterpret_cast<char*>(&e), sizeof(employee));

    EXPECT_EQ(e.num, 1);
    EXPECT_STREQ(e.name, "Ivan");
    EXPECT_DOUBLE_EQ(e.hours, 20.0);

    fin.close();
    std::remove(binFile);
}

TEST(FileTest, CreateTextReport) {
    const char* txtFile = "report.txt";

    {
        std::ofstream fout(txtFile);
        ASSERT_TRUE(fout.is_open());
        fout << "Report test\n";
    }

    std::ifstream fin(txtFile);
    ASSERT_TRUE(fin.is_open());

    std::string header;
    std::getline(fin, header);
    EXPECT_EQ(header, "Report test");

    fin.close();
    std::remove(txtFile);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}