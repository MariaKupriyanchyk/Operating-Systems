#include "marker_manager.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

void MarkerManager::sleep_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

MarkerManager::MarkerManager(int size) {
    array_ = std::make_shared<SharedArray>(size);
}

MarkerManager::~MarkerManager() {
    join_all();
}

void MarkerManager::launch(int count) {
    for (int i = 0; i < count; ++i)
        markers_.push_back(std::make_unique<Marker>());

    for (int i = 0; i < count; ++i)
        markers_[i]->th = std::thread(&MarkerManager::worker, this, i + 1);
}

void MarkerManager::start_all() {
    {
        std::lock_guard<std::mutex> lock(start_mtx_);
        started_ = true;
    }
    start_cv_.notify_all();
}

void MarkerManager::worker(int id) {
    srand(static_cast<unsigned>(id));

    {
        std::unique_lock<std::mutex> lock(start_mtx_);
        start_cv_.wait(lock, [&] { return started_.load(); });
    }

    while (true) {
        if (markers_[id - 1]->stop) break;

        int index = rand() % array_->size();

        if (array_->get(index) == 0) {
            sleep_ms(5);
            if (array_->try_mark(index, static_cast<int>(id))) {
                sleep_ms(5);
                continue;
            }
        }

        std::cout << "Marker " << id
            << " blocked, marked "
            << array_->count_by_id(static_cast<int>(id))
            << ", index = " << index << std::endl;

        markers_[id - 1]->waiting = true;
        ctrl_cv_.notify_one();

        std::unique_lock<std::mutex> lock(markers_[id - 1]->mtx);
        markers_[id - 1]->cv.wait(lock, [&] {
            return markers_[id - 1]->stop ||
                !markers_[id - 1]->waiting.load();
            });
    }

    array_->clear_by_id(static_cast<int>(id));
    markers_[id - 1]->alive = false;
    ctrl_cv_.notify_one();
}

void MarkerManager::wait_all_blocked() {
    std::unique_lock<std::mutex> lock(ctrl_mtx_);
    ctrl_cv_.wait(lock, [&] {
        int alive = 0;
        int waiting = 0;
        for (auto& m : markers_) {
            if (m->alive) {
                ++alive;
                if (m->waiting) ++waiting;
            }
        }
        return alive > 0 && alive == waiting;
        });
}

void MarkerManager::terminate(int id) {
    auto& m = markers_[id - 1];
    m->stop = true;
    m->cv.notify_one();
    if (m->th.joinable()) m->th.join();
}

void MarkerManager::resume_all() {
    for (auto& m : markers_) {
        if (m->waiting && m->alive) {
            m->waiting = false;
            m->cv.notify_one();
        }
    }
}

bool MarkerManager::any_alive() const {
    for (auto& m : markers_)
        if (m->alive) return true;
    return false;
}

void MarkerManager::join_all() {
    for (auto& m : markers_) {
        m->stop = true;
        m->cv.notify_one();
    }
    for (auto& m : markers_)
        if (m->th.joinable()) m->th.join();
}

void MarkerManager::print() const {
    auto snap = array_->snapshot();
    for (int i = 0; i < snap.size(); ++i)
        std::cout << snap[i] << " ";
    std::cout << std::endl;
}