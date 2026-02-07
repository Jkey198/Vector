#include <gtest/gtest.h>
#include "vector.hpp"

TEST(constructors, default) {
  kb::Vector<int> v;
  EXPECT_EQ(v.empty(), true) << "not empty";
}

TEST(constructors, parameter) {
  kb::Vector<int> v(2, 40);
  ASSERT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], 40);
  EXPECT_EQ(v[1], 40);
}

TEST(constructors, copy) {
  kb::Vector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  kb::Vector<int> v1(v);
  ASSERT_EQ(v1[0], v[0]) << "not copy\n";
  ASSERT_EQ(v1[1], v[1]) << "not copy\n";
  ASSERT_EQ(v1[2], v[2]) << "not copy";
}

TEST(destructor, default) {
  
}
