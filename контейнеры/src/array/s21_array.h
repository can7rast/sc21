#ifndef S21_ARRAY_HEADERS
#define S21_ARRAY_HEADERS

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a);
  ~array();
  array &operator=(array &&a);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  iterator begin();
  iterator end();

  bool empty();
  size_type size() const;
  size_type max_size() const;

  void swap(array &other);
  void fill(const_reference value);

 private:
  T *data_;
  size_type size_;
};
}  // namespace s21

#include "s21_array.tpp"

#endif