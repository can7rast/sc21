#include "s21_array.h"

namespace s21 {

template <typename T>
array<T>::array() : data_(nullptr), size_(0) {}

template <typename T>
array<T>::array(std::initializer_list<value_type> const &items) {
  data_ = new value_type[items.size()];
  size_type i = 0;
  for (const auto &item : items) data_[i++] = item;
  size_ = items.size();
}

template <typename T>
array<T>::array(const array &a) {
  size_ = a.size();
  data_ = new value_type[size_];
  for (size_type i = 0; i < size_; ++i) data_[i] = a.data_[i];
}

template <typename T>
array<T>::array(array &&a) {
  data_ = a.data_;
  size_ = a.size_;
  a.data_ = nullptr;
  a.size_ = 0;
}

template <typename T>
array<T>::~array() {
  if (data_ != nullptr) delete[] data_;
  size_ = 0;
}

template <typename T>
array<T> &array<T>::operator=(array &&a) {
  if (this != &a) {
    if (data_ != nullptr) delete[] data_;
    data_ = a.data_;
    size_ = a.size_;
    a.data_ = nullptr;
    a.size_ = 0;
  }
  return *this;
}

template <typename T>
array<T>::reference array<T>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range("Index out of range!");
  return data_[pos];
}

template <typename T>
array<T>::reference array<T>::operator[](size_type pos) {
  if (pos >= size_) throw std::out_of_range("Index out of range!");
  return data_[pos];
}

template <typename T>
array<T>::const_reference array<T>::front() {
  if (size_ == 0) throw std::out_of_range("Array is empty");
  return *data_;
}

template <typename T>
array<T>::const_reference array<T>::back() {
  if (size_ == 0) throw std::out_of_range("Array is empty");
  return *(data_ + size_ - 1);
}

template <typename T>
array<T>::iterator array<T>::data() {
  return data_;
}

template <typename T>
array<T>::iterator array<T>::begin() {
  return data_;
}

template <typename T>
array<T>::iterator array<T>::end() {
  return data_ + size_;
}

template <typename T>
bool array<T>::empty() {
  return data_ == nullptr;
}

template <typename T>
array<T>::size_type array<T>::size() const {
  return size_;
}

template <typename T>
array<T>::size_type array<T>::max_size() const {
  return size_;
}

template <typename T>
void array<T>::swap(array &other) {
  if (size_ != other.size_) throw std::out_of_range("Arrays of unequal size");
  std::swap(size_, other.size_);
  std::swap(data_, other.data_);
}

template <typename T>
void array<T>::fill(const_reference value) {
  if (size_ == 0) throw std::out_of_range("Array is empty");
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = value;
  }
}

}  // namespace s21