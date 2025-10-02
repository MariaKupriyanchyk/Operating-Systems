#include <iostream>
#include <fstream>
#include <iomanip>
#include "employee.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: Reporter <input_bin> <output_txt> <pay_rate>\n";
        return 1;
    }

    const char* binaryFile = argv[1];
    const char* txtFile = argv[2];
    double payRate = atof(argv[3]);

    ifstream fin(binaryFile, ios::binary);
    ofstream fout(txtFile);

    if (!fin || !fout) {
        cerr << "Error opening file\n";
        return 1;
    }

    fout << "Report " << binaryFile << "\n";
    fout << "ID\tName\tHours\tSalary\n";

    employee e;
    while (fin.read(reinterpret_cast<char*>(&e), sizeof(employee))) {
        double salary = calculateSalary(e, payRate);
        fout << e.num << "\t" << e.name << "\t" << e.hours << "\t" << salary << "\n";
    }

    fin.close();
    fout.close();

    return 0;
}
