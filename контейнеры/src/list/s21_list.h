#ifndef S21_LIST_HEADERS
#define S21_LIST_HEADERS

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {

template <class T>
class list {
 private:
  struct Node {
    T data;
    Node *next;
    Node *prev;

    Node(T data = T(), Node *next = nullptr, Node *prev = nullptr)
        : data(data), next(next), prev(prev) {}
  };

  Node *_node;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  class iterator {
   private:
    Node *curr;

   public:
    iterator(Node *ptr = nullptr) : curr(ptr) {}

    reference operator*() const { return curr->data; }
    iterator &operator++() {
      curr = curr->next;
      return *this;
    }
    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }
    iterator &operator--() {
      curr = curr->prev;
      return *this;
    }
    iterator operator--(int) {
      iterator temp = *this;
      --(*this);
      return temp;
    }
    bool operator==(const iterator &other) const { return curr == other.curr; }
    bool operator!=(const iterator &other) const { return curr != other.curr; }

    Node *get_node() const { return curr; }
  };

  class const_iterator {
   private:
    const Node *curr;

   public:
    const_iterator(const Node *ptr = nullptr) : curr(ptr) {}
    const_iterator(const iterator &it) : curr(it.get_node()) {}

    const_reference operator*() const { return curr->data; }
    const_iterator &operator++() {
      curr = curr->next;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }
    const_iterator &operator--() {
      curr = curr->prev;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }
    bool operator==(const const_iterator &other) const {
      return curr == other.curr;
    }
    bool operator!=(const const_iterator &other) const {
      return curr != other.curr;
    }

    const Node *get_node() const { return curr; }
  };

  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();
  list &operator=(list &&l);
  list &operator=(const list &l);

  const_reference front() const;
  const_reference back() const;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);

  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);

  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);
};

}  // namespace s21

#include "s21_list.tpp"

#endif