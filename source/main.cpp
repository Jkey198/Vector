#include <iostream>
#include "../inlcude/vector.hpp"
#include <vector>

int main() {
  Vector<int> a(5, 1);
  for (int i = 0; i < a.size(); ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < a.size(); ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
  
  return 0;
}
