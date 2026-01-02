#include <windows.h>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "file_storage.h"
#include "pipe_protocol.h"
#include "employee.h"

static const char* PIPE_NAME = "\\\\.\\pipe\\EmployeePipe";
static std::unordered_map<int, bool> write_locked;
std::unordered_set<int> used_ids;

int main() {
    std::string file;
    int count;

    std::cout << "Enter binary file name: ";
    std::getline(std::cin, file);

    std::cout << "Enter number of employees: ";
    while (!read_int(count) || count <= 0) {
        std::cout << "Invalid number. Try again: ";
    }

    if (count <= 0) {
        std::cout << "Invalid count\n";
        return 1;
    }

    HANDLE f = CreateFileA(
        file.c_str(), GENERIC_WRITE, 0,
        nullptr, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, nullptr
    );

    if (f == INVALID_HANDLE_VALUE) {
        std::cout << "File error\n";
        return 1;
    }

    for (int i = 0; i < count; ) {
        employee emp{};
        input_employee(emp);

        if (used_ids.count(emp.num)) {
            std::cout << "Employee with this ID already exists. Try again.\n";
            continue;
        }

        used_ids.insert(emp.num);

        DWORD written;
        WriteFile(f, &emp, sizeof(emp), &written, nullptr);
        ++i;
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
        512, 512, 0, nullptr
    );

    std::cout << "\nServer started, waiting for clients...\n";

    while (true) {
        ConnectNamedPipe(pipe, nullptr);

        while (true) {
            PipeRequest req{};
            DWORD read;

            if (!ReadFile(pipe, &req, sizeof(req), &read, nullptr) || read == 0)
                break;

            PipeResponse resp{};
            resp.success = 1;

            if (req.type == REQ_READ) {
                bool found;
                resp.data = storage.read_by_id(req.employee_id, found);
                if (!found) resp.success = 0;
            }

            else if (req.type == REQ_MODIFY_BEGIN) {
                if (write_locked[req.employee_id]) {
                    resp.success = 0;
                }
                else {
                    bool found;
                    resp.data = storage.read_by_id(req.employee_id, found);
                    if (!found)
                        resp.success = 0;
                    else
                        write_locked[req.employee_id] = true;
                }
            }

            else if (req.type == REQ_MODIFY_COMMIT) {
                if (!write_locked[req.data.num] ||
                    !storage.write_by_id(req.data)) {
                    resp.success = 0;
                }
            }

            else if (req.type == REQ_RELEASE) {
                write_locked[req.employee_id] = false;
            }

            else if (req.type == REQ_EXIT) {
                DisconnectNamedPipe(pipe);
                continue;
            }

            DWORD written;
            WriteFile(pipe, &resp, sizeof(resp), &written, nullptr);
        }

        DisconnectNamedPipe(pipe);
    }
}
