#include <windows.h>
#include <iostream>
#include "file_storage.h"

FileStorage::FileStorage(const std::string& filename)
    : filename_(filename) {}

employee FileStorage::read_by_id(int id, bool& found) {
    found = false;

    HANDLE file = CreateFileA(
        filename_.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (file == INVALID_HANDLE_VALUE)
        return {};

    employee emp{};
    DWORD read;

    while (ReadFile(file, &emp, sizeof(emp), &read, nullptr) && read == sizeof(emp)) {
        if (emp.num == id) {
            found = true;
            CloseHandle(file);
            return emp;
        }
    }

    CloseHandle(file);
    return {};
}

bool FileStorage::write_by_id(int id, const employee& updated) {
    HANDLE file = CreateFileA(
        filename_.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (file == INVALID_HANDLE_VALUE)
        return false;

    employee current{};
    DWORD read;
    DWORD pos = 0;

    while (ReadFile(file, &current, sizeof(current), &read, nullptr) && read == sizeof(current)) {
        if (current.num == id) {
            employee to_write = updated;
            to_write.num = id;

            SetFilePointer(file, pos, nullptr, FILE_BEGIN);

            DWORD written;
            WriteFile(file, &to_write, sizeof(to_write), &written, nullptr);
            CloseHandle(file);
            return written == sizeof(to_write);
        }
        pos += sizeof(employee);
    }

    CloseHandle(file);
    return false;
}

bool FileStorage::write_by_id(const employee& updated) {
    return write_by_id(updated.num, updated);
}

void FileStorage::print_all() {
    HANDLE file = CreateFileA(
        filename_.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (file == INVALID_HANDLE_VALUE)
        return;

    employee emp{};
    DWORD read;

    while (ReadFile(file, &emp, sizeof(emp), &read, nullptr) && read == sizeof(emp)) {
        std::cout << emp.num << " | " << emp.name << " | " << emp.hours << "\n";
    }

    CloseHandle(file);
}
