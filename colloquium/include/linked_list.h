#pragma once
#include <memory>
#include <vector>

template<typename T>
class LinkedList {
public:
    struct Node {
        T value;
        std::unique_ptr<Node> next;
        explicit Node(T v) : value(std::move(v)), next(nullptr) {}
    };

    LinkedList() = default;
    ~LinkedList() = default;

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    void push_back(const T& value);
    void fill_sequential(int count);
    void reverse_iterative();
    std::vector<T> to_vector() const;
    std::size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

private:
    std::unique_ptr<Node> head_{ nullptr };
    std::size_t size_{ 0 };
};
