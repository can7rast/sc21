#include "test_run.h"

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int> arr;
  size_t correct_size = 0;
  EXPECT_EQ(arr.size(), correct_size);
  EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, InitializerListConstructor) {
  s21::array<int> arr{10, 20, 30, 40};
  size_t correct_size = 4;
  EXPECT_EQ(arr.size(), correct_size);
  EXPECT_EQ(arr[0], 10);
  EXPECT_EQ(arr[1], 20);
  EXPECT_EQ(arr[2], 30);
  EXPECT_EQ(arr[3], 40);
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int> arr{10, 20, 30, 40};
  s21::array<int> copyarr(arr);
  size_t correct_size = 4;
  EXPECT_EQ(copyarr.size(), correct_size);
  EXPECT_EQ(arr[0], copyarr[0]);
  EXPECT_EQ(arr[1], copyarr[1]);
  EXPECT_EQ(arr[2], copyarr[2]);
  EXPECT_EQ(arr[3], copyarr[3]);
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<int> arr{10, 20, 30, 40};
  s21::array<int> copyarr(std::move(arr));
  size_t correct_size = 4;
  EXPECT_EQ(copyarr.size(), correct_size);
  EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, MoveOperatorEq) {
  s21::array<int> arr{10, 20, 30, 40};
  s21::array<int> copyarr(std::move(arr));
  size_t correct_size = 4;
  EXPECT_EQ(copyarr.size(), correct_size);
  correct_size = 0;
  EXPECT_EQ(arr.size(), correct_size);
  EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, atMethod) {
  s21::array<int> arr{10, 20, 30, 15, 50, 44};
  EXPECT_ANY_THROW(arr.at(8));
  s21::array<int>::reference ref = arr.at(4);
  EXPECT_EQ(ref, 50);
}

TEST(ArrayTest, AppealMasMethod) {
  s21::array<int> arr{10, 20, 30, 15, 50, 44};
  int* mas = arr.data();
  EXPECT_EQ(arr[0], mas[0]);
  EXPECT_EQ(arr[1], mas[1]);
  EXPECT_EQ(arr[2], mas[2]);
  EXPECT_EQ(arr[3], mas[3]);
  EXPECT_EQ(arr[4], mas[4]);
  EXPECT_EQ(arr[5], mas[5]);
}

TEST(ArrayTest, ReturnSizesMethods) {
  s21::array<int> arr{10, 20, 30, 15, 50, 44};
  EXPECT_EQ(arr.size(), arr.max_size());
}

TEST(ArrayTest, TestFrontBack) {
  s21::array<std::string> string_array = {"one", "two", "three", "four",
                                          "five"};
  ASSERT_EQ(string_array.front(), "one");
  ASSERT_EQ(string_array.back(), "five");
}

TEST(ArrayTest, TestBeginEnd) {
  s21::array<double> double_array = {1.1, 2.2, 3.3, 4.4, 5.5};
  ASSERT_NE(double_array.begin(), double_array.end());
}

TEST(ArrayTest, FillMethods) {
  s21::array<int> arr{10, 20, 30, 44};
  EXPECT_EQ(arr[0], 10);
  EXPECT_EQ(arr[1], 20);
  EXPECT_EQ(arr[2], 30);
  EXPECT_EQ(arr[3], 44);
  arr.fill(5);
  EXPECT_EQ(arr[0], 5);
  EXPECT_EQ(arr[1], 5);
  EXPECT_EQ(arr[2], 5);
  EXPECT_EQ(arr[3], 5);
}

TEST(ArrayTest, TestSwap) {
  s21::array<int> int_array1 = {1, 2, 3, 4};
  s21::array<int> int_array2 = {6, 7, 8, 9};
  ASSERT_NO_THROW(int_array1.swap(int_array2));

  s21::array<double> double_array1 = {1.1, 2.2, 3.3, 4.4};
  s21::array<double> double_array2 = {6.6, 7.7, 8.8, 9.9};
  ASSERT_NO_THROW(double_array1.swap(double_array2));

  s21::array<std::string> string_array1 = {"one", "two", "three", "four"};
  s21::array<std::string> string_array2 = {"six", "seven", "eight", "nine"};
  ASSERT_NO_THROW(string_array1.swap(string_array2));
}