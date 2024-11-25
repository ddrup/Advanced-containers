#include <gtest/gtest.h>

#include <string>

#include "s21_containers.h"

using namespace s21;

TEST(Vector, construct_1) {
  Vector<int> vec(10);

  EXPECT_EQ(vec.size(), 10);
  EXPECT_EQ(vec.capacity(), 10);
}

TEST(Vector, construct_2) {
  Vector<int> vec(3, 5);
  Vector<int> res = vec;

  EXPECT_EQ(vec, res);
}

TEST(Vector, construct_3) {
  Vector<int> vec(2, 5);
  Vector<int> res{5, 5};

  EXPECT_EQ(vec, res);
}

TEST(Vector, construct_4) {
  Vector<int> vec(2, 5);
  Vector<int> res{5, 5};

  res = vec;

  EXPECT_EQ(vec, res);
}

TEST(Vector, construct_5) {
  Vector<int> vec(2, 5);
  Vector<int> res{5, 5, 5, 5, 5};

  res = vec;

  EXPECT_EQ(vec, res);
}

TEST(Vector, construct_6) {
  Vector<int> vec(2, 5);
  Vector<int> vec1(2, 5);
  Vector<int> res(std::move(vec));

  EXPECT_EQ(vec1, res);
}

TEST(Vector, move) {
  Vector<int> vec(2, 5);
  Vector<int> vec1(2, 5);
  Vector<int> res(2,5);
  
  res = std::move(vec);

  EXPECT_EQ(vec1, res);
}

TEST(Vector, at) {
  Vector<int> vec{1,2,3,4,5,6};
  const Vector<int> vec1{1,2,3};

  EXPECT_EQ(vec.at(2), 3);
  EXPECT_EQ(vec1[1], 2);
  EXPECT_EQ(vec1.at(2), 3);
  EXPECT_THROW(vec.at(10), std::out_of_range);
  EXPECT_THROW(vec1.at(10), std::out_of_range);
}

TEST(Vector, resize) {
  Vector<int> vec{1,2,3,4,5,6};
  Vector<int> res{1,2,3,4,4};

  vec.resize(3);
  vec.resize(5, 4);

  EXPECT_EQ(vec, res);
}

TEST(Vector, back) {
  Vector<int> vec{1,2,3,4,5,6};
  Vector<int> res{1,2,3,4,10, 666};

  int x = 666;
  vec.pop_back();
  vec.pop_back();
  vec.push_back(10);
  vec.push_back(x);

  EXPECT_EQ(vec, res);
}

TEST(Vector, value) {
  Vector<int> vec{1,2,3,4,5,6};
  int* ptr = static_cast<int *>(&vec[0]);

  EXPECT_EQ(vec.front(), 1);
  EXPECT_EQ(vec.back(), 6);
  EXPECT_EQ(vec.data(), ptr);
}

TEST(Vector, empty) {
  Vector<int> vec{1,2,3,4,5,6};
  
  vec.clear();

  EXPECT_EQ(vec.empty(), 1);

  vec.push_back(1);

  EXPECT_EQ(vec.empty(), 0);
}

TEST(Vector, shrink) {
  Vector<int> vec{1,2,3,4,5,6};
  
  vec.push_back(1);

  EXPECT_TRUE(vec.capacity() != vec.size());

  vec.shrink_to_fit();

  EXPECT_TRUE(vec.capacity() == vec.size());
}

TEST(Vector, insert_lvalue) {
  Vector<int> vec{1, 2, 3, 4};
  Vector<int> res{54, 1, -4, 2, 3, 4, 666};

  int x = 54;
  int y = -4;
  int z = 666;
  Vector<int>::iterator it = vec.insert(vec.begin(), x);
  EXPECT_EQ(*it, *vec.begin());
  vec.insert(vec.begin() + 2, y);
  vec.insert(vec.end(), z);

  EXPECT_EQ(vec, res);
}

TEST(Vector, insert_rvalue) {
  Vector<std::string> vec{"abc", "xyz"};
  Vector<std::string> res{"xxx", "abc", "uuu", "xyz", "lll"};

  std::string s1 = "xxx";
  std::string s2 = "uuu";
  std::string s3 = "lll";

  vec.insert(vec.begin(), std::move(s1));
  vec.insert(vec.begin() + 2, std::move(s2));
  vec.insert(vec.end(), std::move(s3));

  EXPECT_EQ(vec, res);
}

TEST(Vector, insert_count) {
  Vector<int> vec{1, 2, 3, 4};
  Vector<int> res{5, 5, 5, 1, -4, -4, 2, 3, 4, 666, 666, 666, 666, 666};

  vec.insert(vec.begin(), 3, 5);
  vec.insert(vec.begin() + 4, 2, -4);
  vec.insert(vec.end(), 5, 666);

  EXPECT_EQ(vec, res);
}

TEST(Vector, emplace) {
  s21::Vector<std::string> container;
  s21::Vector<std::string> res{"one", "two", "three"};

  container.reserve(10);
  std::string two{"two"};
  std::string three{"three"};

  container.emplace(container.end(), "one");
  container.emplace(container.end(), two);
  container.emplace(container.end(), std::move(three));

  EXPECT_EQ(container, res);
}

TEST(Vector, erase) {
  Vector<int> vec{1, 2, 3, 4};
  Vector<int> res{2};

  Vector<int>::iterator it = vec.erase(vec.begin());
  EXPECT_EQ(it, vec.begin());

  it = vec.erase(vec.begin() + 1);
  EXPECT_EQ(it, std::next(vec.begin()));

  it = vec.erase(std::prev(vec.end()));
  EXPECT_EQ(it, vec.end());

  EXPECT_EQ(vec, res);
}

TEST(Vector, erase_range_1) {
  Vector<int> vec{1, 2, 3, 4, 5, 6, 7};
  Vector<int> res{3, 4};

  Vector<int>::iterator it = vec.erase(vec.cbegin() + 4, vec.cend());
  EXPECT_EQ(it, vec.end());

  it = vec.erase(vec.begin(), vec.begin() + 2);
  EXPECT_EQ(it, vec.begin());

  EXPECT_EQ(vec, res);
}

TEST(Vector, erase_range_2) {
  Vector<int> vec{1, 2, 3, 4, 5, 6, 7};
  Vector<int> res{1, 2, 7};

  Vector<int>::iterator it = vec.erase(vec.cbegin() + 2, std::prev(vec.cend()));
  EXPECT_EQ(it, std::prev(vec.end()));

  EXPECT_EQ(vec, res);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
