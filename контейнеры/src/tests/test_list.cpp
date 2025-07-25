#include "test_run.h"

TEST(ListTest, DefaultConstructor) {
  s21::list<int> l;
  EXPECT_TRUE(l.empty());
  EXPECT_EQ(l.size(), 0U);
  EXPECT_EQ(l.begin(), l.end());
}

TEST(ListTest, SizeConstructor) {
  s21::list<int> l(5);
  EXPECT_EQ(l.size(), 5U);
  for (auto it = l.begin(); it != l.end(); it++) EXPECT_EQ(*it, 0);
}

TEST(ListTest, InitializerListConstructor) {
  s21::list<int> l = {1, 2, 3};
  EXPECT_EQ(l.size(), 3U);
  auto it = l.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
}

TEST(ListTest, CopyConstructor) {
  s21::list<int> l1 = {1, 2, 3};
  s21::list<int> l2(l1);
  EXPECT_EQ(l2.size(), 3U);
  auto it = l2.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
}

TEST(ListTest, MoveConstructor) {
  s21::list<int> l1 = {1, 2, 3};
  s21::list<int> l2(std::move(l1));
  EXPECT_EQ(l2.size(), 3U);
  auto it = l2.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_TRUE(l1.empty());
}

TEST(ListTest, CopyAssignment) {
  s21::list<int> l1 = {1, 2};
  s21::list<int> l2;
  l2 = l1;
  EXPECT_EQ(l2.size(), 2U);
  auto it = l2.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_FALSE(l1.empty());
}

TEST(ListTest, MoveAssignment) {
  s21::list<int> l1 = {1, 2};
  s21::list<int> l2;
  l2 = std::move(l1);
  EXPECT_EQ(l2.size(), 2U);
  auto it = l2.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_TRUE(l1.empty());
}

TEST(ListTest, FrontBack) {
  s21::list<int> l = {10, 20, 30};
  EXPECT_EQ(l.front(), 10);
  EXPECT_EQ(l.back(), 30);
}

TEST(ListTest, IteratorIncrementDecrement) {
  s21::list<int> l = {1, 2, 3};
  auto it = l.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  it++;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  it--;
  EXPECT_EQ(*it, 1);
}

TEST(ListTest, IteratorComparison) {
  s21::list<int> l = {1, 2};
  auto it1 = l.begin();
  auto it2 = l.begin();
  EXPECT_TRUE(it1 == it2);
  ++it2;
  EXPECT_TRUE(it1 != it2);
}

TEST(ListTest, EmptySize) {
  s21::list<int> l;
  EXPECT_TRUE(l.empty());
  l.push_back(1);
  EXPECT_FALSE(l.empty());
  EXPECT_EQ(l.size(), 1U);
}

TEST(ListTest, Clear) {
  s21::list<int> l = {1, 2, 3};
  l.clear();
  EXPECT_TRUE(l.empty());
  EXPECT_EQ(l.size(), 0U);
}

TEST(ListTest, InsertErase) {
  s21::list<int> l = {1, 3};
  auto it = l.begin();
  ++it;
  l.insert(it, 2);
  it = l.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  it = l.begin();
  ++it;
  l.erase(it);
  it = l.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 3);
}

TEST(ListTest, PushPopBackFront) {
  s21::list<int> l;
  l.push_back(2);
  l.push_front(1);
  l.push_back(3);
  EXPECT_EQ(l.size(), 3U);
  auto it = l.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  l.pop_front();
  l.pop_back();
  EXPECT_EQ(l.size(), 1U);
  EXPECT_EQ(l.front(), 2);
  EXPECT_EQ(l.back(), 2);
}

TEST(ListTest, Swap) {
  s21::list<int> l1 = {1, 2};
  s21::list<int> l2 = {10, 20, 30};
  l1.swap(l2);
  EXPECT_EQ(l1.size(), 3U);
  EXPECT_EQ(l2.size(), 2U);
  auto it = l1.begin();
  EXPECT_EQ(*it++, 10);
  EXPECT_EQ(*it++, 20);
  EXPECT_EQ(*it++, 30);
  it = l2.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
}

TEST(ListTest, Merge) {
  s21::list<int> l1 = {1, 3, 5};
  s21::list<int> l2 = {2, 4, 6};
  l1.merge(l2);
  EXPECT_EQ(l1.size(), 6U);
  auto it = l1.begin();
  for (int i = 1; i <= 6; ++i) {
    EXPECT_EQ(*it++, i);
  }
  EXPECT_TRUE(l2.empty());
}

TEST(ListTest, Splice) {
  s21::list<int> l1 = {1, 4};
  s21::list<int> l2 = {2, 3};
  auto it = ++l1.begin();
  l1.splice(it, l2);
  it = l1.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
  EXPECT_TRUE(l2.empty());
}

TEST(ListTest, Reverse) {
  s21::list<int> l = {1, 2, 3};
  l.reverse();
  auto it = l.begin();
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 1);
}

TEST(ListTest, Unique) {
  s21::list<int> l = {1, 1, 2, 2, 2, 3, 1};
  l.unique();
  auto it = l.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 1);
}

TEST(ListTest, Sort) {
  s21::list<int> l = {3, 1, 2, 5, 4};
  l.sort();
  auto it = l.begin();
  for (int i = 1; i <= 5; ++i) {
    EXPECT_EQ(*it++, i);
  }
}

TEST(ListTest, InsertMany) {
  s21::list<int> l = {1, 5};
  auto it = ++l.begin();
  l.insert_many(it, 2, 3, 4);
  it = l.begin();
  for (int i = 1; i <= 5; ++i) {
    EXPECT_EQ(*it++, i);
  }
}

TEST(ListTest, InsertManyBack) {
  s21::list<int> l = {1};
  l.insert_many_back(2, 3, 4);
  auto it = l.begin();
  for (int i = 1; i <= 4; ++i) {
    EXPECT_EQ(*it++, i);
  }
}

TEST(ListTest, InsertManyFront) {
  s21::list<int> l = {4};
  l.insert_many_front(1, 2, 3);
  auto it = l.begin();
  for (int i = 1; i <= 4; ++i) {
    EXPECT_EQ(*it++, i);
  }
}

TEST(ListTest, ListFloat) {
  s21::list<float> l = {1.1, 2.2, 3.3};
  EXPECT_FLOAT_EQ(l.front(), 1.1);
  EXPECT_FLOAT_EQ(l.back(), 3.3);
  l.push_back(4.4);
  EXPECT_FLOAT_EQ(l.back(), 4.4);
}

TEST(ListTest, ListString) {
  s21::list<std::string> l = {"a", "b", "c"};
  EXPECT_EQ(l.front(), "a");
  EXPECT_EQ(l.back(), "c");
  l.push_front("z");
  EXPECT_EQ(l.front(), "z");
}