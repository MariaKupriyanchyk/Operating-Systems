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
        if (!read_int(cmd) || cmd < 1 || cmd > 3) {
            std::cout << "Invalid command. Enter 1, 2 or 3.\n";
            continue;
        }

        if (cmd == 3) {
            PipeRequest req{};
            req.type = REQ_EXIT;

            HANDLE pipe = CreateFileA(
                PIPE_NAME,
                GENERIC_WRITE,
                0, nullptr,
                OPEN_EXISTING,
                0, nullptr
            );

            if (pipe != INVALID_HANDLE_VALUE) {
                DWORD written;
                WriteFile(pipe, &req, sizeof(req), &written, nullptr);
                CloseHandle(pipe);
            }
            break;
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

        if (cmd == 1) {
            PipeRequest req{};
            req.type = REQ_READ;

            std::cout << "ID: ";
            if (!read_int(req.employee_id) || req.employee_id <= 0) {
                std::cout << "Invalid ID\n";
                CloseHandle(pipe);
                continue;
            }

            DWORD written;
            WriteFile(pipe, &req, sizeof(req), &written, nullptr);

            PipeResponse resp{};
            DWORD read;
            ReadFile(pipe, &resp, sizeof(resp), &read, nullptr);

            if (!resp.success)
                std::cout << "Server error\n";
            else
                std::cout << "Employee: "
                << resp.data.num << " "
                << resp.data.name << " "
                << resp.data.hours << "\n";
        }

        else if (cmd == 2) {
            int id;
            std::cout << "ID: ";
            if (!read_int(id) || id <= 0) {
                std::cout << "Invalid ID\n";
                CloseHandle(pipe);
                continue;
            }

            PipeRequest begin{};
            begin.type = REQ_MODIFY_BEGIN;
            begin.employee_id = id;

            DWORD written;
            WriteFile(pipe, &begin, sizeof(begin), &written, nullptr);

            PipeResponse resp{};
            DWORD read;
            ReadFile(pipe, &resp, sizeof(resp), &read, nullptr);

            if (!resp.success) {
                std::cout << "Server error\n";
                CloseHandle(pipe);
                continue;
            }

            std::cout << "Current: Employee: "
                << resp.data.num << " "
                << resp.data.name << " "
                << resp.data.hours << "\n";

            employee updated{};
            updated.num = id;

            input_employee_update(updated);

            PipeRequest commit{};
            commit.type = REQ_MODIFY_COMMIT;
            commit.data = updated;

            WriteFile(pipe, &commit, sizeof(commit), &written, nullptr);
            ReadFile(pipe, &resp, sizeof(resp), &read, nullptr);

            if (!resp.success)
                std::cout << "Update failed\n";
            else
                std::cout << "Updated successfully\n";

            PipeRequest release{};
            release.type = REQ_RELEASE;
            release.employee_id = id;

            WriteFile(pipe, &release, sizeof(release), &written, nullptr);
        }

        CloseHandle(pipe);
    }

    return 0;
}
