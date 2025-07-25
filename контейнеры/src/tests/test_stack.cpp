#include "test_run.h"

TEST(StackTest, DefaultConstructor) {
  s21::stack<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0U);
}

TEST(StackTest, InitializerListConstructor_int) {
  s21::stack<int> q = {1, 2, 3};
  EXPECT_EQ(q.size(), 3U);
  EXPECT_EQ(q.top(), 1);
  q.pop();
  EXPECT_EQ(q.top(), 2);
  q.pop();
  EXPECT_EQ(q.top(), 3);
}

TEST(StackTest, InitializerListConstructor_float) {
  s21::stack<float> q = {1.5, 2.6, 3.7};
  EXPECT_EQ(q.size(), 3U);
  EXPECT_FLOAT_EQ(q.top(), 1.5);
  q.pop();
  EXPECT_FLOAT_EQ(q.top(), 2.6);
  q.pop();
  EXPECT_FLOAT_EQ(q.top(), 3.7);
}

TEST(StackTest, InitializerListConstructor_string) {
  s21::stack<std::string> q = {"Hi", "my", "name"};
  EXPECT_EQ(q.size(), 3U);
  EXPECT_EQ(q.top(), "Hi");
  q.pop();
  EXPECT_EQ(q.top(), "my");
  q.pop();
  EXPECT_EQ(q.top(), "name");
}

TEST(StackTest, CopyConstructor_int) {
  s21::stack<int> q1 = {10, 20, 30};
  s21::stack<int> q2(q1);

  EXPECT_EQ(q2.size(), 3U);
  EXPECT_EQ(q2.top(), 10);
  q2.pop();
  EXPECT_EQ(q2.top(), 20);
  q2.pop();
  EXPECT_EQ(q2.top(), 30);

  EXPECT_FALSE(q1.empty());
}

TEST(StackTest, CopyConstructor_float) {
  s21::stack<float> q1 = {10.1, 20.2, 30.3};
  s21::stack<float> q2(q1);

  EXPECT_EQ(q2.size(), 3U);
  EXPECT_FLOAT_EQ(q2.top(), 10.1);
  q2.pop();
  EXPECT_FLOAT_EQ(q2.top(), 20.2);
  q2.pop();
  EXPECT_FLOAT_EQ(q2.top(), 30.3);

  EXPECT_FALSE(q1.empty());
}

TEST(StackTest, CopyConstructor_string) {
  s21::stack<std::string> q1 = {"How", "are", "you"};
  s21::stack<std::string> q2(q1);

  EXPECT_EQ(q2.size(), 3U);
  EXPECT_EQ(q2.top(), "How");
  q2.pop();
  EXPECT_EQ(q2.top(), "are");
  q2.pop();
  EXPECT_EQ(q2.top(), "you");

  EXPECT_FALSE(q1.empty());
}

TEST(StackTest, MoveConstructor_int) {
  s21::stack<int> q1 = {7, 8, 9};
  s21::stack<int> q2(std::move(q1));

  EXPECT_EQ(q2.size(), 3U);
  EXPECT_EQ(q2.top(), 7);
  q2.pop();
  EXPECT_EQ(q2.top(), 8);
  q2.pop();
  EXPECT_EQ(q2.top(), 9);

  EXPECT_TRUE(q1.empty());
}

TEST(StackTest, MoveConstructor_float) {
  s21::stack<float> q1 = {7.7, 8.8, 9.9};
  s21::stack<float> q2(std::move(q1));

  EXPECT_EQ(q2.size(), 3U);
  EXPECT_FLOAT_EQ(q2.top(), 7.7);
  q2.pop();
  EXPECT_FLOAT_EQ(q2.top(), 8.8);
  q2.pop();
  EXPECT_FLOAT_EQ(q2.top(), 9.9);

  EXPECT_TRUE(q1.empty());
}

TEST(StackTest, MoveConstructor_string) {
  s21::stack<std::string> q1 = {"This", "is", "test"};
  s21::stack<std::string> q2(std::move(q1));

  EXPECT_EQ(q2.size(), 3U);
  EXPECT_EQ(q2.top(), "This");
  q2.pop();
  EXPECT_EQ(q2.top(), "is");
  q2.pop();
  EXPECT_EQ(q2.top(), "test");

  EXPECT_TRUE(q1.empty());
}

TEST(StackTest, CopyAssignment_int) {
  s21::stack<int> q1 = {1, 2};
  s21::stack<int> q2;
  q2 = q1;

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_EQ(q2.top(), 1);
  q2.pop();
  EXPECT_EQ(q2.top(), 2);

  EXPECT_FALSE(q1.empty());
}

TEST(StackTest, CopyAssignment_float) {
  s21::stack<float> q1 = {1.5, 2.5};
  s21::stack<float> q2;
  q2 = q1;

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_FLOAT_EQ(q2.top(), 1.5);
  q2.pop();
  EXPECT_FLOAT_EQ(q2.top(), 2.5);

  EXPECT_FALSE(q1.empty());
}

TEST(StackTest, CopyAssignment_string) {
  s21::stack<std::string> q1 = {"school", "21"};
  s21::stack<std::string> q2;
  q2 = q1;

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_EQ(q2.top(), "school");
  q2.pop();
  EXPECT_EQ(q2.top(), "21");

  EXPECT_FALSE(q1.empty());
}

TEST(StackTest, MoveAssignment_int) {
  s21::stack<int> q1 = {100, 200};
  s21::stack<int> q2;
  q2 = std::move(q1);

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_EQ(q2.top(), 100);
  q2.pop();
  EXPECT_EQ(q2.top(), 200);

  EXPECT_TRUE(q1.empty());
}

TEST(StackTest, MoveAssignment_float) {
  s21::stack<float> q1 = {100.123, 200.456};
  s21::stack<float> q2;
  q2 = std::move(q1);

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_FLOAT_EQ(q2.top(), 100.123);
  q2.pop();
  EXPECT_FLOAT_EQ(q2.top(), 200.456);

  EXPECT_TRUE(q1.empty());
}

TEST(StackTest, MoveAssignment_string) {
  s21::stack<std::string> q1 = {"abc", "def"};
  s21::stack<std::string> q2;
  q2 = std::move(q1);

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_EQ(q2.top(), "abc");
  q2.pop();
  EXPECT_EQ(q2.top(), "def");

  EXPECT_TRUE(q1.empty());
}

TEST(StackTest, PushAndPop_int) {
  s21::stack<int> q;
  q.push(5);
  q.push(10);
  EXPECT_EQ(q.top(), 10);
  EXPECT_EQ(q.size(), 2U);

  q.pop();
  EXPECT_EQ(q.top(), 5);
  EXPECT_EQ(q.size(), 1U);

  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(StackTest, PushAndPop_float) {
  s21::stack<float> q;
  q.push(5.1);
  q.push(10.2);
  EXPECT_FLOAT_EQ(q.top(), 10.2);
  EXPECT_EQ(q.size(), 2U);

  q.pop();
  EXPECT_FLOAT_EQ(q.top(), 5.1);
  EXPECT_EQ(q.size(), 1U);

  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(StackTest, PushAndPop_string) {
  s21::stack<std::string> q;
  q.push("Love");
  q.push("is");
  EXPECT_EQ(q.top(), "is");
  EXPECT_EQ(q.size(), 2U);

  q.pop();
  EXPECT_EQ(q.top(), "Love");
  EXPECT_EQ(q.size(), 1U);

  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(StackTest, Swap_int) {
  s21::stack<int> q1 = {1, 2};
  s21::stack<int> q2 = {9};

  q1.swap(q2);

  EXPECT_EQ(q1.size(), 1U);
  EXPECT_EQ(q1.top(), 9);

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_EQ(q2.top(), 1);
  q2.pop();
  EXPECT_EQ(q2.top(), 2);
}

TEST(StackTest, Swap_float) {
  s21::stack<float> q1 = {1.1, 2.2};
  s21::stack<float> q2 = {9.3};

  q1.swap(q2);

  EXPECT_EQ(q1.size(), 1U);
  EXPECT_FLOAT_EQ(q1.top(), 9.3);

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_FLOAT_EQ(q2.top(), 1.1);
  q2.pop();
  EXPECT_FLOAT_EQ(q2.top(), 2.2);
}

TEST(StackTest, Swap_string) {
  s21::stack<std::string> q1 = {"abc", "def"};
  s21::stack<std::string> q2 = {"ghi"};

  q1.swap(q2);

  EXPECT_EQ(q1.size(), 1U);
  EXPECT_EQ(q1.top(), "ghi");

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_EQ(q2.top(), "abc");
  q2.pop();
  EXPECT_EQ(q2.top(), "def");
}

TEST(StackTest, InsertManyIntoEmpty) {
  s21::stack<int> q;
  q.insert_many_back(1, 2, 3);
  EXPECT_EQ(q.size(), 3U);
  EXPECT_EQ(q.top(), 3);
  q.pop();
  EXPECT_EQ(q.top(), 2);
  q.pop();
  EXPECT_EQ(q.top(), 1);
}

TEST(StackTest, InsertManyIntoNotEmpty_int) {
  s21::stack<int> q = {10};
  q.insert_many_back(20, 30);
  EXPECT_EQ(q.size(), 3U);
  EXPECT_EQ(q.top(), 30);
  q.pop();
  EXPECT_EQ(q.top(), 20);
  q.pop();
  EXPECT_EQ(q.top(), 10);
}

TEST(StackTest, InsertManyIntoNotEmpty_string) {
  s21::stack<std::string> q = {"how"};
  q.insert_many_back("are", "you");
  EXPECT_EQ(q.size(), 3U);
  EXPECT_EQ(q.top(), "you");
  q.pop();
  EXPECT_EQ(q.top(), "are");
  q.pop();
  EXPECT_EQ(q.top(), "how");
}

TEST(StackTest, InsertManyEmptyArgs) {
  s21::stack<int> q = {1, 2};
  q.insert_many_back();
  EXPECT_EQ(q.size(), 2U);
  EXPECT_EQ(q.top(), 1);
  q.pop();
  EXPECT_EQ(q.top(), 2);
}