#include <iostream>
#include <vector>
#include <string>
#include "file_queue.h"

static PROCESS_INFORMATION start_sender(const std::string& exe, const std::string& file) {
    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);

    std::string cmd = exe + " " + file;
    std::vector<char> buffer(cmd.begin(), cmd.end());
    buffer.push_back('\0');

    CreateProcessA(
        nullptr,
        buffer.data(),
        nullptr,
        nullptr,
        FALSE,
        CREATE_NEW_CONSOLE,
        nullptr,
        nullptr,
        &si,
        &pi
    );

    return pi;
}

int main() {
    std::string file;
    unsigned int capacity;
    unsigned int sender_count;

    std::cout << "Enter binary file name: ";
    std::getline(std::cin, file);

    std::cout << "Enter number of records: ";
    std::cin >> capacity;

    if (capacity == 0) {
        std::cout << "Capacity must be greater than 0\n";
        return 1;
    }

    std::cout << "Enter number of Sender processes: ";
    std::cin >> sender_count;
    std::cin.ignore();

    if (sender_count == 0) {
        std::cout << "Sender count must be greater than 0\n";
        return 1;
    }

    FileQueue queue(file, capacity);

    std::vector<PROCESS_INFORMATION> senders;
    for (unsigned int i = 0; i < sender_count; ++i)
        senders.push_back(start_sender("sender.exe", file));

    queue.wait_all_senders(sender_count);

    while (true) {
        std::cout << "[Receiver] command (read / quit): ";
        std::string cmd;
        std::getline(std::cin, cmd);

        if (cmd == "read") {
            std::string msg = queue.pop();
            std::cout << "Received message: " << msg << "\n";
        }
        else if (cmd == "quit") {
            break;
        }
        else {
            std::cout << "Unknown command\n";
        }
    }

    return 0;
}