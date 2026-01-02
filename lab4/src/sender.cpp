#include <iostream>
#include <string>
#include "file_queue.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Sender error: file name not provided\n";
        return 1;
    }

    FileQueue queue(argv[1]);
    queue.signal_sender_ready();

    while (true) {
        std::cout << "[Sender] Commands: 1 - send | 2 - quit\n";

        std::string cmd;
        std::getline(std::cin, cmd);

        if (cmd == "1") {
            std::cout << "Enter message (< 20 chars): ";
            std::string msg;
            std::getline(std::cin, msg);

            if (msg.empty()) {
                std::cout << "Error: message is empty\n";
                continue;
            }

            if (msg.size() > 20) {
                std::cout << "Error: message length > 20 characters\n";
                continue;
            }

            try {
                queue.push(msg);
                std::cout << "Message sent\n";
            }
            catch (const std::exception& e) {
                std::cout << "Send error: " << e.what() << "\n";
            }
        }
        else if (cmd == "2") {
            break;
        }
        else {
            std::cout << "Unknown command\n";
        }
    }

    return 0;
}
