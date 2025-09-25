#include <iostream>
#include <windows.h>
#include <fstream>
#include "employee.h"
#include <string>
#include <vector>

using namespace std;

int main() {
	string binaryFile, reportFile;
	int count;
	double payRate;

	cout << "Enter binary filename: ";
    cin >> binaryFile;
    cout << "Enter number of employees: ";
    cin >> count;

    //Creator
	string creatorCmd = string("Creator.exe") + " " + binaryFile + " " + to_string(count);
    vector<char> cmd1(creatorCmd.begin(), creatorCmd.end());
    cmd1.push_back('\0');

	STARTUPINFOA si1;
    ZeroMemory(&si1, sizeof(si1));
    si1.cb = sizeof(si1);
	PROCESS_INFORMATION pi1;
    ZeroMemory(&pi1, sizeof(pi1));

    if (!CreateProcessA(NULL, cmd1.data(), NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1)) {
        cerr << "Error launching Creator\n";
        return 1;
    }

    WaitForSingleObject(pi1.hProcess, INFINITE);
    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);

    ifstream fin(binaryFile, ios::binary);
    employee e;
    cout << "\nBinary file contents:\n";
    while (fin.read(reinterpret_cast<char*>(&e), sizeof(employee))) {
        cout << e.num << " " << e.name << " " << e.hours << endl;
    }
    fin.close();

    //Reporter
    cout << "\nEnter report filename: ";
    cin >> reportFile;
    cout << "Enter pay per hour: ";
    cin >> payRate;

    string reporterCmd = string("Reporter.exe") + " " + binaryFile + " " + reportFile + " " + to_string(payRate);
    vector<char> cmd2(reporterCmd.begin(), reporterCmd.end());
    cmd2.push_back('\0');

    STARTUPINFOA si2;
    ZeroMemory(&si2, sizeof(si2));
    si2.cb = sizeof(si2);
    PROCESS_INFORMATION pi2;
    ZeroMemory(&pi2, sizeof(pi2));

    if (!CreateProcessA(NULL, cmd2.data(), NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2)) {
        cerr << "Error launching Reporter\n";
        return 1;
    }

    WaitForSingleObject(pi2.hProcess, INFINITE);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);

    ifstream freport(reportFile);
    string line;
    cout << "\nReport file contents:\n";
    while (getline(freport, line)) {
        cout << line << endl;
    }
    freport.close();

    return 0;
}