//
// Created by sashka on 19.10.18.
//

#ifndef LINKED_LIST_LINKEDLIST_H
#define LINKED_LIST_LINKEDLIST_H


#include <vector>
#include <cassert>

template <typename T>
class LinkedList {
 public:
  LinkedList() {
    head_ = nullptr;
    size_ = 0;
  }

  explicit LinkedList(std::vector<T>& init_values) {
    head_ = nullptr;
    for (int i = (int)init_values.size() - 1; i >= 0; i--) {
      Node* new_node = new Node(init_values[i]);
      Node* prior_head = head_;
      head_ = new_node;
      head_->next = prior_head;
    }
    size_ = init_values.size();
  }

  ~LinkedList() {
    Node* cur_head = head_;
    Node* next;

    while (cur_head != nullptr) {
      next = cur_head->next;
      delete cur_head;
      cur_head = next;
    }
  }

  void PushFront(T&& new_value) {
    InsertNth(0, new_value);
  }

  void PushBack(T&& new_value) {
    InsertNth(size(), new_value);
  }

  T NthElement(size_t index) {
    assert(index >= 0);
    assert(index < size_);

    return NthPointer(index, head_)->value;
  }

  void InsertNth(size_t index, T value) {
    assert(index >= 0);
    assert(index <= size_);

    Node* new_node = new Node(value);

    if (index == 0) {
      new_node->next = head_;
      head_ = new_node;
    } else {
      Node* prev = NthPointer(index - 1, head_);
      Node* next = prev->next;
      new_node->next = next;
      prev->next = new_node;
    }
    size_++;
  }

  void DeleteNth(size_t index) {
    assert(index >= 0);
    assert(index < size_);

    if (index == 0) {
      Node* cur = head_;
      head_ = head_->next;
      delete cur;
    } else {
      Node* prev = NthPointer(index - 1, head_);
      Node* cur = prev->next;
      Node* next = cur->next;

      prev->next = next;
      delete cur;
    }
    size_--;
  }

  void ReverseRecursive() {
    head_ = ReverseRecursive_(head_).second;
  }

  void ReverseDivideAndConquer() {
    head_ = DivideConquer(head_, NthPointer(size_ - 1, head_), size_).first;
  }

  size_t size() {
    return size_;
  }

 private:

  struct Node;

  std::pair<Node*,Node*> ReverseRecursive_(Node* starting) {
    if(starting->next == nullptr) {
      return {starting, starting};
    }

    std::pair<Node*,Node*> ans = ReverseRecursive_(starting->next);
    ans.first->next = starting;
    starting->next = nullptr;
    return {starting, ans.second};
  }

  std::pair<Node*, Node*> DivideConquer(Node* starting, Node* ending, size_t cur_size) {
    if (starting == ending) {
      return {starting, starting};
    }

    if (starting->next == ending) {
      ending->next = starting;
      starting->next = nullptr;
      return {ending, starting};
    }

    size_t mid_index = cur_size / 2;
    size_t left_size = mid_index + 1;
    size_t right_size = cur_size - left_size;

    Node* mid = NthPointer(mid_index, starting);
    Node* next_mid = mid->next;
    std::pair<Node*, Node*> rev_left = DivideConquer(starting, mid, left_size);
    std::pair<Node*, Node*> rev_right = DivideConquer(next_mid, ending, right_size);
    rev_right.second->next = rev_left.first;
    return {rev_right.first, rev_left.second};
  }

  Node* NthPointer(size_t index, Node* start) {
    assert(index >= 0);
    assert(index < size_);

    Node* cur_node = start;
    size_t cur = 0;
    while (cur < index) {
      ++cur;
      cur_node = cur_node->next;
    }

    return cur_node;
  }

  struct Node {
    T value;
    Node* next;

    Node (T& value_init) :
        value(value_init),
        next(nullptr)
    {}
  };

  Node* head_;
  size_t size_;
};

#endif //LINKED_LIST_LINKEDLIST_H
