#include <gtest/gtest.h>
#include "vector.hpp"

// === Constructors ===

TEST(Constructors, Default) {
  kb::Vector<int> v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0u);
  EXPECT_EQ(v.capacity(), 0u);
}

TEST(Constructors, SizeAndValue) {
  kb::Vector<int> v(5, 42);
  ASSERT_EQ(v.size(), 5u);
  EXPECT_EQ(v.capacity(), 5u);
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], 42);
  }
}

TEST(Constructors, SizeDefaultValue) {
  kb::Vector<int> v(3);
  ASSERT_EQ(v.size(), 3u);
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], 0);
  }
}

TEST(Constructors, Copy) {
  kb::Vector<int> v(3, 10);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  kb::Vector<int> copy(v);
  ASSERT_EQ(copy.size(), v.size());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(copy[i], v[i]);
  }
}

TEST(Constructors, CopyIsIndependent) {
  kb::Vector<int> v(3, 10);
  kb::Vector<int> copy(v);
  copy[0] = 999;
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(copy[0], 999);
}

// === Destructor ===

TEST(Destructor, NoLeaks) {
  kb::Vector<int>* v = new kb::Vector<int>(100, 5);
  delete v;
}

// === Assignment Operator ===

TEST(AssignmentOperator, Basic) {
  kb::Vector<int> v(3, 10);
  kb::Vector<int> v2;
  v2 = v;
  ASSERT_EQ(v2.size(), 3u);
  for (size_t i = 0; i < v2.size(); ++i) {
    EXPECT_EQ(v2[i], 10);
  }
}

TEST(AssignmentOperator, SelfAssignment) {
  kb::Vector<int> v(3, 10);
  kb::Vector<int>& ref = v;
  v = ref;
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0], 10);
}

TEST(AssignmentOperator, Independence) {
  kb::Vector<int> v(3, 10);
  kb::Vector<int> v2;
  v2 = v;
  v2[0] = 999;
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v2[0], 999);
}

// === Assign ===

TEST(Assign, Basic) {
  kb::Vector<int> v;
  v.assign(5, 7);
  ASSERT_EQ(v.size(), 5u);
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], 7);
  }
}

TEST(Assign, Overwrite) {
  kb::Vector<int> v(3, 10);
  v.assign(2, 20);
  ASSERT_EQ(v.size(), 2u);
  EXPECT_EQ(v[0], 20);
  EXPECT_EQ(v[1], 20);
}

// === Element Access ===

TEST(ElementAccess, At) {
  kb::Vector<int> v(3);
  v[0] = 10;
  v[1] = 20;
  v[2] = 30;
  EXPECT_EQ(v.at(0), 10);
  EXPECT_EQ(v.at(1), 20);
  EXPECT_EQ(v.at(2), 30);
}

TEST(ElementAccess, AtThrowsOutOfRange) {
  kb::Vector<int> v(3);
  EXPECT_THROW(v.at(3), std::runtime_error);
  EXPECT_THROW(v.at(100), std::runtime_error);
}

TEST(ElementAccess, AtConst) {
  kb::Vector<int> v(2, 5);
  const kb::Vector<int>& cv = v;
  EXPECT_EQ(cv.at(0), 5);
  EXPECT_EQ(cv.at(1), 5);
  EXPECT_THROW(cv.at(2), std::runtime_error);
}

TEST(ElementAccess, SubscriptOperator) {
  kb::Vector<int> v(3);
  v[0] = 100;
  v[1] = 200;
  v[2] = 300;
  EXPECT_EQ(v[0], 100);
  EXPECT_EQ(v[1], 200);
  EXPECT_EQ(v[2], 300);
}

TEST(ElementAccess, SubscriptConst) {
  kb::Vector<int> v(2, 42);
  const kb::Vector<int>& cv = v;
  EXPECT_EQ(cv[0], 42);
  EXPECT_EQ(cv[1], 42);
}

TEST(ElementAccess, Front) {
  kb::Vector<int> v(3);
  v[0] = 11;
  v[1] = 22;
  v[2] = 33;
  EXPECT_EQ(v.front(), 11);
}

TEST(ElementAccess, FrontConst) {
  kb::Vector<int> v(2, 99);
  const kb::Vector<int>& cv = v;
  EXPECT_EQ(cv.front(), 99);
}

TEST(ElementAccess, Back) {
  kb::Vector<int> v(3);
  v[0] = 11;
  v[1] = 22;
  v[2] = 33;
  EXPECT_EQ(v.back(), 33);
}

TEST(ElementAccess, BackConst) {
  kb::Vector<int> v(2, 77);
  const kb::Vector<int>& cv = v;
  EXPECT_EQ(cv.back(), 77);
}

TEST(ElementAccess, Data) {
  kb::Vector<int> v(3, 5);
  int* p = v.data();
  EXPECT_EQ(p[0], 5);
  EXPECT_EQ(p[1], 5);
  EXPECT_EQ(p[2], 5);
}

TEST(ElementAccess, DataConst) {
  kb::Vector<int> v(2, 8);
  const kb::Vector<int>& cv = v;
  int* p = cv.data();
  EXPECT_EQ(p[0], 8);
  EXPECT_EQ(p[1], 8);
}

// === Iterators ===

TEST(Iterators, BeginEnd) {
  kb::Vector<int> v(3);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  int* it = v.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, v.end());
}

TEST(Iterators, BeginEqualsEndForEmpty) {
  kb::Vector<int> v;
  EXPECT_EQ(v.begin(), v.end());
}

TEST(Iterators, IterateWithPointerArithmetic) {
  kb::Vector<int> v(4, 0);
  v[0] = 10;
  v[1] = 20;
  v[2] = 30;
  v[3] = 40;

  int sum = 0;
  for (int* it = v.begin(); it != v.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 100);
}

TEST(Iterators, RandomAccess) {
  kb::Vector<int> v(5, 0);
  for (size_t i = 0; i < 5; ++i) {
    v[i] = static_cast<int>(i) * 10;
  }

  int* it = v.begin();
  EXPECT_EQ(*(it + 0), 0);
  EXPECT_EQ(*(it + 1), 10);
  EXPECT_EQ(*(it + 2), 20);
  EXPECT_EQ(*(it + 3), 30);
  EXPECT_EQ(*(it + 4), 40);

  EXPECT_EQ(v.end() - v.begin(), 5);
}

// === Capacity ===

TEST(Capacity, Empty) {
  kb::Vector<int> v;
  EXPECT_TRUE(v.empty());

  kb::Vector<int> v2(3, 1);
  EXPECT_FALSE(v2.empty());
}

TEST(Capacity, Size) {
  kb::Vector<int> v;
  EXPECT_EQ(v.size(), 0u);

  kb::Vector<int> v2(10, 1);
  EXPECT_EQ(v2.size(), 10u);
}

TEST(Capacity, MaxSize) {
  kb::Vector<int> v;
  EXPECT_GT(v.max_size(), 0u);
}

TEST(Capacity, Reserve) {
  kb::Vector<int> v;
  v.reserve(100);
  EXPECT_GE(v.capacity(), 100u);
  EXPECT_EQ(v.size(), 0u);
}

TEST(Capacity, ReservePreservesData) {
  kb::Vector<int> v(3);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  v.reserve(100);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v.size(), 3u);
}

TEST(Capacity, CapacityAfterConstruction) {
  kb::Vector<int> v(5, 1);
  EXPECT_GE(v.capacity(), 5u);
}

TEST(Capacity, ShrinkToFit) {
  kb::Vector<int> v(3, 1);
  v.reserve(100);
  EXPECT_GE(v.capacity(), 100u);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), v.size());
}

TEST(Capacity, ShrinkToFitPreservesData) {
  kb::Vector<int> v(3);
  v[0] = 10;
  v[1] = 20;
  v[2] = 30;
  v.reserve(100);
  v.shrink_to_fit();
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v[2], 30);
}

// === Modifiers ===

TEST(Modifiers, Clear) {
  kb::Vector<int> v(5, 42);
  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0u);
}

TEST(Modifiers, PushBack) {
  kb::Vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(Modifiers, PushBackGrowsCapacity) {
  kb::Vector<int> v;
  for (int i = 0; i < 20; ++i) {
    v.push_back(i);
  }
  ASSERT_EQ(v.size(), 20u);
  EXPECT_GE(v.capacity(), 20u);
  for (int i = 0; i < 20; ++i) {
    EXPECT_EQ(v[i], i);
  }
}

TEST(Modifiers, PopBack) {
  kb::Vector<int> v(3);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  v.pop_back();
  EXPECT_EQ(v.size(), 2u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
}

TEST(Modifiers, ResizeGrow) {
  kb::Vector<int> v(2, 5);
  v.resize(5);
  ASSERT_EQ(v.size(), 5u);
  EXPECT_EQ(v[0], 5);
  EXPECT_EQ(v[1], 5);
  EXPECT_EQ(v[2], 0);
  EXPECT_EQ(v[3], 0);
  EXPECT_EQ(v[4], 0);
}

TEST(Modifiers, ResizeShrink) {
  kb::Vector<int> v(5, 10);
  v.resize(2);
  EXPECT_EQ(v.size(), 2u);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 10);
}

TEST(Modifiers, ResizeSameSize) {
  kb::Vector<int> v(3, 7);
  v.resize(3);
  EXPECT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0], 7);
}

TEST(Modifiers, Swap) {
  kb::Vector<int> a(3, 1);
  kb::Vector<int> b(5, 2);
  a.swap(b);
  ASSERT_EQ(a.size(), 5u);
  ASSERT_EQ(b.size(), 3u);
  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], 2);
  }
  for (size_t i = 0; i < b.size(); ++i) {
    EXPECT_EQ(b[i], 1);
  }
}

// === Mixed scenarios ===

TEST(Mixed, PushBackThenPopBack) {
  kb::Vector<int> v;
  v.push_back(10);
  v.push_back(20);
  v.push_back(30);
  v.pop_back();
  ASSERT_EQ(v.size(), 2u);
  EXPECT_EQ(v.back(), 20);
}

TEST(Mixed, ClearChecksEmpty) {
  kb::Vector<int> v(5, 42);
  EXPECT_FALSE(v.empty());
  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0u);
}

TEST(Mixed, AssignThenResize) {
  kb::Vector<int> v;
  v.assign(3, 100);
  v.resize(5);
  ASSERT_EQ(v.size(), 5u);
  EXPECT_EQ(v[0], 100);
  EXPECT_EQ(v[1], 100);
  EXPECT_EQ(v[2], 100);
}

TEST(Mixed, DoubleType) {
  kb::Vector<double> v;
  v.push_back(1.5);
  v.push_back(2.5);
  v.push_back(3.5);
  ASSERT_EQ(v.size(), 3u);
  EXPECT_DOUBLE_EQ(v[0], 1.5);
  EXPECT_DOUBLE_EQ(v[1], 2.5);
  EXPECT_DOUBLE_EQ(v[2], 3.5);
}
