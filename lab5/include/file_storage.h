#pragma once
#include <string>
#include <vector>
#include <windows.h>
#include "pipe_protocol.h"

class FileStorage {
public:
    FileStorage(const std::string& file);

    employee read_by_id(int id, bool& found);
    bool write_by_id(const employee& emp);

    void print_all();
    int size() const;

private:
    std::string file_name_;
    HANDLE mutex_;
};