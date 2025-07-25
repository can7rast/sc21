#include <string>
#include <vector>

#include "test_run.h"

TEST(SetConstructorsTest, DefaultConstractor) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0U);
  EXPECT_EQ(s.begin(), s.end());
}

TEST(SetConstructorsTest, InitializerListConstructor) {
  s21::set<int> s = {1, 4, 8, 6, 5, 3, 4};
  EXPECT_EQ(s.size(), 6U);
  EXPECT_FALSE(s.empty());
  auto it = s.begin();

  EXPECT_EQ((*it++).first, 1);
  EXPECT_EQ((*it++).first, 3);
  EXPECT_EQ((*it++).first, 4);
  EXPECT_EQ((*it++).first, 5);
  EXPECT_EQ((*it++).first, 6);
  EXPECT_EQ((*it++).first, 8);
}

TEST(SetConstructorsTest, InitializerListConstructorString) {
  s21::set<std::string> s = {"world", "hello", "apple", "world"};
  EXPECT_EQ(s.size(), 3U);
  auto it = s.begin();
  EXPECT_EQ((*it++).first, "apple");
  EXPECT_EQ((*it++).first, "hello");
  EXPECT_EQ((*it++).first, "world");
}

TEST(SetConstructorsTest, InitializerListConstructorEmpty) {
  s21::set<int> s = {};
  EXPECT_TRUE(s.empty());
}

TEST(SetConstructorsTest, CopyConstructor) {
  s21::set<int> s1 = {10, 5, 15};
  s21::set<int> s2(s1);

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_TRUE(s2.contains(5));
  EXPECT_TRUE(s2.contains(10));
  EXPECT_TRUE(s2.contains(15));

  s1.insert(1);
  EXPECT_EQ(s1.size(), 4U);
  EXPECT_EQ(s2.size(), 3U);
}

TEST(SetConstructorsTest, MoveConstructor) {
  s21::set<int> s1 = {1, 5, 3};
  s21::set<int> s2(std::move(s1));

  EXPECT_EQ(s2.size(), 3U);
  EXPECT_EQ(s1.size(), 0U);
  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.contains(1));
}

TEST(SetConstructorsTest, CopyAssignmentOperator) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {99, 100};

  s2 = s1;

  EXPECT_EQ(s2.size(), 3U);
  EXPECT_TRUE(s2.contains(2));
  EXPECT_EQ(s1.size(), 3U);
}

TEST(SetConstructorsTest, MoveAssignmentOperator) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {99, 100};

  s2 = std::move(s1);

  EXPECT_EQ(s2.size(), 3U);
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s1.size(), 0U);
}

TEST(SetMethodsTest, SizeAndEmpty) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0U);

  s.insert(10);
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 1U);

  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0U);
}

TEST(SetMethodsTest, MaxSize) {
  s21::set<int> s;
  EXPECT_GT(s.max_size(), 100000U);
}

TEST(SetMethodsTest, Insert) {
  s21::set<int> s;

  auto res1 = s.insert(20);
  EXPECT_TRUE(res1.second);
  EXPECT_EQ((*res1.first).first, 20);
  EXPECT_EQ(s.size(), 1U);

  s.insert(10);

  auto res3 = s.insert(20);
  EXPECT_FALSE(res3.second);
  EXPECT_EQ((*res3.first).first, 20);
  EXPECT_EQ(s.size(), 2U);
}

TEST(SetMethodsTest, Erase) {
  s21::set<int> s = {10, 5, 20, 3, 8, 15, 25};
  EXPECT_EQ(s.size(), 7U);

  auto it_to_erase = s.find(10);
  s.erase(it_to_erase);

  EXPECT_EQ(s.size(), 6U);
  EXPECT_FALSE(s.contains(10));

  auto it = s.begin();
  EXPECT_EQ((*it++).first, 3);
  EXPECT_EQ((*it++).first, 5);
  EXPECT_EQ((*it++).first, 8);
  EXPECT_EQ((*it++).first, 15);
  EXPECT_EQ((*it++).first, 20);
  EXPECT_EQ((*it++).first, 25);
}

TEST(SetMethodsTest, FindAndContains) {
  s21::set<int> s = {10, 20, 30};
  auto it_found = s.find(20);
  EXPECT_NE(it_found, s.end());
  EXPECT_EQ((*it_found).first, 20);
  EXPECT_TRUE(s.contains(20));

  auto it_not_found = s.find(99);
  EXPECT_EQ(it_not_found, s.end());
  EXPECT_FALSE(s.contains(99));
}

TEST(SetMethodsTest, Clear) {
  s21::set<int> s = {1, 2, 3, 4, 5};
  s.clear();

  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0U);
  EXPECT_EQ(s.begin(), s.end());

  s.insert(100);
  EXPECT_EQ(s.size(), 1U);
  EXPECT_TRUE(s.contains(100));
}

TEST(SetMethodsTest, Swap) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {100, 200};

  s1.swap(s2);

  EXPECT_EQ(s1.size(), 2U);
  EXPECT_TRUE(s1.contains(100));
  EXPECT_FALSE(s1.contains(1));

  EXPECT_EQ(s2.size(), 3U);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_FALSE(s2.contains(100));
}

TEST(SetMethodsTest, Merge) {
  s21::set<int> s1 = {1, 5, 10};
  s21::set<int> s2 = {2, 5, 12};

  s1.merge(s2);

  EXPECT_EQ(s1.size(), 5U);
  EXPECT_TRUE(s1.contains(1));
  EXPECT_TRUE(s1.contains(2));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(10));
  EXPECT_TRUE(s1.contains(12));

  EXPECT_EQ(s2.size(), 1U);
  EXPECT_TRUE(s2.contains(5));
  EXPECT_FALSE(s2.contains(2));
}

TEST(SetMethodsTest, MergeSelf) {
  s21::set<int> s1 = {1, 2, 3};
  s1.merge(s1);
  EXPECT_EQ(s1.size(), 3U);
  EXPECT_TRUE(s1.contains(2));
}

TEST(SetMethodsTest, InsertMany) {
  s21::set<int> s = {10};
  auto results = s.insert_many(20, 5, 10);

  EXPECT_EQ(s.size(), 3U);
  EXPECT_TRUE(s.contains(5) && s.contains(10) && s.contains(20));
  EXPECT_EQ(results.size(), 3U);
  EXPECT_TRUE(results[0].second);
  EXPECT_EQ((*results[0].first).first, 20);
  EXPECT_TRUE(results[1].second);
  EXPECT_EQ((*results[1].first).first, 5);
  EXPECT_FALSE(results[2].second);
  EXPECT_EQ((*results[2].first).first, 10);
}