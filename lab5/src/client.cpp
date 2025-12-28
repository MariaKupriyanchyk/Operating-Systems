#include <windows.h>
#include <iostream>
#include <string>
#include "pipe_protocol.h"
#include "employee.h"

static const char* PIPE_NAME = "\\\\.\\pipe\\EmployeePipe";

int main() {
    while (true) {
        std::cout << "\n1 - read\n2 - modify\n3 - exit\n> ";
        int cmd;
        std::cin >> cmd;
        std::cin.ignore();

        if (cmd == 3)
            break;

        PipeRequest req{};
        req.type = (cmd == 1) ? REQ_READ : REQ_WRITE;

        std::cout << "Enter ID: ";
        std::cin >> req.employee_id;
        std::cin.ignore();

        if (cmd == 2) {
            req.data.num = req.employee_id;

            std::cout << "New name (<=9 chars): ";
            std::string name;
            std::getline(std::cin, name);
            if (name.size() > 9) name = name.substr(0, 9);
            strcpy_s(req.data.name, name.c_str());

            std::cout << "New hours: ";
            std::cin >> req.data.hours;
            std::cin.ignore();
        }

        HANDLE pipe = CreateFileA(
            PIPE_NAME,
            GENERIC_READ | GENERIC_WRITE,
            0,
            nullptr,
            OPEN_EXISTING,
            0,
            nullptr
        );

        if (pipe == INVALID_HANDLE_VALUE) {
            std::cout << "Server not available\n";
            continue;
        }

        DWORD written;
        WriteFile(pipe, &req, sizeof(req), &written, nullptr);

        PipeResponse resp{};
        DWORD read;
        ReadFile(pipe, &resp, sizeof(resp), &read, nullptr);

        if (!resp.success) {
            std::cout << "Server error\n";
        }
        else {
            std::cout << "Employee: "
                << resp.data.num << " "
                << resp.data.name << " "
                << resp.data.hours << "\n";
        }

        CloseHandle(pipe);
    }

    return 0;
}