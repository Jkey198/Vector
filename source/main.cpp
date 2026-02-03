#include <iostream>
#include "../inlcude/vector.hpp"
#include <vector>

int main() {
  kb::Vector<int> a;
  a.reserve(6);
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
  a.resize(5);
  for (size_t i = 0; i < a.size(); ++i) {
    a.push_back(5);
  }
  
  return 0;
}
