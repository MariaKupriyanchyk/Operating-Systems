#pragma once
#include <memory>
#include <vector>
#include <cstddef>

template<typename T>
class SinglyLinkedList {
public:
    struct Node {
        T value;
        std::unique_ptr<Node> next;
        explicit Node(T v) : value(std::move(v)), next(nullptr) {}
    };

    SinglyLinkedList() noexcept = default;
    ~SinglyLinkedList() = default;

    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    void push_back(const T& value);
    void reverse_iterative() noexcept;
    std::vector<T> to_vector() const;
    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }

private:
    std::unique_ptr<Node> head_{ nullptr };
    std::size_t size_{ 0 };
};