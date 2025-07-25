#include "test_run.h"

TEST(VectorTest, DefaultConstructor) {
  s21::vector<int> v;
  size_t correct_size = 0;
  EXPECT_EQ(v.size(), correct_size);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, CountConstructor) {
  s21::vector<char> v(5);
  size_t correct_size = 5;
  EXPECT_EQ(v.size(), correct_size);
}

TEST(VectorTest, InitializerListConstructor) {
  s21::vector<int> v{10, 20, 30, 40};
  size_t correct_size = 4;
  EXPECT_EQ(v.size(), correct_size);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v[2], 30);
  EXPECT_EQ(v[3], 40);
}

TEST(VectorTest, CopyConstructor) {
  s21::vector<int> v{10, 20, 30, 40};
  s21::vector<int> copyv(v);
  size_t correct_size = 4;
  EXPECT_EQ(copyv.size(), correct_size);
  EXPECT_EQ(v[0], copyv[0]);
  EXPECT_EQ(v[1], copyv[1]);
  EXPECT_EQ(v[2], copyv[2]);
  EXPECT_EQ(v[3], copyv[3]);
}

TEST(VectorTest, MoveConstructor) {
  s21::vector<int> v{10, 20, 30, 40};
  s21::vector<int> copyv(std::move(v));
  size_t correct_size = 4;
  EXPECT_EQ(copyv.size(), correct_size);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, CopyOperatorEq) {
  s21::vector<int> v{10, 20, 30, 40};
  s21::vector<int> copyv = v;
  size_t correct_size = 4;
  EXPECT_EQ(copyv.size(), correct_size);
  EXPECT_EQ(v[0], copyv[0]);
  EXPECT_EQ(v[1], copyv[1]);
  EXPECT_EQ(v[2], copyv[2]);
  EXPECT_EQ(v[3], copyv[3]);
}

TEST(VectorTest, MoveOperatorEq) {
  s21::vector<int> v{10, 20, 30, 40};
  s21::vector<int> copyv(std::move(v));
  size_t correct_size = 4;
  EXPECT_EQ(copyv.size(), correct_size);
  correct_size = 0;
  EXPECT_EQ(v.size(), correct_size);
  EXPECT_TRUE(v.empty());
}

TEST(VectorIteratorTest, DereferenceOperator) {
  s21::vector<int> v{10, 20, 30};
  s21::vector<int>::iterator it = v.begin();
  EXPECT_EQ(*it, 10);
  it++;
  EXPECT_EQ(*it, 20);
  it++;
  EXPECT_EQ(*it, 30);
  s21::vector<int>::iterator new_it = v.end();
  --new_it;
  EXPECT_EQ(*it, 30);
}

TEST(VectorIteratorTest, ArrowOperator) {
  struct point {
    int x;
  };
  s21::vector<point> v{{10}, {20}, {30}};
  s21::vector<point>::iterator it = v.begin();
  EXPECT_EQ(it->x, 10);
  it++;
  EXPECT_EQ(it->x, 20);
  it++;
  EXPECT_EQ(it->x, 30);
}

TEST(VectorIteratorTest, MovementOperator) {
  s21::vector<int> v{10, 20, 30, 15, 50, 44};
  s21::vector<int>::iterator it = v.begin();
  it += 5;
  EXPECT_EQ(*it, 44);
  --it;
  EXPECT_EQ(*it, 50);
  it -= 3;
  EXPECT_EQ(*it, 20);
  it++;
  EXPECT_EQ(*it, 30);
  s21::vector<int>::iterator new_it = it + 2;
  EXPECT_EQ(*new_it, 50);
}

TEST(VectorIteratorTest, ComparisonsOperator) {
  s21::vector<int> v{10, 20, 30, 15, 50, 44};
  s21::vector<int>::iterator it = v.begin();
  s21::vector<int>::iterator new_it = it + 2;
  EXPECT_TRUE(it < new_it);
  EXPECT_TRUE(it <= new_it);
  EXPECT_TRUE(it != new_it);
  it += 2;
  EXPECT_TRUE(it == new_it);
  it += 2;
  EXPECT_TRUE(it > new_it);
  EXPECT_TRUE(it >= new_it);
}

TEST(VectorIteratorTest, DereferenceConstOperator) {
  s21::vector<int> v{10, 20, 30};
  s21::vector<int>::const_iterator it = v.container_;
  EXPECT_EQ(*it, 10);
  it++;
  EXPECT_EQ(*it, 20);
  it++;
  EXPECT_EQ(*it, 30);
}

TEST(VectorIteratorTest, ConstArrowOperator) {
  struct point {
    int x;
  };
  s21::vector<point> v{{10}, {20}, {30}};
  s21::vector<point>::const_iterator it = v.container_;
  EXPECT_EQ(it->x, 10);
  it++;
  EXPECT_EQ(it->x, 20);
  it++;
  EXPECT_EQ(it->x, 30);
}

TEST(VectorIteratorTest, MovementConstOperator) {
  s21::vector<int> v{10, 20, 30, 15, 50, 44};
  s21::vector<int>::const_iterator it = v.container_;
  it += 5;
  EXPECT_EQ(*it, 44);
  --it;
  EXPECT_EQ(*it, 50);
  it -= 3;
  EXPECT_EQ(*it, 20);
  it++;
  EXPECT_EQ(*it, 30);
  s21::vector<int>::const_iterator new_it = it + 2;
  EXPECT_EQ(*new_it, 50);
}

TEST(VectorIteratorTest, ComparisonsConstOperator) {
  s21::vector<int> v{10, 20, 30, 15, 50, 44};
  s21::vector<int>::const_iterator it = v.container_;
  s21::vector<int>::const_iterator new_it = it + 2;
  EXPECT_TRUE(it < new_it);
  EXPECT_TRUE(it <= new_it);
  EXPECT_TRUE(it != new_it);
  it += 2;
  EXPECT_TRUE(it == new_it);
  it += 2;
  EXPECT_TRUE(it > new_it);
  EXPECT_TRUE(it > new_it);
}

TEST(VectorTest, atMethod) {
  s21::vector<int> v{10, 20, 30, 15, 50, 44};
  EXPECT_ANY_THROW(v.at(8));
  s21::vector<int>::reference ref = v.at(4);
  EXPECT_EQ(ref, 50);
}

TEST(VectorTest, OperatorMethod) {
  s21::vector<int> v{10, 20, 30, 15, 50, 44};
  s21::vector<int>::reference ref = v[4];
  EXPECT_EQ(ref, 50);
}

TEST(VectorTest, AppealMasMethod) {
  s21::vector<int> v{10, 20, 30, 15, 50, 44};
  int* mas = v.data();
  EXPECT_EQ(v[0], mas[0]);
  EXPECT_EQ(v[1], mas[1]);
  EXPECT_EQ(v[2], mas[2]);
  EXPECT_EQ(v[3], mas[3]);
  EXPECT_EQ(v[4], mas[4]);
  EXPECT_EQ(v[5], mas[5]);
}

TEST(VectorTest, ReserveAndShrinkMethod) {
  s21::vector<int> v{10, 20, 30, 15, 50, 44};
  size_t correct_size = 6;
  EXPECT_EQ(v.capacity(), correct_size);
  v.reserve(30);
  correct_size = 30;
  EXPECT_EQ(v.capacity(), correct_size);
  v.shrink_to_fit();
  correct_size = 6;
  EXPECT_EQ(v.capacity(), correct_size);
}

TEST(VectorTest, ClearMethod) {
  s21::vector<int> v{10, 20, 30, 15, 50, 44};
  v.clear();
  size_t correct_size = 0;
  EXPECT_EQ(v.capacity(), correct_size);
  EXPECT_EQ(v.size(), correct_size);
  EXPECT_EQ(v.container_, nullptr);
}

TEST(VectorTest, InsertMethod) {
  s21::vector<int> v{10, 20, 30, 15, 50, 44};
  int value = 5;
  s21::vector<int>::iterator pos = v.begin() + 4;
  v.insert(pos, value);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v[2], 30);
  EXPECT_EQ(v[3], 15);
  EXPECT_EQ(v[4], 5);
  EXPECT_EQ(v[5], 50);
  EXPECT_EQ(v[6], 44);
}

TEST(VectorTest, EraseMethod) {
  s21::vector<int> v{10, 20, 30, 15, 50, 44};
  s21::vector<int>::iterator pos = v.begin() + 4;
  v.erase(pos);
  size_t correct_size = 5;
  EXPECT_EQ(v.size(), correct_size);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v[2], 30);
  EXPECT_EQ(v[3], 15);
  EXPECT_EQ(v[4], 44);
}

TEST(VectorTest, PushBackMethod) {
  s21::vector<int> v{10, 20, 30, 15, 50, 44};
  v.push_back(50);
  size_t correct_size = 7;
  EXPECT_EQ(v.size(), correct_size);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v[2], 30);
  EXPECT_EQ(v[3], 15);
  EXPECT_EQ(v[4], 50);
  EXPECT_EQ(v[5], 44);
  EXPECT_EQ(v[6], 50);
}

TEST(VectorTest, PopBackMethod) {
  s21::vector<int> v{10, 20, 30, 15, 50, 44};
  v.pop_back();
  size_t correct_size = 5;
  EXPECT_EQ(v.size(), correct_size);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v[2], 30);
  EXPECT_EQ(v[3], 15);
  EXPECT_EQ(v[4], 50);
}

TEST(VectorTest, SwapMethod) {
  s21::vector<int> v1{10, 20, 30, 15, 50, 44};
  s21::vector<int> v2{10, 20, 30, 15, 30, 44};
  v1.swap(v2);
  EXPECT_EQ(v1[4], 30);
  EXPECT_EQ(v2[4], 50);
}

TEST(VectorTest, InsertManyMethod) {
  s21::vector<int> v{10, 20, 30, 15, 50, 44};
  auto pos = v.cbegin() + 1;
  auto it = v.insert_many(pos, 46, 68, 90);
  size_t correct_size = 9;
  EXPECT_EQ(v.size(), correct_size);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 46);
  EXPECT_EQ(v[2], 68);
  EXPECT_EQ(v[3], 90);
  EXPECT_EQ(v[4], 20);
  EXPECT_EQ(v[5], 30);
  EXPECT_EQ(v[6], 15);
  EXPECT_EQ(v[7], 50);
  EXPECT_EQ(v[8], 44);
  EXPECT_EQ(*it, 46);
}

TEST(VectorTest, InsertManyBackMethod) {
  s21::vector<int> v{10, 20, 30, 15, 50, 44};
  v.insert_many_back(46, 68, 90);
  size_t correct_size = 9;
  EXPECT_EQ(v.size(), correct_size);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v[2], 30);
  EXPECT_EQ(v[3], 15);
  EXPECT_EQ(v[4], 50);
  EXPECT_EQ(v[5], 44);
  EXPECT_EQ(v[6], 46);
  EXPECT_EQ(v[7], 68);
  EXPECT_EQ(v[8], 90);
}