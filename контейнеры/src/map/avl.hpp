#pragma once

#include <cstddef> // std::size_t — тип для размеров
#include <functional> // std::less — стандартная функция сравнения
#include <utility> // std::pair — пара ключ-значение

namespace s21 {

template <typename Key, typename T, typename Compare = std::less<Key>>
class AVLTree {
public:
  using value_type = std::pair<const Key, T>;
  using size_type = std::size_t;

  struct Node {
    value_type data;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
    int height = 0;

    Node(const value_type &value) : data(value) {}
  };

  class Iterator {
  public:
    Iterator() : current_(nullptr), tree_(nullptr) {}
    explicit Iterator(Node *node, AVLTree *tree = nullptr)
        : current_(node), tree_(tree) {}

    value_type &operator*() { return current_->data; }
    const value_type &operator*() const { return current_->data; }
    value_type *operator->() { return &(current_->data); }
    const value_type *operator->() const { return &(current_->data); }

    Iterator &operator++();
    Iterator operator++(int);
    Iterator &operator--();
    Iterator operator--(int);

    bool operator==(const Iterator &other) const {
      return current_ == other.current_;
    }
    bool operator!=(const Iterator &other) const { return !(*this == other); }

  private:
    Node *get_next_node(Node *node);
    Node *get_prev_node(Node *node);
    Node *current_;
    AVLTree *tree_;
    friend class AVLTree;
  };

  class ConstIterator {
  public:
    ConstIterator() : current_(nullptr), tree_(nullptr) {}
    explicit ConstIterator(Node *node, AVLTree *tree = nullptr)
        : current_(node), tree_(tree) {}
    ConstIterator(const Iterator &it)
        : current_(it.current_), tree_(it.tree_) {}

    const value_type &operator*() const { return current_->data; }
    const value_type *operator->() const { return &(current_->data); }

    ConstIterator &operator++();
    ConstIterator operator++(int);
    ConstIterator &operator--();
    ConstIterator operator--(int);

    bool operator==(const ConstIterator &other) const {
      return current_ == other.current_;
    }
    bool operator!=(const ConstIterator &other) const {
      return !(*this == other);
    }

  private:
    Node *get_next_node(Node *node) const;
    Node *get_prev_node(Node *node) const;
    Node *current_;
    AVLTree *tree_;
    friend class AVLTree;
  };

  // Конструктор по умолчанию
  AVLTree() noexcept;
  ~AVLTree();
  AVLTree(const AVLTree &other);
  AVLTree(AVLTree &&other) noexcept;

  // операторы сравнения
  AVLTree &operator=(const AVLTree &other);
  AVLTree &operator=(AVLTree &&other) noexcept;

  // доступ
  T &at(const Key &key);
  const T &at(const Key &key) const;
  T &operator[](const Key &key);

  // Итераторы
  Iterator begin() noexcept;
  Iterator end() noexcept;
  ConstIterator begin() const noexcept;
  ConstIterator end() const noexcept;
  ConstIterator cbegin() const noexcept;
  ConstIterator cend() const noexcept;

  // Объем
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // операции
  void clear() noexcept;
  std::pair<Iterator, bool> insert(const value_type &value);
  std::pair<Iterator, bool> insert(const Key &key, const T &value);
  void erase(Iterator pos);
  void erase(const Key &key);
  void swap(AVLTree &other) noexcept;

  // поиск
  size_type count(const Key &key) const;
  Iterator find(const Key &key);
  ConstIterator find(const Key &key) const;
  bool contains(const Key &key) const;

private:
  Node *root_ = nullptr;
  size_type size_ = 0;
  Compare comp_;

  // Вспомогающие методы
  Node *create_node(const value_type &value);
  void destroy_node(Node *node);
  Node *copy_tree(Node *node, Node *parent = nullptr);
  Node *find_node(const Key &key) const;
  Node *find_min(Node *node) const;
  Node *find_max(Node *node) const;

  // AVL методы
  int get_height(Node *node) const;
  int get_balance(Node *node) const;
  void update_height(Node *node);
  Node *rotate_left(Node *node);
  Node *rotate_right(Node *node);
  Node *balance(Node *node);
  Node *insert_node(Node *node, const value_type &value);
  Node *delete_node(Node *node, const Key &key);

  friend class Iterator;
  friend class ConstIterator;
};

} // namespace s21

#include "avl.tpp"
