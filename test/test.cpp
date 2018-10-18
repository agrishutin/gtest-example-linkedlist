//
// Created by sashka on 19.10.18.
//

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE testLinkedList

#include "../src/LinkedList.h"
#include <gtest/gtest.h>

TEST(LinkedList, EmptySize) {
  LinkedList<int> list = LinkedList<int> ();
  EXPECT_EQ(list.size(), 0);
}

TEST(LinkedList, VectorConstructor) {
  std::vector<int> nums = {1, 2, 3};
  LinkedList<int> list = LinkedList<int>(nums);

  EXPECT_EQ(list.size(), nums.size());
  EXPECT_EQ(list.NthElement(0), 1);
  EXPECT_EQ(list.NthElement(1), 2);
  EXPECT_EQ(list.NthElement(2), 3);
}