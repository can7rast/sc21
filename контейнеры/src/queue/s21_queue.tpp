#include "s21_queue.h"

namespace s21 {

template <class T>
queue<T>::queue() : top_(nullptr), end_(nullptr), size_(0) {}

template <class T>
queue<T>::queue(std::initializer_list<value_type> const& items)
    : top_(nullptr), end_(nullptr), size_(0) {
  for (auto it = items.begin(); it != items.end(); it++) push(*it);
}

template <class T>
queue<T>::queue(const queue& other) : top_(nullptr), end_(nullptr), size_(0) {
  Node* iter = other.top_;
  while (iter) {
    push(iter->data);
    iter = iter->next;
  }
}

template <class T>
queue<T>::queue(queue&& other) noexcept
    : top_(other.top_), end_(other.end_), size_(other.size_) {
  other.top_ = nullptr;
  other.end_ = nullptr;
  other.size_ = 0;
}

template <class T>
void queue<T>::clear() {
  while (!empty()) pop();
}

template <class T>
queue<T>::~queue() {
  clear();
}

template <class T>
queue<T>& queue<T>::operator=(queue&& other) noexcept {
  if (this != &other) {
    clear();
    top_ = other.top_;
    end_ = other.end_;
    size_ = other.size_;

    other.top_ = nullptr;
    other.end_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <class T>
queue<T>& queue<T>::operator=(const queue& other) noexcept {
  if (this != &other) {
    clear();
    Node* iter = other.top_;
    while (iter) {
      push(iter->data);
      iter = iter->next;
    }
  }
  return *this;
}

// METHODS
template <class T>
queue<T>::const_reference queue<T>::front() const {
  if (empty()) throw std::out_of_range("queue is empty");
  return top_->data;
}

template <class T>
queue<T>::const_reference queue<T>::back() const {
  if (empty()) throw std::out_of_range("queue is empty");
  return end_->data;
}

template <class T>
bool queue<T>::empty() const {
  return top_ == nullptr;
}

template <class T>
queue<T>::size_type queue<T>::size() const {
  return size_;
}

template <class T>
void queue<T>::push(const_reference value) {
  Node* new_node = new Node(value);
  if (empty()) {
    top_ = new_node;
    end_ = new_node;
  } else {
    end_->next = new_node;
    end_ = new_node;
  }
  size_++;
}

template <class T>
void queue<T>::pop() {
  if (!empty()) {
    Node* temp_node = top_->next;
    delete top_;
    top_ = temp_node;
    if (top_ == nullptr) end_ = nullptr;
    size_--;
  }
}

template <class T>
void queue<T>::swap(queue& other) {
  Node* temp_top = top_;
  Node* temp_end = end_;
  top_ = other.top_;
  end_ = other.end_;
  other.top_ = temp_top;
  other.end_ = temp_end;

  size_type temp_size = size_;
  size_ = other.size_;
  other.size_ = temp_size;
}

template <class T>
void queue<T>::show() const {
  Node* iter = top_;
  while (iter) {
    std::cout << iter->data << " ";
    iter = iter->next;
  }
  std::cout << std::endl;
}

template <class T>
template <typename... Args>
void queue<T>::insert_many_back(Args&&... args) {
  (push(std::forward<Args>(args)), ...);
}

}  // namespace s21