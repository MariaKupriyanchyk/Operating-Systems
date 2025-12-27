#pragma once
#include <windows.h>
#include <string>

class FileQueue {
public:
    FileQueue(const std::string& file_name, unsigned int capacity);
    FileQueue(const std::string& file_name);
    ~FileQueue();

    void push(const std::string& message);
    std::string pop();

    void signal_sender_ready();
    void wait_all_senders(unsigned int expected);

private:
    struct QueueHeader {
        unsigned int capacity;
        unsigned int head;
        unsigned int tail;
        unsigned int count;
        unsigned int ready_senders;
    };

    struct QueueSlot {
        char text[21];
    };

    HANDLE file_;
    HANDLE mutex_;
    HANDLE sem_empty_;
    HANDLE sem_full_;
    std::string file_name_;

    void read_header(QueueHeader& header);
    void write_header(const QueueHeader& header);
    void write_slot(unsigned int index, const QueueSlot& slot);
    QueueSlot read_slot(unsigned int index);

    void lock();
    void unlock();
};