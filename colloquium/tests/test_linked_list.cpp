#include "linked_list.h"
#include <gtest/gtest.h>
#include <vector>

TEST(LinkedListTests, PushBackAndReverse) {
    SinglyLinkedList<int> list;
    for (int i = 1; i <= 4; ++i) list.push_back(i);
    list.reverse_iterative();
    EXPECT_EQ(list.to_vector(), std::vector<int>({ 4,3,2,1 }));
}

TEST(LinkedListTests, EmptyList) {
    SinglyLinkedList<int> list;
    list.reverse_iterative();
    EXPECT_TRUE(list.empty());
}