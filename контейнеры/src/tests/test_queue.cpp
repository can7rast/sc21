#include "test_run.h"

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0U);
}

TEST(QueueTest, InitializerListConstructor_int) {
  s21::queue<int> q = {1, 2, 3};
  EXPECT_EQ(q.size(), 3U);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, InitializerListConstructor_float) {
  s21::queue<float> q = {1.5, 2.6, 3.7};
  EXPECT_EQ(q.size(), 3U);
  EXPECT_FLOAT_EQ(q.front(), 1.5);
  EXPECT_FLOAT_EQ(q.back(), 3.7);
}

TEST(QueueTest, InitializerListConstructor_string) {
  s21::queue<std::string> q = {"Hi", "my", "name"};
  EXPECT_EQ(q.size(), 3U);
  EXPECT_EQ(q.front(), "Hi");
  EXPECT_EQ(q.back(), "name");
}

TEST(QueueTest, CopyConstructor_int) {
  s21::queue<int> q1 = {10, 20, 30};
  s21::queue<int> q2(q1);

  EXPECT_EQ(q2.size(), 3U);
  EXPECT_EQ(q2.front(), 10);
  q2.pop();
  EXPECT_EQ(q2.front(), 20);
  EXPECT_EQ(q2.back(), 30);

  EXPECT_FALSE(q1.empty());
}

TEST(QueueTest, CopyConstructor_float) {
  s21::queue<float> q1 = {10.1, 20.2, 30.3};
  s21::queue<float> q2(q1);

  EXPECT_EQ(q2.size(), 3U);
  EXPECT_FLOAT_EQ(q2.front(), 10.1);
  q2.pop();
  EXPECT_FLOAT_EQ(q2.front(), 20.2);
  EXPECT_FLOAT_EQ(q2.back(), 30.3);

  EXPECT_FALSE(q1.empty());
}

TEST(QueueTest, CopyConstructor_string) {
  s21::queue<std::string> q1 = {"How", "are", "you"};
  s21::queue<std::string> q2(q1);

  EXPECT_EQ(q2.size(), 3U);
  EXPECT_EQ(q2.front(), "How");
  q2.pop();
  EXPECT_EQ(q2.front(), "are");
  EXPECT_EQ(q2.back(), "you");

  EXPECT_FALSE(q1.empty());
}

TEST(QueueTest, MoveConstructor_int) {
  s21::queue<int> q1 = {7, 8, 9};
  s21::queue<int> q2(std::move(q1));

  EXPECT_EQ(q2.size(), 3U);
  EXPECT_EQ(q2.front(), 7);
  q2.pop();
  EXPECT_EQ(q2.front(), 8);
  EXPECT_EQ(q2.back(), 9);

  EXPECT_TRUE(q1.empty());
}

TEST(QueueTest, MoveConstructor_float) {
  s21::queue<float> q1 = {7.7, 8.8, 9.9};
  s21::queue<float> q2(std::move(q1));

  EXPECT_EQ(q2.size(), 3U);
  EXPECT_FLOAT_EQ(q2.front(), 7.7);
  q2.pop();
  EXPECT_FLOAT_EQ(q2.front(), 8.8);
  EXPECT_FLOAT_EQ(q2.back(), 9.9);

  EXPECT_TRUE(q1.empty());
}

TEST(QueueTest, MoveConstructor_string) {
  s21::queue<std::string> q1 = {"This", "is", "test"};
  s21::queue<std::string> q2(std::move(q1));

  EXPECT_EQ(q2.size(), 3U);
  EXPECT_EQ(q2.front(), "This");
  q2.pop();
  EXPECT_EQ(q2.front(), "is");
  EXPECT_EQ(q2.back(), "test");

  EXPECT_TRUE(q1.empty());
}

TEST(QueueTest, CopyAssignment_int) {
  s21::queue<int> q1 = {1, 2};
  s21::queue<int> q2;
  q2 = q1;

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 2);

  EXPECT_FALSE(q1.empty());
}

TEST(QueueTest, CopyAssignment_float) {
  s21::queue<float> q1 = {1.5, 2.5};
  s21::queue<float> q2;
  q2 = q1;

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_FLOAT_EQ(q2.front(), 1.5);
  EXPECT_FLOAT_EQ(q2.back(), 2.5);

  EXPECT_FALSE(q1.empty());
}

TEST(QueueTest, CopyAssignment_string) {
  s21::queue<std::string> q1 = {"school", "21"};
  s21::queue<std::string> q2;
  q2 = q1;

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_EQ(q2.front(), "school");
  EXPECT_EQ(q2.back(), "21");

  EXPECT_FALSE(q1.empty());
}

TEST(QueueTest, MoveAssignment_int) {
  s21::queue<int> q1 = {100, 200};
  s21::queue<int> q2;
  q2 = std::move(q1);

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_EQ(q2.front(), 100);
  EXPECT_EQ(q2.back(), 200);

  EXPECT_TRUE(q1.empty());
}

TEST(QueueTest, MoveAssignment_float) {
  s21::queue<float> q1 = {100.123, 200.456};
  s21::queue<float> q2;
  q2 = std::move(q1);

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_FLOAT_EQ(q2.front(), 100.123);
  EXPECT_FLOAT_EQ(q2.back(), 200.456);

  EXPECT_TRUE(q1.empty());
}

TEST(QueueTest, MoveAssignment_string) {
  s21::queue<std::string> q1 = {"abc", "def"};
  s21::queue<std::string> q2;
  q2 = std::move(q1);

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_EQ(q2.front(), "abc");
  EXPECT_EQ(q2.back(), "def");

  EXPECT_TRUE(q1.empty());
}

TEST(QueueTest, PushAndPop_int) {
  s21::queue<int> q;
  q.push(5);
  q.push(10);
  EXPECT_EQ(q.front(), 5);
  EXPECT_EQ(q.back(), 10);
  EXPECT_EQ(q.size(), 2U);

  q.pop();
  EXPECT_EQ(q.front(), 10);
  EXPECT_EQ(q.size(), 1U);

  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, PushAndPop_float) {
  s21::queue<float> q;
  q.push(5.1);
  q.push(10.2);
  EXPECT_FLOAT_EQ(q.front(), 5.1);
  EXPECT_FLOAT_EQ(q.back(), 10.2);
  EXPECT_EQ(q.size(), 2U);

  q.pop();
  EXPECT_FLOAT_EQ(q.front(), 10.2);
  EXPECT_EQ(q.size(), 1U);

  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, PushAndPop_string) {
  s21::queue<std::string> q;
  q.push("Love");
  q.push("is");
  EXPECT_EQ(q.front(), "Love");
  EXPECT_EQ(q.back(), "is");
  EXPECT_EQ(q.size(), 2U);

  q.pop();
  EXPECT_EQ(q.front(), "is");
  EXPECT_EQ(q.size(), 1U);

  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, Swap_int) {
  s21::queue<int> q1 = {1, 2};
  s21::queue<int> q2 = {9};

  q1.swap(q2);

  EXPECT_EQ(q1.size(), 1U);
  EXPECT_EQ(q1.front(), 9);

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 2);
}

TEST(QueueTest, Swap_float) {
  s21::queue<float> q1 = {1.1, 2.2};
  s21::queue<float> q2 = {9.3};

  q1.swap(q2);

  EXPECT_EQ(q1.size(), 1U);
  EXPECT_FLOAT_EQ(q1.front(), 9.3);

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_FLOAT_EQ(q2.front(), 1.1);
  EXPECT_FLOAT_EQ(q2.back(), 2.2);
}

TEST(QueueTest, Swap_string) {
  s21::queue<std::string> q1 = {"abc", "def"};
  s21::queue<std::string> q2 = {"ghi"};

  q1.swap(q2);

  EXPECT_EQ(q1.size(), 1U);
  EXPECT_EQ(q1.front(), "ghi");

  EXPECT_EQ(q2.size(), 2U);
  EXPECT_EQ(q2.front(), "abc");
  EXPECT_EQ(q2.back(), "def");
}

TEST(QueueTest, InsertManyIntoEmpty) {
  s21::queue<int> q;
  q.insert_many_back(1, 2, 3);
  EXPECT_EQ(q.size(), 3U);
  EXPECT_EQ(q.front(), 1);
  q.pop();
  EXPECT_EQ(q.front(), 2);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, InsertManyIntoNotEmpty_int) {
  s21::queue<int> q = {10};
  q.insert_many_back(20, 30);
  EXPECT_EQ(q.size(), 3U);
  EXPECT_EQ(q.front(), 10);
  q.pop();
  EXPECT_EQ(q.front(), 20);
  EXPECT_EQ(q.back(), 30);
}

TEST(QueueTest, InsertManyIntoNotEmpty_string) {
  s21::queue<std::string> q = {"ab"};
  q.insert_many_back("cd", "ef");
  EXPECT_EQ(q.size(), 3U);
  EXPECT_EQ(q.front(), "ab");
  q.pop();
  EXPECT_EQ(q.front(), "cd");
  EXPECT_EQ(q.back(), "ef");
}

TEST(QueueTest, InsertManyEmptyArgs) {
  s21::queue<int> q = {1, 2};
  q.insert_many_back();
  EXPECT_EQ(q.size(), 2U);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 2);
}