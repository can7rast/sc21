#ifndef S21_VECTOR_HEADERS
#define S21_VECTOR_HEADERS

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>

using namespace std;

namespace s21 {
template <typename T>
class vector {
 public:
  class iterator;
  class const_iterator;
  T* container_;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;
  using size_type = std::size_t;
  size_type size_;
  size_type maxsize_;

  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& v);
  vector(vector&& v);
  ~vector();
  vector& operator=(vector&& v);
  vector<T>& operator=(const vector& other);

  class iterator {
   public:
    T* ptr_;
    iterator(T* ptr = nullptr) : ptr_(ptr) {};
    reference operator*() const;
    pointer operator->() const;
    iterator& operator++();
    iterator operator++(int);
    iterator& operator+=(size_t n);
    iterator& operator-=(size_t n);
    iterator& operator--();
    iterator operator+(size_type n) const;
    iterator operator-(size_type n) const;
    friend size_type operator-(const iterator& lhs, const iterator& rhs) {
      return lhs.ptr_ - rhs.ptr_;
    }
    bool operator==(const iterator& other) const;
    bool operator==(const typename s21::vector<T>::const_iterator& other) const;
    bool operator!=(const iterator& other) const;
    bool operator<=(const iterator& other) const;
    bool operator>=(const iterator& other) const;
    bool operator>(const iterator& other) const;
    bool operator<(const iterator& other) const;
  };

  class const_iterator {
   public:
    const T* ptr_;
    const_iterator(const T* ptr = nullptr) : ptr_(ptr) {};
    const_reference operator*() const;
    const_pointer operator->() const;
    const_iterator& operator++();
    const_iterator operator++(int);
    const_iterator& operator+=(size_t n);
    const_iterator& operator-=(size_t n);
    const_iterator& operator--();
    const_iterator operator+(size_type n) const;
    const_iterator operator-(size_type n) const;
    friend size_type operator-(const const_iterator& lhs,
                               const const_iterator& rhs) {
      return lhs.ptr_ - rhs.ptr_;
    }
    bool operator==(const const_iterator& other) const;
    bool operator==(const typename s21::vector<T>::iterator& other) const;
    bool operator!=(const const_iterator& other) const;
    bool operator<=(const const_iterator& other) const;
    bool operator>=(const const_iterator& other) const;
    bool operator>(const const_iterator& other) const;
    bool operator<(const const_iterator& other) const;
  };

  iterator begin() const;
  iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T* data();

  bool empty();
  size_type size() const;
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
};
}  // namespace s21

#include "s21_vector.tpp"

#endif