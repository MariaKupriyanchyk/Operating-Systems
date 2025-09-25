#include <iostream>
#include <fstream>
#include <cstring>
#include "employee.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: Creator <filename> <count>\n";
		return 1;
	}

	const char* filename = argv[1];
	int count = atoi(argv[2]);

	ofstream fout(filename, ios::binary);
	if (!fout) {
		cerr << "Error: cannot open file\n";
		return 1;
	}

	for (int i = 0; i < count; i++) {
		employee e;
		cout << "Enter employee #" << (i + 1) << ":\n";
		cout << "ID: "; cin >> e.num;
		cout << "Name: "; cin >> e.name;
		cout << "Hours: "; cin >> e.hours;

		fout.write(reinterpret_cast<char*>(&e), sizeof(employee));
	}

	fout.close();

	return 0;
}