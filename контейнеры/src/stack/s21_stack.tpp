#include "s21_stack.h"

namespace s21 {

template <class T>
stack<T>::stack() : top_(nullptr), size_(0) {}

template <class T>
stack<T>::stack(std::initializer_list<value_type> const &items)
    : top_(nullptr), size_(0) {
  for (auto it = items.end() - 1; it != items.begin() - 1; it--) push(*it);
}

template <class T>
stack<T>::stack(const stack &other) : top_(nullptr), size_(0) {
  Node *temp_top = other.top_;
  stack<T> temp_stack;

  while (temp_top) {
    temp_stack.push(temp_top->data);
    temp_top = temp_top->next;
  }

  while (!temp_stack.empty()) {
    push(temp_stack.top());
    temp_stack.pop();
  }
}

template <class T>
stack<T>::stack(stack &&other) noexcept : top_(other.top_), size_(other.size_) {
  other.top_ = nullptr;
  other.size_ = 0;
}

template <class T>
void stack<T>::clear() {
  while (!empty()) pop();
}

template <class T>
stack<T>::~stack() {
  clear();
}

template <class T>
stack<T> &stack<T>::operator=(stack &&other) noexcept {
  if (this != &other) {
    clear();
    top_ = other.top_;
    size_ = other.size_;
    other.top_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <class T>
stack<T> &stack<T>::operator=(const stack<T> &other) noexcept {
  if (this != &other) {
    clear();
    Node *temp_top = other.top_;
    stack<T> temp_stack;

    while (temp_top) {
      temp_stack.push(temp_top->data);
      temp_top = temp_top->next;
    }

    while (!temp_stack.empty()) {
      push(temp_stack.top());
      temp_stack.pop();
    }
  }
  return *this;
}

// METHODS
template <class T>
stack<T>::const_reference stack<T>::top() const {
  if (empty()) throw std::out_of_range("stack is empty");
  return top_->data;
}

template <class T>
bool stack<T>::empty() const {
  return top_ == nullptr;
}

template <class T>
stack<T>::size_type stack<T>::size() const {
  return size_;
}

template <class T>
void stack<T>::push(const_reference value) {
  top_ = new Node(value, top_);
  size_++;
}

template <class T>
void stack<T>::pop() {
  if (!empty()) {
    Node *temp = top_->next;
    delete top_;
    top_ = temp;
    size_--;
  }
}

template <class T>
void stack<T>::swap(stack &other) {
  Node *temp = top_;
  top_ = other.top_;
  other.top_ = temp;

  size_type temp_size = size_;
  size_ = other.size_;
  other.size_ = temp_size;
}

template <class T>
void stack<T>::show() const {
  Node *i = top_;
  while (i) {
    std::cout << i->data << " ";
    i = i->next;
  }
  std::cout << std::endl;
}

template <class T>
template <typename... Args>
void stack<T>::insert_many_back(Args &&...args) {
  (push(std::forward<Args>(args)), ...);
}

}  // namespace s21