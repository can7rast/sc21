#ifndef S21_STACK_HEADERS
#define S21_STACK_HEADERS

#include <cstddef>
#include <initializer_list>
#include <iostream>

namespace s21 {
template <class T>
class stack {
 private:
  struct Node {
    T data;
    Node *next;
    Node(const T &val, Node *nxt = nullptr) : data(val), next(nxt) {}
  };
  Node *top_;
  std::size_t size_;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &other);
  stack(stack &&other) noexcept;
  void clear();
  ~stack();

  stack &operator=(stack &&other) noexcept;
  stack &operator=(const stack &other) noexcept;

  const_reference top() const;
  bool empty() const;
  size_type size() const;
  void push(const_reference value);
  void pop();
  void swap(stack &other);
  void show() const;

  template <typename... Args>
  void insert_many_back(Args &&...args);
};
}  // namespace s21

#include "s21_stack.tpp"

#endif