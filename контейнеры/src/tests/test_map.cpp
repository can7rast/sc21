#include "test_run.h"

namespace s21 {

// Тест конструктора по умолчанию: создаётся пустой map
TEST(MapTest, DefaultConstructor) {
  map<int, std::string> m;
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.size(), 0u);
}

// Тест конструктора со списком инициализации
TEST(MapTest, InitializerListConstructor) {
  map<int, std::string> m{{1, "one"}, {2, "two"}};
  EXPECT_EQ(m.size(), 2u);
  EXPECT_EQ(m.at(1), "one");
  EXPECT_EQ(m.at(2), "two");
}

// Тест конструктора копирования
TEST(MapTest, CopyConstructor) {
  map<int, int> m1;
  m1.insert({1, 10});
  map<int, int> m2(m1);
  EXPECT_EQ(m2.size(), 1u);
  EXPECT_EQ(m2.at(1), 10);
}

// Тест конструктора перемещения
TEST(MapTest, MoveConstructor) {
  map<int, int> m1;
  m1.insert({1, 10});
  map<int, int> m2(std::move(m1));
  EXPECT_EQ(m2.size(), 1u);
  EXPECT_EQ(m2.at(1), 10);
}

// Тест оператора перемещающего присваивания
TEST(MapTest, MoveAssignment) {
  map<int, int> m1;
  m1.insert({1, 10});
  map<int, int> m2;
  m2 = std::move(m1);
  EXPECT_EQ(m2.size(), 1u);
  EXPECT_EQ(m2.at(1), 10);
}

// Тест вставки и доступа через at
TEST(MapTest, InsertAndAt) {
  map<int, std::string> m;
  m.insert({1, "one"});
  m.insert({2, "two"});
  EXPECT_EQ(m.at(1), "one");
  EXPECT_EQ(m.at(2), "two");
  EXPECT_THROW(m.at(3), std::out_of_range);  // Проверка выброса исключения
}

// Тест оператора [] (создание по умолчанию и изменение значения)
TEST(MapTest, OperatorSquareBrackets) {
  map<int, int> m;
  m[5] = 42;
  EXPECT_EQ(m[5], 42);
  m[5] = 100;
  EXPECT_EQ(m[5], 100);
  EXPECT_EQ(m.size(), 1u);
}

// Тест insert_or_assign (вставка и присваивание по ключу)
TEST(MapTest, InsertOrAssign) {
  map<int, std::string> m;
  m.insert({1, "one"});
  m.insert_or_assign(1, "ONE");  // Перезапись значения
  EXPECT_EQ(m.at(1), "ONE");
  m.insert_or_assign(2, "TWO");  // Вставка нового
  EXPECT_EQ(m.at(2), "TWO");
}

// Тест удаления по итератору
TEST(MapTest, Erase) {
  map<int, int> m;
  m.insert({1, 10});
  m.insert({2, 20});
  auto it = m.begin();
  m.erase(it);  // Удаляем первый элемент
  EXPECT_EQ(m.size(), 1u);
  EXPECT_FALSE(m.contains(1));
}

// Тест удаления последнего элемента
TEST(MapTest, EraseLast) {
  map<int, int> m;
  m.insert({1, 10});
  auto it = m.begin();
  m.erase(it);
  EXPECT_TRUE(m.empty());
}

// Тест contains (проверка наличия ключа)
TEST(MapTest, Contains) {
  map<int, int> m;
  m.insert({1, 10});
  EXPECT_TRUE(m.contains(1));
  EXPECT_FALSE(m.contains(2));
}

// Тест очистки контейнера
TEST(MapTest, Clear) {
  map<int, int> m;
  m.insert({1, 10});
  m.insert({2, 20});
  m.clear();
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.size(), 0u);
}

// Тест обмена содержимым двух map
TEST(MapTest, Swap) {
  map<int, int> m1, m2;
  m1.insert({1, 10});
  m2.insert({2, 20});
  m1.swap(m2);
  EXPECT_TRUE(m1.contains(2));
  EXPECT_TRUE(m2.contains(1));
  EXPECT_FALSE(m1.contains(1));
  EXPECT_FALSE(m2.contains(2));
}

// Тест merge с непересекающимися ключами
TEST(MapTest, Merge) {
  map<int, int> m1, m2;
  m1.insert({1, 10});
  m2.insert({2, 20});
  m1.merge(m2);
  EXPECT_TRUE(m1.contains(1));
  EXPECT_TRUE(m1.contains(2));
  EXPECT_FALSE(m2.contains(2));
}

// Тест insert_many (вставка нескольких элементов сразу)
TEST(MapTest, InsertMany) {
  map<int, std::string> m;
  m.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"),
                std::make_pair(3, "three"));
  EXPECT_EQ(m.size(), 3u);
  EXPECT_EQ(m.at(2), "two");
}

// Тест обычного итератора (обход и суммирование значений)
TEST(MapTest, Iterator) {
  map<int, int> m;
  m.insert({1, 10});
  m.insert({2, 20});
  int sum = 0;
  for (auto it = m.begin(); it != m.end(); ++it) {
    sum += it->second;
  }
  EXPECT_EQ(sum, 30);
}

// Тест константного итератора (обход и суммирование значений)
TEST(MapTest, ConstIterator) {
  map<int, int> m;
  m.insert({1, 10});
  m.insert({2, 20});
  const map<int, int>& cm = m;
  int sum = 0;
  for (auto it = cm.cbegin(); it != cm.cend(); ++it) {
    sum += it->second;
  }
  EXPECT_EQ(sum, 30);
}

// Тест max_size (максимально возможный размер контейнера)
TEST(MapTest, MaxSize) {
  map<int, int> m;
  EXPECT_GT(m.max_size(), 1000u);
}

// Тест вставки дубликатов (insert возвращает false для существующего ключа)
TEST(MapTest, InsertDuplicate) {
  map<int, int> m;
  auto res1 = m.insert({1, 10});
  auto res2 = m.insert({1, 20});
  EXPECT_TRUE(res1.second);
  EXPECT_FALSE(res2.second);
  EXPECT_EQ(m.at(1), 10);
}

// Тест вставки по ключу и значению
TEST(MapTest, InsertByKeyValue) {
  map<int, int> m;
  auto res = m.insert(1, 42);
  EXPECT_TRUE(res.second);
  EXPECT_EQ(m.at(1), 42);
}

// Тест на пустоту после clear
TEST(MapTest, EmptyAfterClear) {
  map<int, int> m;
  m.insert({1, 1});
  m.clear();
  EXPECT_TRUE(m.empty());
}

// Тест удаления по невалидному итератору (end)
TEST(MapTest, EraseInvalidIterator) {
  map<int, int> m;
  // Не должно падать при попытке удалить end()
  EXPECT_NO_THROW(m.erase(m.end()));
}

// Тест всех операторов обычного итератора (++, --, *, ->, ==, !=)
TEST(MapTest, IteratorOperators) {
  map<int, int> m;
  m.insert({1, 10});
  m.insert({2, 20});
  auto it1 = m.begin();
  auto it2 = it1;
  ++it2;
  EXPECT_TRUE(it1 != it2);  // сравнение на неравенство
  auto it3 = it2++;
  EXPECT_TRUE(it3 != it2);  // постфиксный инкремент
  --it2;
  auto it4 = it2--;
  EXPECT_TRUE(it4 != it2);  // постфиксный декремент
  // Проверка operator->
  EXPECT_EQ(it1->second, 10);
}

// Тест всех операторов константного итератора (++, --, *, ->, ==, !=)
TEST(MapTest, ConstIteratorOperators) {
  map<int, int> m;
  m.insert({1, 10});
  m.insert({2, 20});
  const map<int, int>& cm = m;
  auto it1 = cm.cbegin();
  auto it2 = it1;
  ++it2;
  EXPECT_TRUE(it1 != it2);
  auto it3 = it2++;
  EXPECT_TRUE(it3 != it2);
  --it2;
  auto it4 = it2--;
  EXPECT_TRUE(it4 != it2);
  // Проверка operator->
  EXPECT_EQ(it1->second, 10);
}

// Тест конструкторов итераторов (копирование, из обычного в константный)
TEST(MapTest, IteratorConstructors) {
  map<int, int> m;
  m.insert({1, 10});
  auto it = m.begin();
  map<int, int>::MapIterator it2(it);
  EXPECT_TRUE(it == it2);
  map<int, int>::ConstMapIterator cit1(it);
  map<int, int>::ConstMapIterator cit2(cit1);
  EXPECT_TRUE(cit1 == cit2);
}

// Тест merge с пересечением ключей (ключ уже есть в первом map)
TEST(MapTest, MergeWithIntersection) {
  map<int, int> m1, m2;
  m1.insert({1, 10});
  m1.insert({2, 20});
  m2.insert({2, 200});
  m2.insert({3, 30});
  m1.merge(m2);
  EXPECT_EQ(m1.size(), 3u);
  EXPECT_EQ(m1.at(2), 20);  // старое значение сохраняется
  EXPECT_TRUE(m1.contains(3));
  EXPECT_TRUE(m2.contains(2));  // не перемещён, так как ключ уже был
  EXPECT_FALSE(m2.contains(3));
}

// Тест insert_many с дубликатами ключей
TEST(MapTest, InsertManyWithDuplicates) {
  map<int, int> m;
  auto res = m.insert_many(std::make_pair(1, 10), std::make_pair(1, 20),
                           std::make_pair(2, 30));
  EXPECT_EQ(m.size(), 2u);
  EXPECT_TRUE(res[0].second);
  EXPECT_FALSE(res[1].second);
  EXPECT_TRUE(res[2].second);
  EXPECT_EQ(m.at(1), 10);
  EXPECT_EQ(m.at(2), 30);
}

// Тест удаления из пустого контейнера (не должно быть исключения)
TEST(MapTest, EraseOnEmpty) {
  map<int, int> m;
  EXPECT_NO_THROW(m.erase(m.begin()));
  EXPECT_NO_THROW(m.erase(m.end()));
}

// Тест max_size для контейнера с большим типом значения
#include <array>
TEST(MapTest, MaxSizeBigType) {
  map<int, std::array<int, 100>> m;
  EXPECT_GT(m.max_size(), 0u);
}

// LL Rotation (правый поворот)
TEST(MapTest, AVL_LL_Rotation) {
  map<int, int> m;
  m.insert(3, 1);
  m.insert(2, 2);
  m.insert(1, 3);  // LL-case: 3-2-1
  // После поворота корень должен быть 2
  EXPECT_EQ(m.begin()->first, 1);
  auto it = m.begin();
  ++it;
  EXPECT_EQ(it->first, 2);
  ++it;
  EXPECT_EQ(it->first, 3);
}

// RR Rotation (левый поворот)
TEST(MapTest, AVL_RR_Rotation) {
  map<int, int> m;
  m.insert(1, 1);
  m.insert(2, 2);
  m.insert(3, 3);  // RR-case: 1-2-3
  EXPECT_EQ(m.begin()->first, 1);
  auto it = m.begin();
  ++it;
  EXPECT_EQ(it->first, 2);
  ++it;
  EXPECT_EQ(it->first, 3);
}

// LR Rotation (большой правый поворот)
TEST(MapTest, AVL_LR_Rotation) {
  map<int, int> m;
  m.insert(3, 1);
  m.insert(1, 2);
  m.insert(2, 3);  // LR-case: 3-1-2
  EXPECT_EQ(m.begin()->first, 1);
  auto it = m.begin();
  ++it;
  EXPECT_EQ(it->first, 2);
  ++it;
  EXPECT_EQ(it->first, 3);
}

// RL Rotation (большой левый поворот)
TEST(MapTest, AVL_RL_Rotation) {
  map<int, int> m;
  m.insert(1, 1);
  m.insert(3, 2);
  m.insert(2, 3);  // RL-case: 1-3-2
  EXPECT_EQ(m.begin()->first, 1);
  auto it = m.begin();
  ++it;
  EXPECT_EQ(it->first, 2);
  ++it;
  EXPECT_EQ(it->first, 3);
}

// Удаление листа
TEST(MapTest, EraseLeaf) {
  map<int, int> m;
  m.insert(2, 1);
  m.insert(1, 2);
  m.insert(3, 3);
  m.erase(m.begin());  // удаляем 1 (лист)
  EXPECT_EQ(m.size(), 2u);
  EXPECT_FALSE(m.contains(1));
  EXPECT_TRUE(m.contains(2));
  EXPECT_TRUE(m.contains(3));
}

// Удаление корня
TEST(MapTest, EraseRoot) {
  map<int, int> m;
  m.insert(2, 1);
  m.insert(1, 2);
  m.insert(3, 3);
  auto it = m.begin();
  ++it;  // указывает на 2 (корень)
  m.erase(it);
  EXPECT_EQ(m.size(), 2u);
  EXPECT_FALSE(m.contains(2));
  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(3));
}

// Удаление узла с одним ребёнком
TEST(MapTest, EraseNodeWithOneChild) {
  map<int, int> m;
  m.insert(1, 1);
  m.insert(2, 2);
  m.insert(3, 3);
  m.erase(m.begin());  // удаляем 1, у 2 останется только 3
  EXPECT_EQ(m.size(), 2u);
  EXPECT_FALSE(m.contains(1));
  EXPECT_TRUE(m.contains(2));
  EXPECT_TRUE(m.contains(3));
}

// Удаление узла с двумя детьми
TEST(MapTest, EraseNodeWithTwoChildren) {
  map<int, int> m;
  m.insert(2, 1);
  m.insert(1, 2);
  m.insert(3, 3);
  auto it = m.begin();
  ++it;         // указывает на 2
  m.erase(it);  // удаляем 2, у которого два потомка
  EXPECT_EQ(m.size(), 2u);
  EXPECT_FALSE(m.contains(2));
  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(3));
}

// Последовательное удаление всех элементов
TEST(MapTest, EraseAllSequential) {
  map<int, int> m;
  for (int i = 1; i <= 5; ++i) m.insert(i, i);
  while (!m.empty()) {
    m.erase(m.begin());
  }
  EXPECT_TRUE(m.empty());
}

// Удаление несуществующего ключа (не должно падать)
TEST(MapTest, EraseNonExistentKey) {
  map<int, int> m;
  m.insert(1, 1);
  m.erase(m.find(42));  // несуществующий ключ
  EXPECT_EQ(m.size(), 1u);
  EXPECT_TRUE(m.contains(1));
}

// Удаление до пустоты
TEST(MapTest, EraseToEmpty) {
  map<int, int> m;
  m.insert(1, 1);
  m.erase(m.begin());
  EXPECT_TRUE(m.empty());
}

// Удаление с поворотом LL (правый поворот)
TEST(MapTest, EraseWithLLRotation) {
  map<int, int> m;
  m.insert(3, 1);
  m.insert(2, 2);
  m.insert(1, 3);
  m.erase(
      m.find(3));  // после удаления 3, 2 становится корнем, 1 левым потомком
  EXPECT_EQ(m.begin()->first, 1);
  auto it = m.begin();
  ++it;
  EXPECT_EQ(it->first, 2);
  EXPECT_EQ(m.size(), 2u);
}

// Удаление с поворотом RR (левый поворот)
TEST(MapTest, EraseWithRRRotation) {
  map<int, int> m;
  m.insert(1, 1);
  m.insert(2, 2);
  m.insert(3, 3);
  m.erase(
      m.find(1));  // после удаления 1, 2 становится корнем, 3 правым потомком
  EXPECT_EQ(m.begin()->first, 2);
  auto it = m.begin();
  ++it;
  EXPECT_EQ(it->first, 3);
  EXPECT_EQ(m.size(), 2u);
}

// Удаление с поворотом LR (большой правый поворот)
TEST(MapTest, EraseWithLRRotation) {
  map<int, int> m;
  m.insert(3, 1);
  m.insert(1, 2);
  m.insert(2, 3);
  m.erase(
      m.find(3));  // после удаления 3, 2 становится корнем, 1 левым потомком
  EXPECT_EQ(m.begin()->first, 1);
  auto it = m.begin();
  ++it;
  EXPECT_EQ(it->first, 2);
  EXPECT_EQ(m.size(), 2u);
}

// Удаление с поворотом RL (большой левый поворот)
TEST(MapTest, EraseWithRLRotation) {
  map<int, int> m;
  m.insert(1, 1);
  m.insert(3, 2);
  m.insert(2, 3);
  m.erase(
      m.find(1));  // после удаления 1, 2 становится корнем, 3 правым потомком
  EXPECT_EQ(m.begin()->first, 2);
  auto it = m.begin();
  ++it;
  EXPECT_EQ(it->first, 3);
  EXPECT_EQ(m.size(), 2u);
}

}  // namespace s21
