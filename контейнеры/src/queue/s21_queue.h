#ifndef S21_QUEUE_HEADERS
#define S21_QUEUE_HEADERS

#include <cstddef>
#include <initializer_list>
#include <iostream>

namespace s21 {
template <class T>
class queue {
 private:
  struct Node {
    T data;
    Node *next;
    Node(const T &val) : data(val), next(nullptr) {}
  };
  Node *top_;
  Node *end_;
  std::size_t size_;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &other);
  queue(queue &&other) noexcept;
  void clear();
  ~queue();

  queue &operator=(queue &&q) noexcept;
  queue &operator=(const queue &q) noexcept;

  const_reference front() const;
  const_reference back() const;
  bool empty() const;
  size_type size() const;
  void push(const_reference value);
  void pop();
  void swap(queue &other);
  void show() const;

  template <typename... Args>
  void insert_many_back(Args &&...args);
};
}  // namespace s21

#include "s21_queue.tpp"

#endif