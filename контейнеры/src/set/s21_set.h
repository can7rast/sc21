#ifndef S21_SET_HEADERS
#define S21_SET_HEADERS

#include <utility>
#include <vector>

#include "../map/avl.hpp"
namespace s21 {
template <typename Key>
class set {
 private:
  AVLTree<Key, Key> tree_;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const Key &;
  using iterator = typename AVLTree<Key, Key>::Iterator;
  using const_iterator = typename AVLTree<Key, Key>::ConstIterator;
  using size_type = std::size_t;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &other);
  set(set &&other) noexcept;
  set &operator=(set &&other);
  set &operator=(const set &other);
  ~set();

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  iterator find(const Key &key);
  bool contains(const Key &key);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};
}  // namespace s21

#include "s21_set.tpp"

#endif