#include "s21_set.h"
namespace s21 {  // логика строится на реализации авл из мэпа
template <typename Key>
set<Key>::set() : tree_() {}

template <typename Key>
set<Key>::~set() {}

template <typename Key>
set<Key>::set(const set &other) : tree_(other.tree_) {}

template <typename Key>
bool set<Key>::empty() {
  return tree_.empty();
}

template <typename Key>
typename set<Key>::size_type set<Key>::size() {
  return tree_.size();
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() {
  return tree_.max_size();
}

template <typename Key>
typename set<Key>::iterator set<Key>::begin() {
  return tree_.begin();
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() {
  return tree_.end();
}

template <typename Key>
void set<Key>::clear() {
  tree_.clear();
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type &value) {
  return tree_.insert({value, value});
}

template <typename Key>
void set<Key>::erase(iterator pos) {
  tree_.erase(pos);
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key &key) {
  return tree_.find(key);
}

template <typename Key>
bool set<Key>::contains(const Key &key) {
  return tree_.contains(key);
}

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const &items) {
  for (const auto &item : items) {
    insert(item);
  }
}

template <typename Key>
set<Key> &set<Key>::operator=(const set &other) {
  if (this != &other) {
    tree_ = other.tree_;
  }
  return *this;
}

template <typename Key>
set<Key>::set(set &&other) noexcept : tree_(std::move(other.tree_)) {}

template <typename Key>
set<Key> &set<Key>::operator=(set &&other) {
  if (this != &other) {
    tree_ = std::move(other.tree_);
  }
  return *this;
}

template <typename Key>
void set<Key>::swap(set &other) {
  tree_.swap(other.tree_);
}

template <typename Key>
void set<Key>::merge(set &other) {
  if (this == &other) {
    return;
  }

  std::vector<Key> keys_to_move;
  for (const auto &key : other) {
    if (this->insert(key.first).second) {
      keys_to_move.push_back(key.first);
    }
  }
  for (const auto &key : keys_to_move) {
    other.erase(other.find(key));
  }
}

template <typename Key>
template <typename... Args>
std::vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args &&...args) {
  std::vector<std::pair<iterator, bool>> res;
  (res.push_back(insert(std::forward<Args>(args))), ...);
  return res;
}
}  // namespace s21
