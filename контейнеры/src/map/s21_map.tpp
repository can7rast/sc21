#pragma once
#include <stdexcept>
#include <vector>

#include "avl.hpp"
#include "s21_map.h"

namespace s21 {

// --- Реализация конструкторов и деструктора ---

// Конструктор по умолчанию
template <typename Key, typename T> map<Key, T>::map() : tree_() {}

// Конструктор со списком инициализации
template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const &items) : tree_() {
  for (const auto &item : items) {
    insert(item);
  }
}

// Конструктор копирования
template <typename Key, typename T>
map<Key, T>::map(const map &m) : tree_(m.tree_) {}

// Конструктор перемещения
template <typename Key, typename T>
map<Key, T>::map(map &&m) : tree_(std::move(m.tree_)) {}

// Деструктор
template <typename Key, typename T> map<Key, T>::~map() { clear(); }

// Оператор перемещающего присваивания
template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(map &&m) {
  if (this != &m) {
    clear();
    tree_ = std::move(m.tree_);
  }
  return *this;
}

// --- Доступ к элементам ---

template <typename Key, typename T> T &map<Key, T>::at(const Key &key) {
  return tree_.at(key);
}

// Доступ к значению по ключу, создаёт элемент по умолчанию, если не найден
template <typename Key, typename T> T &map<Key, T>::operator[](const Key &key) {
  return tree_[key];
}

// --- Итераторы ---

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  return iterator(tree_.begin());
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  return iterator(tree_.end());
}

// --- Методы для работы с размером и состоянием контейнера ---

// Проверка на пустоту
template <typename Key, typename T> bool map<Key, T>::empty() {
  return tree_.empty();
}

// Количество элементов
template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() {
  return tree_.size();
}

// Максимально возможное количество элементов
template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::max_size() {
  return tree_.max_size();
}

// Константный итератор на первый элемент
template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::cbegin() const {
  return const_iterator(tree_.cbegin());
}

// Константный итератор на элемент после последнего
template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::cend() const {
  return const_iterator(tree_.cend());
}

// --- Модификаторы ---

// Очистка контейнера
template <typename Key, typename T> void map<Key, T>::clear() { tree_.clear(); }

// Вставка пары ключ-значение
template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert(const value_type &value) {
  auto result = tree_.insert(value);
  return std::make_pair(iterator(result.first), result.second);
}

// Вставка по ключу и значению
template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert(const Key &key, const T &obj) {
  return insert(std::make_pair(key, obj));
}

// Вставка или присваивание значения по ключу
template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert_or_assign(const Key &key, const T &obj) {
  auto it = tree_.find(key);
  if (it != tree_.end()) {
    (*it).second = obj;
    return std::make_pair(iterator(it), false);
  } else {
    return insert(std::make_pair(key, obj));
  }
}

// Удаление элемента по итератору
template <typename Key, typename T> void map<Key, T>::erase(iterator pos) {
  tree_.erase(pos.it_);
}

// Обмен содержимым с другим map
template <typename Key, typename T> void map<Key, T>::swap(map &other) {
  tree_.swap(other.tree_);
}

// Перемещение элементов из другого map
template <typename Key, typename T> void map<Key, T>::merge(map &other) {
  auto it = other.begin();
  while (it != other.end()) {
    auto next_it = it;
    ++next_it;
    auto result = insert(*it);
    if (result.second) {
      other.erase(it);
    }
    it = next_it;
  }
}

// Проверка наличия ключа
template <typename Key, typename T> bool map<Key, T>::contains(const Key &key) {
  return tree_.contains(key);
}

// Вставка нескольких элементов сразу (parameter pack)
template <typename Key, typename T>
template <typename... Args>
std::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> results;
  // резервируем память для вектора результатов
  results.reserve(sizeof...(args));
  // лямбда функция для вставки одного элемента
  auto insert_single = [this, &results](const value_type &value) {
    auto result = insert(value);
    results.push_back(result);
  };

  (insert_single(std::forward<Args>(args)), ...);

  return results;
}

// --- Реализация MapIterator ---

// Конструктор по умолчанию
template <typename Key, typename T>
map<Key, T>::MapIterator::MapIterator() : it_() {}

// Конструктор из итератора AVLTree
template <typename Key, typename T>
map<Key, T>::MapIterator::MapIterator(typename AVLTree<Key, T>::Iterator it)
    : it_(it) {}

// Разыменование итератора
template <typename Key, typename T>
typename map<Key, T>::reference map<Key, T>::MapIterator::operator*() {
  return *it_;
}

// Доступ к члену пары
template <typename Key, typename T>
typename map<Key, T>::value_type *map<Key, T>::MapIterator::operator->() {
  return &(*it_);
}

// Префиксный инкремент
template <typename Key, typename T>
typename map<Key, T>::MapIterator &map<Key, T>::MapIterator::operator++() {
  ++it_;
  return *this;
}

// Постфиксный инкремент
template <typename Key, typename T>
typename map<Key, T>::MapIterator map<Key, T>::MapIterator::operator++(int) {
  MapIterator tmp = *this;
  ++it_;
  return tmp;
}

// Префиксный декремент
template <typename Key, typename T>
typename map<Key, T>::MapIterator &map<Key, T>::MapIterator::operator--() {
  --it_;
  return *this;
}

// Постфиксный декремент
template <typename Key, typename T>
typename map<Key, T>::MapIterator map<Key, T>::MapIterator::operator--(int) {
  MapIterator tmp = *this;
  --it_;
  return tmp;
}

// Операторы сравнения
template <typename Key, typename T>
bool map<Key, T>::MapIterator::operator==(const MapIterator &other) const {
  return it_ == other.it_;
}

template <typename Key, typename T>
bool map<Key, T>::MapIterator::operator!=(const MapIterator &other) const {
  return !(*this == other);
}

// --- Реализация ConstMapIterator ---

// Конструктор по умолчанию
template <typename Key, typename T>
map<Key, T>::ConstMapIterator::ConstMapIterator() : it_() {}

// Конструктор из константного итератора AVLTree
template <typename Key, typename T>
map<Key, T>::ConstMapIterator::ConstMapIterator(
    typename AVLTree<Key, T>::ConstIterator it)
    : it_(it) {}

// Конструктор из обычного итератора
template <typename Key, typename T>
map<Key, T>::ConstMapIterator::ConstMapIterator(const MapIterator &it)
    : it_(it.it_) {}

// Разыменование итератора
template <typename Key, typename T>
typename map<Key, T>::const_reference
map<Key, T>::ConstMapIterator::operator*() const {
  return *it_;
}

// Доступ к члену пары
template <typename Key, typename T>
const typename map<Key, T>::value_type *
map<Key, T>::ConstMapIterator::operator->() const {
  return &(*it_);
}

// Префиксный инкремент
template <typename Key, typename T>
typename map<Key, T>::ConstMapIterator &
map<Key, T>::ConstMapIterator::operator++() {
  ++it_;
  return *this;
}

// Постфиксный инкремент
template <typename Key, typename T>
typename map<Key, T>::ConstMapIterator
map<Key, T>::ConstMapIterator::operator++(int) {
  ConstMapIterator tmp = *this;
  ++it_;
  return tmp;
}

// Префиксный декремент
template <typename Key, typename T>
typename map<Key, T>::ConstMapIterator &
map<Key, T>::ConstMapIterator::operator--() {
  --it_;
  return *this;
}

// Постфиксный декремент
template <typename Key, typename T>
typename map<Key, T>::ConstMapIterator
map<Key, T>::ConstMapIterator::operator--(int) {
  ConstMapIterator tmp = *this;
  --it_;
  return tmp;
}

// Операторы сравнения
template <typename Key, typename T>
bool map<Key, T>::ConstMapIterator::operator==(
    const ConstMapIterator &other) const {
  return it_ == other.it_;
}

template <typename Key, typename T>
bool map<Key, T>::ConstMapIterator::operator!=(
    const ConstMapIterator &other) const {
  return !(*this == other);
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::find(const Key &key) {
  return iterator(tree_.find(key));
}

} // namespace s21