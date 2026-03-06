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

// === Iterator Range Constructor ===

TEST(IteratorRangeConstructor, FromArray) {
  int arr[] = {10, 20, 30, 40, 50};
  kb::Vector<int> v(arr, arr + 5);
  ASSERT_EQ(v.size(), 5u);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v[2], 30);
  EXPECT_EQ(v[3], 40);
  EXPECT_EQ(v[4], 50);
}

TEST(IteratorRangeConstructor, FromVectorIterators) {
  kb::Vector<int> src(3, 0);
  src[0] = 1;
  src[1] = 2;
  src[2] = 3;

  kb::Vector<int> v(src.begin(), src.end());
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(IteratorRangeConstructor, EmptyRange) {
  int arr[] = {1};
  kb::Vector<int> v(arr, arr);
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0u);
}

TEST(IteratorRangeConstructor, SingleElement) {
  int arr[] = {42};
  kb::Vector<int> v(arr, arr + 1);
  ASSERT_EQ(v.size(), 1u);
  EXPECT_EQ(v[0], 42);
}

TEST(IteratorRangeConstructor, SubRange) {
  int arr[] = {10, 20, 30, 40, 50};
  kb::Vector<int> v(arr + 1, arr + 4);
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0], 20);
  EXPECT_EQ(v[1], 30);
  EXPECT_EQ(v[2], 40);
}

TEST(IteratorRangeConstructor, IsIndependentFromSource) {
  int arr[] = {1, 2, 3};
  kb::Vector<int> v(arr, arr + 3);
  arr[0] = 999;
  EXPECT_EQ(v[0], 1);
}

// === Iterator Range Assign ===

TEST(IteratorRangeAssign, FromArray) {
  int arr[] = {5, 10, 15};
  kb::Vector<int> v;
  v.assign(arr, arr + 3);
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0], 5);
  EXPECT_EQ(v[1], 10);
  EXPECT_EQ(v[2], 15);
}

TEST(IteratorRangeAssign, OverwriteExisting) {
  kb::Vector<int> v(5, 99);
  int arr[] = {1, 2};
  v.assign(arr, arr + 2);
  ASSERT_EQ(v.size(), 2u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
}

TEST(IteratorRangeAssign, EmptyRange) {
  kb::Vector<int> v(3, 10);
  int arr[] = {1};
  v.assign(arr, arr);
  EXPECT_EQ(v.size(), 0u);
  EXPECT_TRUE(v.empty());
}

TEST(IteratorRangeAssign, FromVectorIterators) {
  kb::Vector<int> src(4, 0);
  src[0] = 10;
  src[1] = 20;
  src[2] = 30;
  src[3] = 40;

  kb::Vector<int> v;
  v.assign(src.begin(), src.end());
  ASSERT_EQ(v.size(), 4u);
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], src[i]);
  }
}

TEST(IteratorRangeAssign, SingleElement) {
  int arr[] = {77};
  kb::Vector<int> v(10, 0);
  v.assign(arr, arr + 1);
  ASSERT_EQ(v.size(), 1u);
  EXPECT_EQ(v[0], 77);
}

// === Const Iterators ===

TEST(ConstIterators, BeginEndConst) {
  kb::Vector<int> v(3, 0);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  const kb::Vector<int>& cv = v;

  const int* it = cv.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, cv.end());
}

TEST(ConstIterators, EmptyConstVector) {
  const kb::Vector<int> cv;
  EXPECT_EQ(cv.begin(), cv.end());
}

TEST(ConstIterators, IterateConstVector) {
  kb::Vector<int> v(4, 0);
  v[0] = 10;
  v[1] = 20;
  v[2] = 30;
  v[3] = 40;
  const kb::Vector<int>& cv = v;

  int sum = 0;
  for (const int* it = cv.begin(); it != cv.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 100);
}

TEST(ConstIterators, ConstIteratorDistance) {
  kb::Vector<int> v(5, 1);
  const kb::Vector<int>& cv = v;
  EXPECT_EQ(cv.end() - cv.begin(), 5);
}

// === Reverse Iterators ===

TEST(ReverseIterators, RbeginRend) {
  kb::Vector<int> v(3, 0);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  kb::Vector<int>::reverse_iterator rit = v.rbegin();
  EXPECT_EQ(*rit, 3);
  ++rit;
  EXPECT_EQ(*rit, 2);
  ++rit;
  EXPECT_EQ(*rit, 1);
  ++rit;
  EXPECT_TRUE(rit == v.rend());
}

TEST(ReverseIterators, EmptyVector) {
  kb::Vector<int> v;
  EXPECT_TRUE(v.rbegin() == v.rend());
}

TEST(ReverseIterators, SingleElement) {
  kb::Vector<int> v(1, 42);
  kb::Vector<int>::reverse_iterator rit = v.rbegin();
  EXPECT_EQ(*rit, 42);
  ++rit;
  EXPECT_TRUE(rit == v.rend());
}

TEST(ReverseIterators, ModifyThroughReverseIterator) {
  kb::Vector<int> v(3, 0);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  *v.rbegin() = 99;
  EXPECT_EQ(v[2], 99);
}

TEST(ReverseIterators, ReverseSum) {
  kb::Vector<int> v(4, 0);
  v[0] = 10;
  v[1] = 20;
  v[2] = 30;
  v[3] = 40;

  int sum = 0;
  for (kb::Vector<int>::reverse_iterator rit = v.rbegin(); rit != v.rend(); ++rit) {
    sum += *rit;
  }
  EXPECT_EQ(sum, 100);
}

// === Const Reverse Iterators ===

TEST(ConstReverseIterators, RbeginRendConst) {
  kb::Vector<int> v(3, 0);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  const kb::Vector<int>& cv = v;

  kb::Vector<int>::const_reverse_iterator rit = cv.rbegin();
  EXPECT_EQ(*rit, 3);
  ++rit;
  EXPECT_EQ(*rit, 2);
  ++rit;
  EXPECT_EQ(*rit, 1);
  ++rit;
  EXPECT_TRUE(rit == cv.rend());
}

TEST(ConstReverseIterators, EmptyConstVector) {
  const kb::Vector<int> cv;
  EXPECT_TRUE(cv.rbegin() == cv.rend());
}

TEST(ConstReverseIterators, ConstReverseSum) {
  kb::Vector<int> v(4, 0);
  v[0] = 10;
  v[1] = 20;
  v[2] = 30;
  v[3] = 40;
  const kb::Vector<int>& cv = v;

  int sum = 0;
  for (kb::Vector<int>::const_reverse_iterator rit = cv.rbegin(); rit != cv.rend(); ++rit) {
    sum += *rit;
  }
  EXPECT_EQ(sum, 100);
}

// === Insert (single element) ===

TEST(InsertSingle, AtBeginning) {
  kb::Vector<int> v(3, 0);
  v[0] = 2;
  v[1] = 3;
  v[2] = 4;

  kb::Vector<int>::iterator it = v.insert(v.begin(), 1);
  ASSERT_EQ(v.size(), 4u);
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(it, v.begin());
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
}

TEST(InsertSingle, AtEnd) {
  kb::Vector<int> v(3, 0);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  kb::Vector<int>::iterator it = v.insert(v.end(), 4);
  ASSERT_EQ(v.size(), 4u);
  EXPECT_EQ(*it, 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
}

TEST(InsertSingle, InMiddle) {
  kb::Vector<int> v(3, 0);
  v[0] = 1;
  v[1] = 3;
  v[2] = 4;

  kb::Vector<int>::iterator it = v.insert(v.begin() + 1, 2);
  ASSERT_EQ(v.size(), 4u);
  EXPECT_EQ(*it, 2);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
}

TEST(InsertSingle, IntoEmptyVector) {
  kb::Vector<int> v;
  kb::Vector<int>::iterator it = v.insert(v.begin(), 42);
  ASSERT_EQ(v.size(), 1u);
  EXPECT_EQ(*it, 42);
  EXPECT_EQ(v[0], 42);
}

TEST(InsertSingle, TriggersReallocation) {
  kb::Vector<int> v;
  v.push_back(1);
  v.push_back(3);
  size_t old_cap = v.capacity();

  while (v.size() < v.capacity()) {
    v.push_back(99);
  }
  // vector is now full
  v.insert(v.begin() + 1, 2);
  EXPECT_GT(v.capacity(), old_cap);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
}

TEST(InsertSingle, MultipleInserts) {
  kb::Vector<int> v;
  v.insert(v.begin(), 3);
  v.insert(v.begin(), 2);
  v.insert(v.begin(), 1);
  v.insert(v.end(), 4);
  v.insert(v.end(), 5);
  ASSERT_EQ(v.size(), 5u);
  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(v[i], static_cast<int>(i) + 1);
  }
}

// === Insert (range) ===

TEST(InsertRange, AtBeginning) {
  kb::Vector<int> v(3, 0);
  v[0] = 3;
  v[1] = 4;
  v[2] = 5;

  int arr[] = {1, 2};
  v.insert(v.begin(), arr, arr + 2);
  ASSERT_EQ(v.size(), 5u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
}

TEST(InsertRange, AtEnd) {
  kb::Vector<int> v(3, 0);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  int arr[] = {4, 5};
  v.insert(v.end(), arr, arr + 2);
  ASSERT_EQ(v.size(), 5u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
}

TEST(InsertRange, InMiddle) {
  kb::Vector<int> v(2, 0);
  v[0] = 1;
  v[1] = 4;

  int arr[] = {2, 3};
  v.insert(v.begin() + 1, arr, arr + 2);
  ASSERT_EQ(v.size(), 4u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
}

TEST(InsertRange, EmptyRange) {
  kb::Vector<int> v(3, 10);
  int arr[] = {1};
  v.insert(v.begin(), arr, arr);
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0], 10);
}

TEST(InsertRange, IntoEmptyVector) {
  kb::Vector<int> v;
  int arr[] = {1, 2, 3};
  v.insert(v.begin(), arr, arr + 3);
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(InsertRange, SingleElementRange) {
  kb::Vector<int> v(2, 0);
  v[0] = 1;
  v[1] = 3;

  int arr[] = {2};
  v.insert(v.begin() + 1, arr, arr + 1);
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(InsertRange, TriggersReallocation) {
  kb::Vector<int> v;
  v.push_back(1);
  // fill to capacity
  while (v.size() < v.capacity()) {
    v.push_back(0);
  }
  size_t old_cap = v.capacity();

  int arr[] = {10, 20, 30, 40, 50};
  v.insert(v.end(), arr, arr + 5);
  EXPECT_GT(v.capacity(), old_cap);
  EXPECT_EQ(v[0], 1);
}

TEST(InsertRange, LargeRangeInsert) {
  kb::Vector<int> v;
  v.push_back(0);
  v.push_back(99);

  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  v.insert(v.begin() + 1, arr, arr + 10);
  ASSERT_EQ(v.size(), 12u);
  EXPECT_EQ(v[0], 0);
  for (int i = 1; i <= 10; ++i) {
    EXPECT_EQ(v[i], i);
  }
  EXPECT_EQ(v[11], 99);
}

// === Erase (single element) ===

TEST(EraseSingle, First) {
  kb::Vector<int> v(3, 0);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  kb::Vector<int>::iterator it = v.erase(v.begin());
  ASSERT_EQ(v.size(), 2u);
  EXPECT_EQ(*it, 2);
  EXPECT_EQ(it, v.begin());
  EXPECT_EQ(v[0], 2);
  EXPECT_EQ(v[1], 3);
}

TEST(EraseSingle, Last) {
  kb::Vector<int> v(3, 0);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  kb::Vector<int>::iterator it = v.erase(v.end() - 1);
  ASSERT_EQ(v.size(), 2u);
  EXPECT_EQ(it, v.end());
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
}

TEST(EraseSingle, Middle) {
  kb::Vector<int> v(4, 0);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  v[3] = 4;

  kb::Vector<int>::iterator it = v.erase(v.begin() + 1);
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(*it, 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 3);
  EXPECT_EQ(v[2], 4);
}

TEST(EraseSingle, OnlyElement) {
  kb::Vector<int> v(1, 42);
  kb::Vector<int>::iterator it = v.erase(v.begin());
  EXPECT_EQ(v.size(), 0u);
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(it, v.end());
}

TEST(EraseSingle, SequentialEraseFromFront) {
  kb::Vector<int> v(5, 0);
  for (size_t i = 0; i < 5; ++i) {
    v[i] = static_cast<int>(i) + 1;
  }

  v.erase(v.begin());
  v.erase(v.begin());
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0], 3);
  EXPECT_EQ(v[1], 4);
  EXPECT_EQ(v[2], 5);
}

TEST(EraseSingle, SequentialEraseFromBack) {
  kb::Vector<int> v(5, 0);
  for (size_t i = 0; i < 5; ++i) {
    v[i] = static_cast<int>(i) + 1;
  }

  v.erase(v.end() - 1);
  v.erase(v.end() - 1);
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

// === Erase (range) ===

TEST(EraseRange, EntireVector) {
  kb::Vector<int> v(5, 42);
  kb::Vector<int>::iterator it = v.erase(v.begin(), v.end());
  EXPECT_EQ(v.size(), 0u);
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(it, v.end());
}

TEST(EraseRange, FromBeginning) {
  kb::Vector<int> v(5, 0);
  for (size_t i = 0; i < 5; ++i) {
    v[i] = static_cast<int>(i) + 1;
  }

  kb::Vector<int>::iterator it = v.erase(v.begin(), v.begin() + 2);
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(*it, 3);
  EXPECT_EQ(it, v.begin());
  EXPECT_EQ(v[0], 3);
  EXPECT_EQ(v[1], 4);
  EXPECT_EQ(v[2], 5);
}

TEST(EraseRange, FromEnd) {
  kb::Vector<int> v(5, 0);
  for (size_t i = 0; i < 5; ++i) {
    v[i] = static_cast<int>(i) + 1;
  }

  kb::Vector<int>::iterator it = v.erase(v.begin() + 3, v.end());
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(it, v.end());
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(EraseRange, FromMiddle) {
  kb::Vector<int> v(5, 0);
  for (size_t i = 0; i < 5; ++i) {
    v[i] = static_cast<int>(i) + 1;
  }

  kb::Vector<int>::iterator it = v.erase(v.begin() + 1, v.begin() + 4);
  ASSERT_EQ(v.size(), 2u);
  EXPECT_EQ(*it, 5);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 5);
}

TEST(EraseRange, EmptyRange) {
  kb::Vector<int> v(3, 10);
  kb::Vector<int>::iterator it = v.erase(v.begin() + 1, v.begin() + 1);
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(*it, 10);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 10);
  EXPECT_EQ(v[2], 10);
}

TEST(EraseRange, SingleElementRange) {
  kb::Vector<int> v(3, 0);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  kb::Vector<int>::iterator it = v.erase(v.begin() + 1, v.begin() + 2);
  ASSERT_EQ(v.size(), 2u);
  EXPECT_EQ(*it, 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 3);
}

// === Non-member swap ===

TEST(NonMemberSwap, Basic) {
  kb::Vector<int> a(3, 1);
  kb::Vector<int> b(5, 2);
  kb::swap(a, b);
  ASSERT_EQ(a.size(), 5u);
  ASSERT_EQ(b.size(), 3u);
  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], 2);
  }
  for (size_t i = 0; i < b.size(); ++i) {
    EXPECT_EQ(b[i], 1);
  }
}

TEST(NonMemberSwap, DifferentCapacities) {
  kb::Vector<int> a(2, 10);
  kb::Vector<int> b(8, 20);
  size_t cap_a = a.capacity();
  size_t cap_b = b.capacity();
  kb::swap(a, b);
  EXPECT_EQ(a.capacity(), cap_b);
  EXPECT_EQ(b.capacity(), cap_a);
  EXPECT_EQ(a.size(), 8u);
  EXPECT_EQ(b.size(), 2u);
}

// === Mixed scenarios with new methods ===

TEST(MixedNew, InsertThenErase) {
  kb::Vector<int> v;
  v.push_back(1);
  v.push_back(3);
  v.push_back(5);
  v.insert(v.begin() + 1, 2);
  v.insert(v.begin() + 3, 4);
  ASSERT_EQ(v.size(), 5u);
  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(v[i], static_cast<int>(i) + 1);
  }

  v.erase(v.begin() + 2);
  ASSERT_EQ(v.size(), 4u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 4);
  EXPECT_EQ(v[3], 5);
}

TEST(MixedNew, RangeConstructThenInsertAndErase) {
  int arr[] = {10, 20, 30};
  kb::Vector<int> v(arr, arr + 3);

  int insert_arr[] = {15, 25};
  v.insert(v.begin() + 1, insert_arr, insert_arr + 2);
  ASSERT_EQ(v.size(), 5u);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 15);
  EXPECT_EQ(v[2], 25);
  EXPECT_EQ(v[3], 20);
  EXPECT_EQ(v[4], 30);

  v.erase(v.begin() + 1, v.begin() + 3);
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v[2], 30);
}

TEST(MixedNew, IteratorRangeAssignThenReverseIterate) {
  int arr[] = {1, 2, 3, 4, 5};
  kb::Vector<int> v;
  v.assign(arr, arr + 5);

  int expected = 5;
  for (kb::Vector<int>::reverse_iterator rit = v.rbegin(); rit != v.rend(); ++rit) {
    EXPECT_EQ(*rit, expected);
    --expected;
  }
  EXPECT_EQ(expected, 0);
}

TEST(MixedNew, EraseAllThenInsert) {
  kb::Vector<int> v(5, 10);
  v.erase(v.begin(), v.end());
  EXPECT_TRUE(v.empty());

  v.insert(v.begin(), 42);
  ASSERT_EQ(v.size(), 1u);
  EXPECT_EQ(v[0], 42);
}

TEST(MixedNew, DoubleTypeWithNewMethods) {
  double arr[] = {1.1, 2.2, 3.3};
  kb::Vector<double> v(arr, arr + 3);
  v.insert(v.begin() + 1, 1.5);
  ASSERT_EQ(v.size(), 4u);
  EXPECT_DOUBLE_EQ(v[0], 1.1);
  EXPECT_DOUBLE_EQ(v[1], 1.5);
  EXPECT_DOUBLE_EQ(v[2], 2.2);
  EXPECT_DOUBLE_EQ(v[3], 3.3);

  v.erase(v.begin() + 2);
  ASSERT_EQ(v.size(), 3u);
  EXPECT_DOUBLE_EQ(v[0], 1.1);
  EXPECT_DOUBLE_EQ(v[1], 1.5);
  EXPECT_DOUBLE_EQ(v[2], 3.3);
}
