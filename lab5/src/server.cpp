#include <windows.h>
#include <iostream>
#include <vector>
#include "file_storage.h"
#include "pipe_protocol.h"
#include "employee.h"

static const char* PIPE_NAME = "\\\\.\\pipe\\EmployeePipe";

int main() {
    std::string file;
    int count;

    std::cout << "Enter binary file name: ";
    std::getline(std::cin, file);

    std::cout << "Enter number of employees: ";
    std::cin >> count;
    std::cin.ignore();

    if (count <= 0) {
        std::cout << "Invalid count\n";
        return 1;
    }

    HANDLE f = CreateFileA(
        file.c_str(),
        GENERIC_WRITE,
        0,
        nullptr,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (f == INVALID_HANDLE_VALUE) {
        std::cout << "File error\n";
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        employee emp{};
        std::cout << "ID: ";
        std::cin >> emp.num;
        std::cin.ignore();

        std::cout << "Name (<=9 chars): ";
        std::string name;
        std::getline(std::cin, name);
        if (name.size() > 9) name = name.substr(0, 9);
        strcpy_s(emp.name, name.c_str());

        std::cout << "Hours: ";
        std::cin >> emp.hours;
        std::cin.ignore();

        DWORD written;
        WriteFile(f, &emp, sizeof(emp), &written, nullptr);
    }

    CloseHandle(f);

    FileStorage storage(file);
    std::cout << "\nInitial file:\n";
    storage.print_all();

    HANDLE pipe = CreateNamedPipeA(
        PIPE_NAME,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        512, 512,
        0,
        nullptr
    );

    std::cout << "\nServer started, waiting for clients...\n";

    while (true) {
        ConnectNamedPipe(pipe, nullptr);

        PipeRequest req{};
        DWORD read;
        ReadFile(pipe, &req, sizeof(req), &read, nullptr);

        PipeResponse resp{};
        resp.success = 1;

        if (req.type == REQ_READ) {
            bool found;
            resp.data = storage.read_by_id(req.employee_id, found);
            if (!found) {
                resp.success = 0;
                //strcpy_s(resp.message, "Record not found");
            }
        }
        else if (req.type == REQ_WRITE) {
            if (!storage.write_by_id(req.data)) {
                resp.success = 0;
                //strcpy_s(resp.message, "Write failed");
            }
        }
        else if (req.type == REQ_EXIT) {
            DisconnectNamedPipe(pipe);
            break;
        }

        DWORD written;
        WriteFile(pipe, &resp, sizeof(resp), &written, nullptr);
        DisconnectNamedPipe(pipe);
    }

    std::cout << "\nFinal file:\n";
    storage.print_all();

    CloseHandle(pipe);
    return 0;
}