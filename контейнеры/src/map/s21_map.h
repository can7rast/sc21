#ifndef S21_MAP_HEADERS
#define S21_MAP_HEADERS

#include <initializer_list>
#include <utility>
#include <vector>

#include "avl.hpp"

namespace s21 {

// Класс map реализует ассоциативный контейнер на основе AVL-дерева поиска

template <typename Key, typename T> class map {
public:
  // Итераторы для обхода контейнера
  class MapIterator;
  class ConstMapIterator;
  // Типы для удобства
  using key_type = Key;  // тип ключа
  using mapped_type = T; // тип значения
  using value_type =
      std::pair<const key_type, mapped_type>; // пара ключ-значение
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = MapIterator;
  using const_iterator = ConstMapIterator;
  using size_type = std::size_t;

  // Конструкторы и деструктор
  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  ~map();
  map &operator=(map &&m);

  // Доступ к элементам
  T &at(const Key &key);
  T &operator[](const Key &key); // доступ с созданием по умолчанию

  // Итераторы
  iterator begin();
  iterator end();

  // Методы для работы с размером и состоянием контейнера
  bool empty();
  size_type size();
  size_type max_size();
  const_iterator cbegin() const;
  const_iterator cend() const;

  // Модификаторы
  void clear();
  std::pair<iterator, bool> insert(const value_type &value); // вставка пары
  std::pair<iterator, bool> insert(const Key &key,
                                   const T &obj); // вставка по ключу и значению
  std::pair<iterator, bool>
  insert_or_assign(const Key &key, const T &obj); // вставка или присваивание
  void erase(iterator pos); // удалить по итератору
  void swap(map &other);    // обмен содержимым
  void merge(map &other); // переместить элементы из другого map
  bool contains(const Key &key); // проверить наличие ключа

  // Вставка нескольких элементов сразу (через parameter pack)
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  iterator find(const Key &key); // поиск по ключу

  // Класс обычного итератора для map
  class MapIterator {
  public:
    friend class map;
    MapIterator();
    explicit MapIterator(typename AVLTree<Key, T>::Iterator it);
    reference operator*();
    value_type *operator->();
    MapIterator &operator++();
    MapIterator operator++(int);
    MapIterator &operator--();
    MapIterator operator--(int);
    bool operator==(const MapIterator &other) const;
    bool operator!=(const MapIterator &other) const;

  private:
    typename AVLTree<Key, T>::Iterator it_;
  };

  // Класс константного итератора для map
  class ConstMapIterator {
  public:
    friend class map;
    ConstMapIterator();
    explicit ConstMapIterator(typename AVLTree<Key, T>::ConstIterator it);
    ConstMapIterator(const MapIterator &it);
    const_reference operator*() const;
    const value_type *operator->() const;
    ConstMapIterator &operator++();
    ConstMapIterator operator++(int);
    ConstMapIterator &operator--();
    ConstMapIterator operator--(int);
    bool operator==(const ConstMapIterator &other) const;
    bool operator!=(const ConstMapIterator &other) const;

  private:
    typename AVLTree<Key, T>::ConstIterator it_;
  };

private:
  AVLTree<Key, T> tree_; // внутреннее AVL-дерево для хранения данных
};

} // namespace s21

#include "s21_map.tpp"

#endif
