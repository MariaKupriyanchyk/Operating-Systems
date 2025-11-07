#pragma once
#include <windows.h>

class ThreadGuard {
public:
    explicit ThreadGuard(HANDLE handle) : handle_(handle) {}
    ~ThreadGuard() {
        if (handle_) CloseHandle(handle_);
    }

    ThreadGuard(const ThreadGuard&) = delete;
    ThreadGuard& operator=(const ThreadGuard&) = delete;
    ThreadGuard(ThreadGuard&& other) : handle_(other.handle_) {
        other.handle_ = nullptr;
    }
    ThreadGuard& operator=(ThreadGuard&& other) {
        if (this != &other) {
            if (handle_) CloseHandle(handle_);
            handle_ = other.handle_;
            other.handle_ = nullptr;
        }
        return *this;
    }

    [[nodiscard]] HANDLE get() const { return handle_; }

private:
    HANDLE handle_{ nullptr };
};
