#include <iostream>
#include "vector.hpp"
#include <vector>

template<typename T>
void printStdVectorCapacity(std::vector<T>& a) {
  std::cout << "std::vector capacity: " << a.capacity() << std::endl;
}

template<typename T>
void printKbVectorCapacity(kb::Vector<T>& a) {
  std::cout << "kb::Vector capacity: " << a.capacity() << std::endl;
}

void sep() {
  std::cout << std::endl;
}

int main() {
  // working with capacity
  
  /*std::cout << std::endl << std::endl << std::endl;

  std::vector<int> vec(5);            //An array A of capacity 5

  //Print
  std::cout << "---------- BEFORE ---------------" << std::endl;
  std::cout << "capacity = " << vec.capacity() << std::endl;
  std::cout << "size = " << vec.size() << std::endl;
  

  //Add 2 additional elemetns to the end of A
  vec.push_back(10);
  vec.push_back(20);

  //Print
  std::cout << "---------- AFTER ---------------" << std::endl;
  std::cout << "capacity = " << vec.capacity() << std::endl;
  std::cout << "size = " << vec.size() << std::endl;
  
  sep();
  sep();
  
  std::vector<int> Vec(5);            //An array A of capacity 5

  //Print
  std::cout << "---------- BEFORE ---------------" << std::endl;
  std::cout << "capacity = " << Vec.capacity() << std::endl;
  std::cout << "size = " << Vec.size() << std::endl;
  

  //Add 2 additional elemetns to the end of A
  Vec.push_back(10);
  Vec.push_back(20);

  //Print
  std::cout << "---------- AFTER ---------------" << std::endl;
  std::cout << "capacity = " << Vec.capacity() << std::endl;
  std::cout << "size = " << Vec.size() << std::endl;*/
  
  /*std::vector<int> vec1;
  kb::Vector<int> Vec1;

  printStdVectorCapacity(vec1);
  vec1.assign(10, 1);
  printStdVectorCapacity(vec1);
  vec1.resize(6);
  printStdVectorCapacity(vec1);
  vec1.shrink_to_fit();
  printStdVectorCapacity(vec1);

  sep();

  printKbVectorCapacity(Vec1);
  Vec1.assign(10, 1);
  printKbVectorCapacity(Vec1);
  Vec1.resize(6);
  printKbVectorCapacity(Vec1);
  Vec1.shrink_to_fit();
  printKbVectorCapacity(Vec1);*/
  
  kb::Vector<int> a(6, 1);
  // a.reserve(6);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;
  a.resize(5);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;
  a.assign(4, 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;
  a.pop_back();
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "====================================" << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;

  std::cout << a.size() << std::endl;
  for (size_t i = 0; i < a.size(); ++i) {
    int x;
    std::cin >> x;
    a[i] = x;
  }
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "After swap() method:" << std::endl;
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a.at(i) << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "front(): " << a.front() << "\n";
  std::cout << "back(): " << a.back() << "\n";
  std::cout << "*begin(): " << *a.begin() << "\n";
  std::cout << "*end(): " << *a.end() << "\n";
  std::cout << "data(): " << a.data() << "   " << *a.data();
  std::cout << std::endl;

  std::cout << "====================================" << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;
  
  if (!a.empty()) {
    std::cout << "yapi!" << std::endl;
  } else {
    std::cout << "not yapi..." << std::endl;
  }
  
  std::cout << "After clear() method:" << std::endl;
  a.clear();
  if (!a.empty()) {
    std::cout << "yapi!" << std::endl;
  } else {
    std::cout << "not yapi..." << std::endl;
  }
  
  std::cout << "Check push_back() method (pop_back() already checked):" << std::endl;
  std::cout << a.capacity() << std::endl;
  a.resize(5);
  for (size_t i = 0; i < a.size(); ++i) {
    a[i] = i;
  }
  size_t boba = a.size();
  for (size_t i = 0; i < boba; ++i) {
    a.push_back(5);
  }
  
  std::cout << a.capacity() << std::endl;
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;
  
  std::cout << "====================================" << std::endl;
  std::cout << "====================================" << std::endl;
  std::cout << std::endl;
  
  // kb::Vector<int> a(5, 1);
  // kb::Vector<int> b(4, 2);
  
  // std::cout << "Before swap() method:" << std::endl;
  // for (size_t i = 0; i < a.size(); ++i) {
  //   std::cout << a[i] << " ";
  // }
  // std::cout << std::endl;
  // for (size_t i = 0; i < b.size(); ++i) {
  //   std::cout << b[i] << " ";
  // }
  // std::cout << std::endl << std::endl;

  // std::cout << "After swap() method:" << std::endl;
  // a.swap(b);
  // for (size_t i = 0; i < a.size(); ++i) {
  //   std::cout << a[i] << " ";
  // }
  // std::cout << std::endl;
  // for (size_t i = 0; i < b.size(); ++i) {
  //   std::cout << b[i] << " ";
  // }
  // std::cout << std::endl;
  
  return 0;
}
