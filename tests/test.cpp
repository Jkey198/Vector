#include <gtest/gtest.h>
#include "vector.hpp"
#include <numeric>
#include <algorithm>
#include <functional>

static int square(int x) { return x * x; }
static bool is_even(int x) { return x % 2 == 0; }

TEST(Numeric, Accumulate) {
  kb::Vector<int> v(5);
  for (int i = 0; i < 5; ++i) v[i] = i + 1;

  int sum = std::accumulate(v.begin(), v.end(), 0);
  EXPECT_EQ(sum, 15);

  int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());
  EXPECT_EQ(product, 120);
}

TEST(Numeric, InnerProduct) {
  kb::Vector<int> a(3), b(3);
  a[0] = 1; a[1] = 2; a[2] = 3;
  b[0] = 4; b[1] = 5; b[2] = 6;

  int dot = std::inner_product(a.begin(), a.end(), b.begin(), 0);
  EXPECT_EQ(dot, 32);
}

TEST(Numeric, PartialSum) {
  kb::Vector<int> v(4);
  v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;

  kb::Vector<int> result(4);
  std::partial_sum(v.begin(), v.end(), result.begin());

  EXPECT_EQ(result[0], 1);
  EXPECT_EQ(result[1], 3);
  EXPECT_EQ(result[2], 6);
  EXPECT_EQ(result[3], 10);
}

TEST(Numeric, AdjacentDifference) {
  kb::Vector<int> v(4);
  v[0] = 2; v[1] = 5; v[2] = 9; v[3] = 14;

  kb::Vector<int> result(4);
  std::adjacent_difference(v.begin(), v.end(), result.begin());

  EXPECT_EQ(result[0], 2);
  EXPECT_EQ(result[1], 3);
  EXPECT_EQ(result[2], 4);
  EXPECT_EQ(result[3], 5);
}

TEST(Algorithm, Sort) {
  kb::Vector<int> v(5);
  v[0] = 5; v[1] = 3; v[2] = 1; v[3] = 4; v[4] = 2;

  std::sort(v.begin(), v.end());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(v[i], i + 1);
  }

  std::sort(v.begin(), v.end(), std::greater<int>());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(v[i], 5 - i);
  }
}

TEST(Algorithm, FindAndCount) {
  kb::Vector<int> v(6);
  v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 2; v[4] = 4; v[5] = 2;

  kb::Vector<int>::iterator it = std::find(v.begin(), v.end(), 3);
  ASSERT_NE(it, v.end());
  EXPECT_EQ(it - v.begin(), 2);
  EXPECT_EQ(std::find(v.begin(), v.end(), 99), v.end());

  EXPECT_EQ(std::count(v.begin(), v.end(), 2), 3);
  EXPECT_EQ(std::count_if(v.begin(), v.end(), is_even), 4);
}

TEST(Algorithm, CopyAndEqual) {
  kb::Vector<int> src(4);
  src[0] = 10; src[1] = 20; src[2] = 30; src[3] = 40;

  kb::Vector<int> dst(4);
  std::copy(src.begin(), src.end(), dst.begin());
  EXPECT_TRUE(std::equal(src.begin(), src.end(), dst.begin()));

  kb::Vector<int> rev(4);
  std::reverse_copy(src.begin(), src.end(), rev.begin());
  EXPECT_EQ(rev[0], 40);
  EXPECT_EQ(rev[3], 10);
}

TEST(Algorithm, Reverse) {
  kb::Vector<int> v(5);
  for (int i = 0; i < 5; ++i) v[i] = i + 1;

  std::reverse(v.begin(), v.end());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(v[i], 5 - i);
  }
}

TEST(Algorithm, Transform) {
  kb::Vector<int> v(4);
  v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;

  kb::Vector<int> result(4);
  std::transform(v.begin(), v.end(), result.begin(), square);

  EXPECT_EQ(result[0], 1);
  EXPECT_EQ(result[1], 4);
  EXPECT_EQ(result[2], 9);
  EXPECT_EQ(result[3], 16);
}

TEST(Algorithm, MinMaxElement) {
  kb::Vector<int> v(5);
  v[0] = 30; v[1] = 10; v[2] = 50; v[3] = 20; v[4] = 40;

  EXPECT_EQ(*std::min_element(v.begin(), v.end()), 10);
  EXPECT_EQ(*std::max_element(v.begin(), v.end()), 50);
  EXPECT_EQ(std::min_element(v.begin(), v.end()) - v.begin(), 1);
  EXPECT_EQ(std::max_element(v.begin(), v.end()) - v.begin(), 2);
}

TEST(Algorithm, FillAndReplace) {
  kb::Vector<int> v(6);
  std::fill(v.begin(), v.end(), 0);
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], 0);
  }

  std::fill(v.begin(), v.begin() + 3, 5);
  std::replace(v.begin(), v.end(), 0, 10);

  EXPECT_EQ(v[0], 5);
  EXPECT_EQ(v[2], 5);
  EXPECT_EQ(v[3], 10);
  EXPECT_EQ(v[5], 10);
}

TEST(Algorithm, SortAndBinarySearch) {
  kb::Vector<int> v(6);
  v[0] = 40; v[1] = 10; v[2] = 30; v[3] = 50; v[4] = 20; v[5] = 60;

  std::sort(v.begin(), v.end());

  EXPECT_TRUE(std::binary_search(v.begin(), v.end(), 30));
  EXPECT_FALSE(std::binary_search(v.begin(), v.end(), 35));

  kb::Vector<int>::iterator lb = std::lower_bound(v.begin(), v.end(), 25);
  EXPECT_EQ(*lb, 30);
}

TEST(Algorithm, UniqueAfterSort) {
  kb::Vector<int> v(8);
  v[0] = 3; v[1] = 1; v[2] = 2; v[3] = 3;
  v[4] = 1; v[5] = 2; v[6] = 4; v[7] = 1;

  std::sort(v.begin(), v.end());
  kb::Vector<int>::iterator new_end = std::unique(v.begin(), v.end());
  size_t unique_count = static_cast<size_t>(new_end - v.begin());

  EXPECT_EQ(unique_count, 4u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
}
