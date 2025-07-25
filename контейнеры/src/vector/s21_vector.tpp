#include "s21_vector.h"

namespace s21 {

template <typename T>
vector<T>::vector() : container_(nullptr), size_(0), maxsize_(0) {}

template <typename T>
vector<T>::vector(size_type n)
    : container_(new value_type[n]), size_(n), maxsize_(n) {}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const& items) {
  container_ = new value_type[items.size()];
  size_type i = 0;
  for (const auto& item : items) container_[i++] = item;
  size_ = items.size();
  maxsize_ = items.size();
}

template <typename T>
vector<T>::vector(const vector& v)
    : container_(v.size() ? new value_type[v.size()] : nullptr),
      size_(v.size()),
      maxsize_(v.size()) {
  for (size_type i = 0; i < v.size(); i++) container_[i] = v.container_[i];
}

template <typename T>
vector<T>::vector(vector&& v)
    : container_(v.container_), size_(v.size_), maxsize_(v.maxsize_) {
  v.container_ = nullptr;
  v.size_ = 0;
  v.maxsize_ = 0;
}

template <typename T>
vector<T>::~vector() {
  delete[] container_;
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& v) {
  if (this != &v) {
    if (container_ != nullptr) delete[] container_;
    container_ = v.container_;
    size_ = v.size_;
    maxsize_ = v.maxsize_;
    v.container_ = nullptr;
    v.size_ = 0;
    v.maxsize_ = 0;
  }
  return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(const vector& other) {
  if (this != &other) {
    delete[] container_;
    size_ = other.size_;
    maxsize_ = other.maxsize_;
    container_ = (other.container_ ? new value_type[maxsize_] : nullptr);
    for (size_type i = 0; i < size_; ++i) {
      container_[i] = other.container_[i];
    }
  }
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::iterator::operator*() const {
  return *ptr_;
}

template <typename T>
typename vector<T>::pointer vector<T>::iterator::operator->() const {
  return ptr_;
}

template <typename T>
typename vector<T>::iterator& vector<T>::iterator::operator++() {
  ++ptr_;
  return *this;
}

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator++(int) {
  iterator temp = *this;
  ptr_++;
  return temp;
}

template <typename T>
typename vector<T>::iterator& vector<T>::iterator::operator+=(size_t n) {
  ptr_ += n;
  return *this;
}

template <typename T>
typename vector<T>::iterator& vector<T>::iterator::operator-=(size_t n) {
  ptr_ -= n;
  return *this;
}

template <typename T>
typename vector<T>::iterator& vector<T>::iterator::operator--() {
  --ptr_;
  return *this;
}

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator-(size_t n) const {
  iterator temp = ptr_ - n;
  return temp;
}

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator+(size_t n) const {
  iterator temp = ptr_ + n;
  return temp;
}

template <typename T>
bool vector<T>::iterator::operator==(const iterator& other) const {
  return ptr_ == other.ptr_;
}

template <typename T>
bool vector<T>::iterator::operator==(
    const typename s21::vector<T>::const_iterator& other) const {
  return ptr_ == other.ptr_;
}

template <typename T>
bool vector<T>::iterator::operator!=(const iterator& other) const {
  return ptr_ != other.ptr_;
}

template <typename T>
bool vector<T>::iterator::operator>=(const iterator& other) const {
  return ptr_ >= other.ptr_;
}

template <typename T>
bool vector<T>::iterator::operator<=(const iterator& other) const {
  return ptr_ <= other.ptr_;
}

template <typename T>
bool vector<T>::iterator::operator>(const iterator& other) const {
  return ptr_ > other.ptr_;
}

template <typename T>
bool vector<T>::iterator::operator<(const iterator& other) const {
  return ptr_ < other.ptr_;
}

template <typename T>
typename vector<T>::const_reference vector<T>::const_iterator::operator*()
    const {
  return *ptr_;
}

template <typename T>
typename vector<T>::const_pointer vector<T>::const_iterator::operator->()
    const {
  return ptr_;
}

template <typename T>
typename vector<T>::const_iterator& vector<T>::const_iterator::operator++() {
  ++ptr_;
  return *this;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator++(int) {
  const_iterator temp = *this;
  ptr_++;
  return temp;
}

template <typename T>
typename vector<T>::const_iterator& vector<T>::const_iterator::operator+=(
    size_t n) {
  ptr_ += n;
  return *this;
}

template <typename T>
typename vector<T>::const_iterator& vector<T>::const_iterator::operator-=(
    size_t n) {
  ptr_ -= n;
  return *this;
}

template <typename T>
typename vector<T>::const_iterator& vector<T>::const_iterator::operator--() {
  --ptr_;
  return *this;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator-(
    size_t n) const {
  const_iterator temp = ptr_ - n;
  return temp;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator+(
    size_t n) const {
  const_iterator temp = ptr_ + n;
  return temp;
}

template <typename T>
bool vector<T>::const_iterator::operator==(const const_iterator& other) const {
  return ptr_ == other.ptr_;
}

template <typename T>
bool vector<T>::const_iterator::operator==(
    const typename s21::vector<T>::iterator& other) const {
  return ptr_ == other.ptr_;
}

template <typename T>
bool vector<T>::const_iterator::operator!=(const const_iterator& other) const {
  return ptr_ != other.ptr_;
}

template <typename T>
bool vector<T>::const_iterator::operator>=(const const_iterator& other) const {
  return ptr_ >= other.ptr_;
}

template <typename T>
bool vector<T>::const_iterator::operator<=(const const_iterator& other) const {
  return ptr_ <= other.ptr_;
}

template <typename T>
bool vector<T>::const_iterator::operator>(const const_iterator& other) const {
  return ptr_ > other.ptr_;
}

template <typename T>
bool vector<T>::const_iterator::operator<(const const_iterator& other) const {
  return ptr_ < other.ptr_;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() const {
  return iterator(container_);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() const {
  return iterator(container_ + size_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const {
  return const_iterator(container_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() const {
  return const_iterator(container_ + size_);
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) throw out_of_range("Index out of range!");
  return *(container_ + pos);
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  if (pos >= size_) throw out_of_range("Index out of range!");
  return *(container_ + pos);
}

template <typename T>
T* vector<T>::data() {
  return container_;
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  return container_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  return container_[size_ - 1];
}

template <typename T>
bool vector<T>::empty() {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
vector<T>::size_type vector<T>::max_size() {
  return numeric_limits<size_type>::max() / sizeof(T);
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (maxsize_ < size) {
    maxsize_ = (maxsize_ == 0) ? size : maxsize_ * 2;
    if (maxsize_ < size) maxsize_ = size;
    T* temp = new value_type[maxsize_];
    for (size_type i = 0; i < size_; i++) temp[i] = container_[i];
    delete[] container_;
    container_ = temp;
  }
}

template <typename T>
vector<T>::size_type vector<T>::capacity() {
  return maxsize_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < this->capacity()) {
    T* temp = new value_type[size_];
    maxsize_ = size_;
    for (size_type i = 0; i < size_; i++) temp[i] = container_[i];
    delete[] container_;
    container_ = temp;
  }
}

template <typename T>
void vector<T>::clear() {
  delete[] container_;
  container_ = nullptr;
  size_ = 0;
  maxsize_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  if (pos > end() || pos < begin()) throw out_of_range("Incorrect iterator!");
  size_type idx = pos - begin();
  reserve(size_ + 1);
  size_ += 1;
  for (size_type i = size_; i > idx; i--) container_[i] = container_[i - 1];
  container_[idx] = value;
  return iterator(container_ + idx);
}

template <typename T>
void vector<T>::erase(iterator pos) {
  if (pos > end() || pos < begin()) throw out_of_range("Incorrect iterator!");
  size_type idx = pos - begin();
  for (; idx < size_ - 1; idx++) container_[idx] = container_[idx + 1];
  size_--;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  reserve(size_ + 1);
  container_[size_] = value;
  size_++;
}

template <typename T>
void vector<T>::pop_back() {
  size_--;
}

template <typename T>
void vector<T>::swap(vector& other) {
  using std::swap;
  swap(container_, other.container_);
  swap(size_, other.size_);
  swap(maxsize_, other.maxsize_);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  if (pos < cbegin() || pos > cend()) throw out_of_range("Incorrect iterator!");
  size_type idx = pos - cbegin();
  size_type insert_count = sizeof...(args);
  reserve(size_ + insert_count);
  for (size_type i = size_; i > idx; i--)
    container_[i + insert_count - 1] = container_[i - 1];
  size_type insert_idx = idx;
  ((container_[insert_idx++] = std::forward<Args>(args)), ...);
  size_ += sizeof...(args);
  return iterator(container_ + idx);
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args&&... args) {
  size_type idx = size_;
  reserve(size_ + sizeof...(args));
  size_ += sizeof...(args);
  ((container_[idx++] = std::forward<Args>(args)), ...);
}

}  // namespace s21