#include "s21_list.h"

template <typename T>
s21::list<T>::list() : _node(nullptr) {}

template <typename T>
s21::list<T>::list(size_type n) : _node(nullptr) {
  for (size_type i = 0; i < n; i++) {
    push_back(T());
  }
}

template <typename T>
s21::list<T>::list(std::initializer_list<value_type> const &items)
    : _node(nullptr) {
  for (const auto &item : items) {
    push_back(item);
  }
}

template <typename T>
s21::list<T>::list(const list<T> &l) : _node(nullptr) {
  Node *temp = l._node;
  while (temp != nullptr) {
    push_back(temp->data);
    temp = temp->next;
  }
}

template <typename T>
s21::list<T>::list(list<T> &&l) : _node(l._node) {
  l._node = nullptr;
}

template <typename T>
s21::list<T>::~list() {
  clear();
}

template <typename T>
s21::list<T> &s21::list<T>::operator=(list<T> &&l) {
  if (this != &l) {
    clear();
    _node = l._node;
    l._node = nullptr;
  }
  return *this;
}

template <typename T>
s21::list<T> &s21::list<T>::operator=(const list<T> &other) {
  if (this != &other) {
    clear();
    Node *temp = other._node;
    while (temp != nullptr) {
      push_back(temp->data);
      temp = temp->next;
    }
  }

  return *this;
}

template <typename T>
typename s21::list<T>::const_reference s21::list<T>::front() const {
  if (empty()) {
    throw std::out_of_range("list::front(): container is empty");
  }
  return _node->data;
}

template <typename T>
typename s21::list<T>::const_reference s21::list<T>::back() const {
  if (empty()) {
    throw std::out_of_range("list::back(): container is empty");
  }
  Node *temp = _node;
  while (temp->next != nullptr) {
    temp = temp->next;
  }
  return temp->data;
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::begin() {
  return iterator(_node);
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::end() {
  return iterator(nullptr);
}

template <typename T>
typename s21::list<T>::const_iterator s21::list<T>::begin() const {
  return const_iterator(_node);
}

template <typename T>
typename s21::list<T>::const_iterator s21::list<T>::end() const {
  return const_iterator(nullptr);
}

template <typename T>
bool s21::list<T>::empty() const {
  return _node == nullptr;
}

template <typename T>
typename s21::list<T>::size_type s21::list<T>::size() const {
  size_type count = 0;
  Node *temp = _node;
  while (temp != nullptr) {
    count++;
    temp = temp->next;
  }
  return count;
}

template <typename T>
typename s21::list<T>::size_type s21::list<T>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void s21::list<T>::clear() {
  while (_node != nullptr) {
    pop_front();
  }
}

template <typename T>
typename s21::list<T>::iterator s21::list<T>::insert(iterator pos,
                                                     const_reference value) {
  int flag = 1;
  Node *new_node = new Node(value);
  new_node->next = nullptr;
  new_node->prev = nullptr;

  if (_node == nullptr) {
    _node = new_node;
    flag = 0;
  }

  if (flag) {
    Node *node_after = pos.get_node();

    if (node_after == nullptr) {
      Node *last_node = _node;
      while (last_node->next != nullptr) {
        last_node = last_node->next;
      }
      last_node->next = new_node;
      new_node->prev = last_node;
    } else if (node_after->prev == nullptr) {
      new_node->next = node_after;
      node_after->prev = new_node;
      _node = new_node;
    }

    else {
      Node *node_before = node_after->prev;

      node_before->next = new_node;
      new_node->prev = node_before;

      new_node->next = node_after;
      node_after->prev = new_node;
    }
  }

  return iterator(new_node);
}

template <typename T>
void s21 ::list<T>::erase(iterator pos) {
  int flag = 1;
  if (pos == this->end()) {
    flag = 0;
  }
  if (flag) {
    Node *node_erase = pos.get_node();
    Node *node_before = node_erase->prev;
    Node *node_after = node_erase->next;
    if (node_erase == _node) {
      _node = node_after;
    }
    if (node_before != nullptr) node_before->next = node_after;
    if (node_after != nullptr) node_after->prev = node_before;
    delete node_erase;
  }
}

template <typename T>
void s21::list<T>::push_back(const_reference value) {
  Node *new_node = new Node(value);
  if (_node == nullptr) {
    _node = new_node;
  } else {
    Node *temp = _node;
    while (temp->next != nullptr) {
      temp = temp->next;
    }
    temp->next = new_node;
    new_node->prev = temp;
  }
}

template <typename T>
void s21::list<T>::pop_back() {
  if (empty()) return;

  if (_node->next == nullptr) {
    delete _node;
    _node = nullptr;
  } else {
    Node *temp = _node;
    while (temp->next->next != nullptr) {
      temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
  }
}

template <typename T>
void s21::list<T>::push_front(const_reference value) {
  Node *new_node = new Node(value);
  new_node->next = _node;
  if (_node != nullptr) {
    _node->prev = new_node;
  }
  _node = new_node;
}

template <typename T>
void s21::list<T>::pop_front() {
  if (empty()) return;

  Node *temp = _node;
  _node = _node->next;
  if (_node != nullptr) {
    _node->prev = nullptr;
  }
  delete temp;
}

template <typename T>
void s21::list<T>::swap(list<T> &other) {
  std::swap(this->_node, other._node);
}

template <typename T>
void s21::list<T>::reverse() {
  if (_node == nullptr || _node->next == nullptr) {
    return;
  }

  Node *new_head = _node;
  while (new_head->next != nullptr) {
    new_head = new_head->next;
  }
  Node *temp = _node;
  while (temp != nullptr) {
    Node *curr = temp->next;
    std::swap(temp->next, temp->prev);
    temp = curr;
  }
  _node = new_head;
}

template <typename T>
void s21::list<T>::splice(const_iterator pos, list &other) {
  if (other.empty() || this == &other) {
    return;
  }

  Node *other_head = other._node;
  Node *other_tail = other._node;
  while (other_tail->next != nullptr) {
    other_tail = other_tail->next;
  }

  Node *insertion_node = const_cast<Node *>(pos.get_node());

  if (insertion_node == nullptr) {
    if (this->empty()) {
      _node = other_head;
    } else {
      Node *this_tail = _node;
      while (this_tail->next != nullptr) {
        this_tail = this_tail->next;
      }
      this_tail->next = other_head;
      other_head->prev = this_tail;
    }
  }

  else if (insertion_node == _node) {
    other_tail->next = _node;
    _node->prev = other_tail;
    _node = other_head;
  }

  else {
    Node *before_insertion = insertion_node->prev;

    before_insertion->next = other_head;
    other_head->prev = before_insertion;

    other_tail->next = insertion_node;
    insertion_node->prev = other_tail;
  }

  other._node = nullptr;
}

template <typename T>
void s21::list<T>::merge(list<T> &other) {
  if (this == &other || other.empty()) {
    return;
  }

  if (this->empty()) {
    this->swap(other);
    return;
  }

  Node *this_current = this->_node;
  Node *other_current = other._node;

  while (this_current != nullptr && other_current != nullptr) {
    if (other_current->data < this_current->data) {
      Node *node_to_move = other_current;
      other_current = other_current->next;

      Node *prev_node = this_current->prev;

      node_to_move->prev = prev_node;
      node_to_move->next = this_current;
      this_current->prev = node_to_move;

      if (prev_node != nullptr) {
        prev_node->next = node_to_move;
      } else {
        this->_node = node_to_move;
      }
    } else {
      this_current = this_current->next;
    }
  }
  if (other_current != nullptr) {
    Node *this_tail = this->_node;
    while (this_tail->next != nullptr) {
      this_tail = this_tail->next;
    }

    this_tail->next = other_current;
    other_current->prev = this_tail;
  }

  other._node = nullptr;
}

template <typename T>
void s21::list<T>::unique() {
  if (_node == nullptr || _node->next == nullptr) {
    return;
  }

  Node *temp = _node;
  while (temp != nullptr && temp->next != nullptr) {
    if (temp->data == temp->next->data) {
      Node *need_delete = temp->next;
      temp->next = need_delete->next;
      if (need_delete->next != nullptr) {
        need_delete->next->prev = temp;
      }
      delete need_delete;
    } else {
      temp = temp->next;
    }
  }
}

template <typename T>
void s21::list<T>::sort() {
  if (_node == nullptr || _node->next == nullptr) return;

  Node *slow = _node, *fast = _node->next;
  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }

  list<T> right_half;
  right_half._node = slow->next;
  if (right_half._node) right_half._node->prev = nullptr;
  slow->next = nullptr;

  list<T> left_half;
  left_half._node = _node;
  _node = nullptr;

  left_half.sort();
  right_half.sort();

  left_half.merge(right_half);
  this->swap(left_half);
}

template <typename T>
template <typename... Args>
typename s21::list<T>::iterator s21::list<T>::insert_many(
    typename s21::list<T>::const_iterator pos, Args &&...args) {
  int flag = 1;
  iterator result_it = iterator(const_cast<Node *>(pos.get_node()));

  if (sizeof...(args) == 0) {
    flag = 0;
  }

  if (flag) {
    Node *node_after = const_cast<Node *>(pos.get_node());
    Node *node_before = nullptr;
    if (empty()) {
      node_before = nullptr;
    } else if (node_after == nullptr) {
      Node *last_node = _node;
      while (last_node->next != nullptr) {
        last_node = last_node->next;
      }
      node_before = last_node;
    } else {
      node_before = node_after->prev;
    }

    Node *first_inserted_node = nullptr;
    Node *last_inserted_node = node_before;

    for (const auto &arg : {std::forward<Args>(args)...}) {
      Node *new_node = new Node(arg);

      if (first_inserted_node == nullptr) {
        first_inserted_node = new_node;
      }

      new_node->prev = last_inserted_node;
      if (last_inserted_node != nullptr) {
        last_inserted_node->next = new_node;
      }

      last_inserted_node = new_node;
    }

    if (first_inserted_node != nullptr) {
      last_inserted_node->next = node_after;

      if (node_after != nullptr) {
        node_after->prev = last_inserted_node;
      }

      if (node_before == nullptr) {
        _node = first_inserted_node;
      }
      result_it = iterator(first_inserted_node);
    }
  }

  return result_it;
}

template <typename T>
template <typename... Args>
void s21::list<T>::insert_many_back(Args &&...args) {
  insert_many(this->end(), std::forward<Args>(args)...);
}

template <typename T>
template <typename... Args>
void s21::list<T>::insert_many_front(Args &&...args) {
  insert_many(this->begin(), std::forward<Args>(args)...);
}