#include "../include/file_queue.h"
#include <stdexcept>
#include <cstring>

static HANDLE open_mutex(const std::string& name) {
    HANDLE h = CreateMutexA(nullptr, FALSE, name.c_str());
    if (!h) throw std::runtime_error("Mutex error");
    return h;
}

static HANDLE open_semaphore(const std::string& name, int init, int max) {
    HANDLE h = CreateSemaphoreA(nullptr, init, max, name.c_str());
    if (!h) throw std::runtime_error("Semaphore error");
    return h;
}

FileQueue::FileQueue(const std::string& file_name, unsigned int capacity)
    : file_(INVALID_HANDLE_VALUE), file_name_(file_name) {

    file_ = CreateFileA(
        file_name.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (file_ == INVALID_HANDLE_VALUE)
        throw std::runtime_error("File create failed");

    LARGE_INTEGER size;
    size.QuadPart = sizeof(QueueHeader) + capacity * sizeof(QueueSlot);
    SetFilePointerEx(file_, size, nullptr, FILE_BEGIN);
    SetEndOfFile(file_);

    QueueHeader header{};
    header.capacity = capacity;
    write_header(header);

    mutex_ = open_mutex("Global\\fq_mutex_" + file_name);
    sem_empty_ = open_semaphore("Global\\fq_empty_" + file_name, capacity, capacity);
    sem_full_ = open_semaphore("Global\\fq_full_" + file_name, 0, capacity);
}

FileQueue::FileQueue(const std::string& file_name)
    : file_(INVALID_HANDLE_VALUE), file_name_(file_name) {

    file_ = CreateFileA(
        file_name.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (file_ == INVALID_HANDLE_VALUE)
        throw std::runtime_error("File open failed");

    QueueHeader header{};
    read_header(header);

    mutex_ = open_mutex("Global\\fq_mutex_" + file_name);
    sem_empty_ = open_semaphore("Global\\fq_empty_" + file_name, header.capacity, header.capacity);
    sem_full_ = open_semaphore("Global\\fq_full_" + file_name, 0, header.capacity);
}

FileQueue::~FileQueue() {
    CloseHandle(file_);
    CloseHandle(mutex_);
    CloseHandle(sem_empty_);
    CloseHandle(sem_full_);
}

void FileQueue::lock() { WaitForSingleObject(mutex_, INFINITE); }
void FileQueue::unlock() { ReleaseMutex(mutex_); }

void FileQueue::read_header(QueueHeader& header) {
    DWORD read;
    SetFilePointer(file_, 0, nullptr, FILE_BEGIN);
    ReadFile(file_, &header, sizeof(header), &read, nullptr);
}

void FileQueue::write_header(const QueueHeader& header) {
    DWORD written;
    SetFilePointer(file_, 0, nullptr, FILE_BEGIN);
    WriteFile(file_, &header, sizeof(header), &written, nullptr);
}

void FileQueue::write_slot(unsigned int index, const QueueSlot& slot) {
    DWORD written;
    SetFilePointer(file_, sizeof(QueueHeader) + index * sizeof(QueueSlot), nullptr, FILE_BEGIN);
    WriteFile(file_, &slot, sizeof(slot), &written, nullptr);
}

FileQueue::QueueSlot FileQueue::read_slot(unsigned int index) {
    QueueSlot slot{};
    DWORD read;
    SetFilePointer(file_, sizeof(QueueHeader) + index * sizeof(QueueSlot), nullptr, FILE_BEGIN);
    ReadFile(file_, &slot, sizeof(slot), &read, nullptr);
    return slot;
}

void FileQueue::push(const std::string& message) {
    if (message.empty())
        throw std::runtime_error("Empty message is not allowed");

    if (message.size() > 20)
        throw std::runtime_error("Message length exceeds 20 characters");

    WaitForSingleObject(sem_empty_, INFINITE);
    lock();

    QueueHeader header{};
    read_header(header);

    QueueSlot slot{};
    memset(slot.text, 0, sizeof(slot.text));
    strncpy_s(slot.text, message.c_str(), 20);

    write_slot(header.tail, slot);

    header.tail = (header.tail + 1) % header.capacity;
    header.count++;
    write_header(header);

    unlock();
    ReleaseSemaphore(sem_full_, 1, nullptr);
}

std::string FileQueue::pop() {
    WaitForSingleObject(sem_full_, INFINITE);
    lock();

    QueueHeader header{};
    read_header(header);

    QueueSlot slot = read_slot(header.head);
    header.head = (header.head + 1) % header.capacity;
    header.count--;
    write_header(header);

    unlock();
    ReleaseSemaphore(sem_empty_, 1, nullptr);

    return std::string(slot.text);
}

void FileQueue::signal_sender_ready() {
    lock();
    QueueHeader header{};
    read_header(header);
    header.ready_senders++;
    write_header(header);
    unlock();
}

void FileQueue::wait_all_senders(unsigned int expected) {
    while (true) {
        lock();
        QueueHeader header{};
        read_header(header);
        unsigned int ready = header.ready_senders;
        unlock();
        if (ready >= expected) break;
        Sleep(50);
    }
}