#pragma once
#include <string>
#include "pipe_protocol.h"

class FileStorage {
public:
    FileStorage(const std::string& filename);

    employee read_by_id(int id, bool& found);
    bool write_by_id(int id, const employee& updated);
    bool write_by_id(const employee& updated);
    void print_all();

private:
    std::string filename_;
};
