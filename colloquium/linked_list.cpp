#include "include/linked_list.h"
#include <vector>
#include <stdexcept>
#include <iostream>

template<typename T>
void LinkedList<T>::push_back(const T& value) {
    auto new_node = std::make_unique<Node>(value);
    if (!head_) {
        head_ = std::move(new_node);
    }
    else {
        Node* current = head_.get();
        while (current->next) current = current->next.get();
        current->next = std::move(new_node);
    }
    ++size_;
}

template<typename T>
void LinkedList<T>::fill_sequential(int count) {
    if (count <= 0) {
        throw std::invalid_argument("LinkedList size must be positive");
    }

    for (int i = 1; i <= count; ++i) {
        push_back(i);
    }
}

template<typename T>
void LinkedList<T>::reverse_iterative() {
    std::unique_ptr<Node> new_head = nullptr;
    while (head_) {
        std::unique_ptr<Node> current = std::move(head_);
        head_ = std::move(current->next);
        current->next = std::move(new_head);
        new_head = std::move(current);
    }
    head_ = std::move(new_head);
}

template<typename T>
std::vector<T> LinkedList<T>::to_vector() const {
    std::vector<T> out;
    out.reserve(size_);
    Node* current = head_.get();
    while (current) {
        out.push_back(current->value);
        current = current->next.get();
    }
    return out;
}

template class LinkedList<int>;
