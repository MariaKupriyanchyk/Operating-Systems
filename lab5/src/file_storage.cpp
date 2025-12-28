#include <iostream>
#include "file_storage.h"
#include "pipe_protocol.h"
#include "employee.h"

FileStorage::FileStorage(const std::string& file)
    : file_name_(file) {
    mutex_ = CreateMutexA(nullptr, FALSE, nullptr);
}

employee FileStorage::read_by_id(int id, bool& found) {
    WaitForSingleObject(mutex_, INFINITE);

    employee emp{};
    found = false;

    HANDLE file = CreateFileA(
        file_name_.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (file == INVALID_HANDLE_VALUE) {
        ReleaseMutex(mutex_);
        return emp;
    }

    DWORD read;
    while (ReadFile(file, &emp, sizeof(emp), &read, nullptr) && read == sizeof(emp)) {
        if (emp.num == id) {
            found = true;
            break;
        }
    }

    CloseHandle(file);
    ReleaseMutex(mutex_);
    return emp;
}

bool FileStorage::write_by_id(const employee& emp) {
    WaitForSingleObject(mutex_, INFINITE);

    HANDLE file = CreateFileA(
        file_name_.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (file == INVALID_HANDLE_VALUE) {
        ReleaseMutex(mutex_);
        return false;
    }

    DWORD read;
    employee cur{};
    while (ReadFile(file, &cur, sizeof(cur), &read, nullptr) && read == sizeof(cur)) {
        if (cur.num == emp.num) {
            SetFilePointer(file, -static_cast<LONG>(sizeof(cur)), nullptr, FILE_CURRENT);
            DWORD written;
            WriteFile(file, &emp, sizeof(emp), &written, nullptr);
            CloseHandle(file);
            ReleaseMutex(mutex_);
            return true;
        }
    }

    CloseHandle(file);
    ReleaseMutex(mutex_);
    return false;
}

void FileStorage::print_all() {
    HANDLE file = CreateFileA(
        file_name_.c_str(),
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

int FileStorage::size() const {
    HANDLE file = CreateFileA(
        file_name_.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (file == INVALID_HANDLE_VALUE)
        return 0;

    LARGE_INTEGER sz{};
    GetFileSizeEx(file, &sz);
    CloseHandle(file);

    return static_cast<int>(sz.QuadPart / sizeof(employee));
}