#pragma once
#include <algorithm>
#include <stdexcept>

#include "avl.hpp"

namespace s21 {

// Конструкторы и деструктор
// Конструктор по умолчанию, создает пустое дерево
template <typename Key, typename T, typename Compare>
AVLTree<Key, T, Compare>::AVLTree() noexcept : root_(nullptr), size_(0) {}

// Деструктор, освобождает всю память
template <typename Key, typename T, typename Compare>
AVLTree<Key, T, Compare>::~AVLTree() {
  clear();
}

// Конструктор копирования, создает глубокую копию дерева
template <typename Key, typename T, typename Compare>
AVLTree<Key, T, Compare>::AVLTree(const AVLTree &other)
    : root_(nullptr), size_(0) {
  if (other.root_) {
    root_ = copy_tree(other.root_);
    size_ = other.size_;
  }
}

// Конструктор перемещения, перемещает ресурсы из другого дерева
template <typename Key, typename T, typename Compare>
AVLTree<Key, T, Compare>::AVLTree(AVLTree &&other) noexcept
    : root_(other.root_), size_(other.size_) {
  other.root_ = nullptr;
  other.size_ = 0;
}

// Операторы присваивания
// Оператор копирующего присваивания
template <typename Key, typename T, typename Compare>
AVLTree<Key, T, Compare> &
AVLTree<Key, T, Compare>::operator=(const AVLTree &other) {
  if (this != &other) {
    AVLTree temp(other);
    swap(temp);
  }
  return *this;
}

// Оператор перемещающего присваивания
template <typename Key, typename T, typename Compare>
AVLTree<Key, T, Compare> &
AVLTree<Key, T, Compare>::operator=(AVLTree &&other) noexcept {
  if (this != &other) {
    clear();
    root_ = other.root_;
    size_ = other.size_;
    other.root_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

// Доступ к элементам
// Возвращает значение по ключу с проверкой существования
template <typename Key, typename T, typename Compare>
T &AVLTree<Key, T, Compare>::at(const Key &key) {
  Node *node = find_node(key);
  if (!node) {
    throw std::out_of_range("Key not found");
  }
  return node->data.second;
}

// Константная версия at
template <typename Key, typename T, typename Compare>
const T &AVLTree<Key, T, Compare>::at(const Key &key) const {
  Node *node = find_node(key);
  if (!node) {
    throw std::out_of_range("Key not found");
  }
  return node->data.second;
}

// Оператор доступа по ключу, создает элемент если не существует
template <typename Key, typename T, typename Compare>
T &AVLTree<Key, T, Compare>::operator[](const Key &key) {
  Node *node = find_node(key);
  if (!node) {
    auto [it, _] = insert(std::make_pair(key, T()));
    node = it.current_;
  }
  return node->data.second;
}

// Итераторы
// Возвращает итератор на первый элемент
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Iterator
AVLTree<Key, T, Compare>::begin() noexcept {
  Node *result = nullptr;
  if (root_) {
    result = find_min(root_);
  }
  return Iterator(result, this);
}

// Возвращает итератор на конец дерева
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Iterator
AVLTree<Key, T, Compare>::end() noexcept {
  return Iterator(nullptr, this);
}

// Константные версии итераторов
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::ConstIterator
AVLTree<Key, T, Compare>::begin() const noexcept {
  Node *result = nullptr;
  if (root_) {
    result = find_min(root_);
  }
  return ConstIterator(result, const_cast<AVLTree *>(this));
}

template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::ConstIterator
AVLTree<Key, T, Compare>::end() const noexcept {
  return ConstIterator(nullptr, const_cast<AVLTree *>(this));
}

template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::ConstIterator
AVLTree<Key, T, Compare>::cbegin() const noexcept {
  return begin();
}

template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::ConstIterator
AVLTree<Key, T, Compare>::cend() const noexcept {
  return end();
}

// Емкость
// Проверяет, пусто ли дерево
template <typename Key, typename T, typename Compare>
bool AVLTree<Key, T, Compare>::empty() const noexcept {
  return size_ == 0;
}

// Возвращает количество элементов
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::size_type
AVLTree<Key, T, Compare>::size() const noexcept {
  return size_;
}

// Возвращает максимально возможный размер
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::size_type
AVLTree<Key, T, Compare>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

// Модификаторы
// Очищает дерево
template <typename Key, typename T, typename Compare>
void AVLTree<Key, T, Compare>::clear() noexcept {
  if (root_) {
    destroy_node(root_);
    root_ = nullptr;
    size_ = 0;
  }
}

// Вставляет элемент в дерево
template <typename Key, typename T, typename Compare>
std::pair<typename AVLTree<Key, T, Compare>::Iterator, bool>
AVLTree<Key, T, Compare>::insert(const value_type &value) {
  Node *existing = find_node(value.first);
  if (existing) {
    return std::make_pair(Iterator(existing, this), false);
  }
  root_ = insert_node(root_, value);
  size_++;
  return std::make_pair(Iterator(find_node(value.first), this), true);
}

// Вставляет элемент по ключу и значению
template <typename Key, typename T, typename Compare>
std::pair<typename AVLTree<Key, T, Compare>::Iterator, bool>
AVLTree<Key, T, Compare>::insert(const Key &key, const T &value) {
  return insert(std::make_pair(key, value));
}

// Удаляет элемент по итератору
template <typename Key, typename T, typename Compare>
void AVLTree<Key, T, Compare>::erase(Iterator pos) {
  if (pos.current_) {
    root_ = delete_node(root_, pos.current_->data.first);
    size_--;
  }
}

// Удаляет элемент по ключу
template <typename Key, typename T, typename Compare>
void AVLTree<Key, T, Compare>::erase(const Key &key) {
  if (find_node(key)) {
    root_ = delete_node(root_, key);
    size_--;
  }
}

// Обменивает содержимое с другим деревом
template <typename Key, typename T, typename Compare>
void AVLTree<Key, T, Compare>::swap(AVLTree &other) noexcept {
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
}

// Поиск
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::size_type
AVLTree<Key, T, Compare>::count(const Key &key) const {
  return find_node(key) ? 1 : 0;
}

// Находит элемент по ключу
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Iterator
AVLTree<Key, T, Compare>::find(const Key &key) {
  return Iterator(find_node(key), this);
}

// Константная версия find
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::ConstIterator
AVLTree<Key, T, Compare>::find(const Key &key) const {
  return ConstIterator(find_node(key), const_cast<AVLTree *>(this));
}

// Проверяет наличие элемента с заданным ключом
template <typename Key, typename T, typename Compare>
bool AVLTree<Key, T, Compare>::contains(const Key &key) const {
  return find_node(key) != nullptr;
}

// Вспомогательные методы
// Создает новый узел
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Node *
AVLTree<Key, T, Compare>::create_node(const value_type &value) {
  return new Node(value);
}

// Рекурсивно удаляет узел и его потомков
template <typename Key, typename T, typename Compare>
void AVLTree<Key, T, Compare>::destroy_node(Node *node) {
  if (node) {
    destroy_node(node->left);
    destroy_node(node->right);
    delete node;
  }
}

// Рекурсивно копирует поддерево
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Node *
AVLTree<Key, T, Compare>::copy_tree(Node *node, Node *parent) {
  Node *result = nullptr;
  if (node) {
    result = create_node(node->data);
    result->parent = parent;
    result->left = copy_tree(node->left, result);
    result->right = copy_tree(node->right, result);
    result->height = node->height;
  }
  return result;
}

// Рекурсивно ищет узел по ключу.
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Node *
AVLTree<Key, T, Compare>::find_node(const Key &key) const {
  Node *result = nullptr;
  Node *current = root_;
  bool found = false;

  while (current != nullptr && !found) {
    if (comp_(key, current->data.first)) {
      current = current->left;
    } else if (comp_(current->data.first, key)) {
      current = current->right;
    } else {
      found = true;
      result = current;
    }
  }

  return result;
}

// Находит узел с минимальным ключом
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Node *
AVLTree<Key, T, Compare>::find_min(Node *node) const {
  Node *result = node;
  while (result && result->left) {
    result = result->left;
  }
  return result;
}

// Находит узел с максимальным ключом
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Node *
AVLTree<Key, T, Compare>::find_max(Node *node) const {
  Node *result = node;
  while (result && result->right) {
    result = result->right;
  }
  return result;
}

// AVL-специфичные методы
// Получает высоту узла
template <typename Key, typename T, typename Compare>
int AVLTree<Key, T, Compare>::get_height(Node *node) const {
  return node ? node->height : -1;
}

// Вычисляет баланс узла
template <typename Key, typename T, typename Compare>
int AVLTree<Key, T, Compare>::get_balance(Node *node) const {
  return node ? get_height(node->left) - get_height(node->right) : 0;
}

// Обновляет высоту узла
template <typename Key, typename T, typename Compare>
void AVLTree<Key, T, Compare>::update_height(Node *node) {
  if (node) {
    node->height =
        1 + std::max(get_height(node->left), get_height(node->right));
  }
}

// Выполняет левый поворот
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Node *
AVLTree<Key, T, Compare>::rotate_left(Node *node) {
  Node *result = node->right;
  Node *right_left = result->left;

  result->left = node;
  node->right = right_left;

  if (right_left) {
    right_left->parent = node;
  }

  result->parent = node->parent;
  node->parent = result;

  update_height(node);
  update_height(result);

  return result;
}

// Выполняет правый поворот
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Node *
AVLTree<Key, T, Compare>::rotate_right(Node *node) {
  Node *result = node->left;
  Node *left_right = result->right;

  result->right = node;
  node->left = left_right;

  if (left_right) {
    left_right->parent = node;
  }

  result->parent = node->parent;
  node->parent = result;

  update_height(node);
  update_height(result);

  return result;
}

// Балансирует узел
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Node *
AVLTree<Key, T, Compare>::balance(Node *node) {
  Node *result = node;
  if (node) {
    update_height(node);
    int balance_factor = get_balance(node);

    if (balance_factor > 1) {
      if (get_balance(node->left) < 0) {
        node->left = rotate_left(node->left);
      }
      result = rotate_right(node);
    } else if (balance_factor < -1) {
      if (get_balance(node->right) > 0) {
        node->right = rotate_right(node->right);
      }
      result = rotate_left(node);
    }
  }
  return result;
}

// Вставляет узел в поддерево
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Node *
AVLTree<Key, T, Compare>::insert_node(Node *node, const value_type &value) {
  Node *result = node;
  if (!node) {
    result = create_node(value);
  }
  // Если ключ меньше, чем ключ текущего узла, вставляем в левое поддерево
  else if (comp_(value.first, node->data.first)) {
    node->left = insert_node(node->left, value);
    node->left->parent = node;
    result = balance(node);
    // Если ключ больше, чем ключ текущего узла, вставляем в правое поддерево
  } else if (comp_(node->data.first, value.first)) {
    node->right = insert_node(node->right, value);
    node->right->parent = node;
    result = balance(node);
  }
  return result;
}

// Удаляет узел из поддерева
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Node *
AVLTree<Key, T, Compare>::delete_node(Node *node, const Key &key) {
  Node *result = node;
  if (node) {
    // Если ключ меньше, чем ключ текущего узла, удаляем из левого поддерева
    if (comp_(key, node->data.first)) {
      node->left = delete_node(node->left, key);
      if (node->left) {
        node->left->parent = node;
      }
      result = balance(node);
    }
    // Если ключ больше, чем ключ текущего узла, удаляем из правого поддерева
    else if (comp_(node->data.first, key)) {
      node->right = delete_node(node->right, key);
      if (node->right) {
        node->right->parent = node;
      }
      result = balance(node);
    }
    // Если ключ равен ключу текущего узла, удаляем узел
    else {
      if (!node->left || !node->right) {
        Node *temp = node->left ? node->left : node->right;
        delete node;
        result = temp;
      } else {
        Node *temp = find_min(node->right);
        // Заменяем данные удаляемого узла данными его преемника.
        // const_cast нужен, так как ключ в паре константный.
        const_cast<Key &>(node->data.first) = temp->data.first;
        node->data.second = temp->data.second;
        // Удаляем узел-преемник.
        node->right = delete_node(node->right, temp->data.first);
        if (node->right)
          node->right->parent = node;
        result = balance(node);
      }
    }
  }
  return result;
}

// Операторы итератора
// Префиксный инкремент
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Iterator &
AVLTree<Key, T, Compare>::Iterator::operator++() {
  Node *next_node = nullptr;
  if (current_) {
    Node *max_node = tree_ ? tree_->find_max(tree_->root_) : nullptr;
    if (current_ != max_node) {
      next_node = get_next_node(current_);
    }
  }
  // Если current_ был nullptr (end()) или max_node, next_node останется nullptr
  // Инкремент end() не делает ничего, как и в STL.
  if (current_) {
    current_ = next_node;
  }
  return *this;
}

// Постфиксный инкремент
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Iterator
AVLTree<Key, T, Compare>::Iterator::operator++(int) {
  Iterator result = *this;
  ++(*this);
  return result;
}

// Префиксный декремент
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Iterator &
AVLTree<Key, T, Compare>::Iterator::operator--() {
  Node *prev_node = nullptr;
  if (!current_) { // Если итератор был end()
    if (tree_ && tree_->root_) {
      prev_node = tree_->find_max(tree_->root_);
    }
  } else {
    Node *min_node = tree_ ? tree_->find_min(tree_->root_) : nullptr;
    if (current_ != min_node) {
      prev_node = get_prev_node(current_);
    }
  }
  current_ = prev_node;
  return *this;
}

// Постфиксный декремент
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Iterator
AVLTree<Key, T, Compare>::Iterator::operator--(int) {
  Iterator result = *this;
  --(*this);
  return result;
}

// Операторы константного итератора
// Префиксный инкремент
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::ConstIterator &
AVLTree<Key, T, Compare>::ConstIterator::operator++() {
  Node *next_node = nullptr;
  if (current_) {
    Node *max_node = tree_ ? tree_->find_max(tree_->root_) : nullptr;
    if (current_ != max_node) {
      next_node = get_next_node(current_);
    }
  }
  if (current_) {
    current_ = next_node;
  }
  return *this;
}

// Постфиксный инкремент
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::ConstIterator
AVLTree<Key, T, Compare>::ConstIterator::operator++(int) {
  ConstIterator result = *this;
  ++(*this);
  return result;
}

// Префиксный декремент
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::ConstIterator &
AVLTree<Key, T, Compare>::ConstIterator::operator--() {
  Node *prev_node = nullptr;
  if (!current_) { // Если итератор был end()
    if (tree_ && tree_->root_) {
      prev_node = tree_->find_max(tree_->root_);
    }
  } else {
    Node *min_node = tree_ ? tree_->find_min(tree_->root_) : nullptr;
    if (current_ != min_node) {
      prev_node = get_prev_node(current_);
    }
  }
  current_ = prev_node;
  return *this;
}

// Постфиксный декремент
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::ConstIterator
AVLTree<Key, T, Compare>::ConstIterator::operator--(int) {
  ConstIterator result = *this;
  --(*this);
  return result;
}

// Новые приватные методы итераторов
// Находит следующий по порядку узел
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Node *
AVLTree<Key, T, Compare>::Iterator::get_next_node(Node *node) {
  Node *result = nullptr;
  if (node) {
    if (node->right) {
      result = node->right;
      while (result->left) {
        result = result->left;
      }
    } else {
      Node *parent = node->parent;
      while (parent && node == parent->right) {
        node = parent;
        parent = parent->parent;
      }
      result = parent;
    }
  }
  return result;
}

// Находит предыдущий по порядку узел
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Node *
AVLTree<Key, T, Compare>::Iterator::get_prev_node(Node *node) {
  Node *result = nullptr;
  if (node) {
    if (node->left) {
      result = node->left;
      while (result->right) {
        result = result->right;
      }
    } else {
      Node *parent = node->parent;
      while (parent && node == parent->left) {
        node = parent;
        parent = parent->parent;
      }
      result = parent;
    }
  }
  return result;
}

// Находит следующий по порядку узел для ConstIterator.
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Node *
AVLTree<Key, T, Compare>::ConstIterator::get_next_node(Node *node) const {
  Node *result = nullptr;
  if (node) {
    if (node->right) {
      result = node->right;
      while (result->left) {
        result = result->left;
      }
    } else {
      Node *parent = node->parent;
      while (parent && node == parent->right) {
        node = parent;
        parent = parent->parent;
      }
      result = parent;
    }
  }
  return result;
}

// Находит предыдущий по порядку узел для ConstIterator.
template <typename Key, typename T, typename Compare>
typename AVLTree<Key, T, Compare>::Node *
AVLTree<Key, T, Compare>::ConstIterator::get_prev_node(Node *node) const {
  Node *result = nullptr;
  if (node) {
    if (node->left) {
      result = node->left;
      while (result->right) {
        result = result->right;
      }
    } else {
      Node *parent = node->parent;
      while (parent && node == parent->left) {
        node = parent;
        parent = parent->parent;
      }
      result = parent;
    }
  }
  return result;
}

} // namespace s21