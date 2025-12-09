#pragma once
#include "shared_array.h"
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <memory>

class MarkerManager {
public:
    explicit MarkerManager(int size);
    ~MarkerManager();

    void launch(int count);
    void start_all();
    void wait_all_blocked();
    void terminate(int id);
    void resume_all();
    bool any_alive() const;
    void join_all();
    void print() const;

private:
    struct Marker {
        std::thread th;
        std::atomic<bool> waiting{ false };
        std::atomic<bool> stop{ false };
        std::atomic<bool> alive{ true };
        std::mutex mtx;
        std::condition_variable cv;
    };

    void worker(int id);
    static void sleep_ms(int ms);

    std::shared_ptr<SharedArray> array_;
    std::vector<std::unique_ptr<Marker>> markers_;

    std::mutex ctrl_mtx_;
    std::condition_variable ctrl_cv_;

    std::atomic<bool> started_{ false };
    std::mutex start_mtx_;
    std::condition_variable start_cv_;
};