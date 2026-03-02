# Vector Container Implementation

Custom implementation of a dynamic array container similar to `std::vector` in C++.

## Features

- Dynamic resizing with automatic capacity management
- Standard container operations (push_back, pop_back, resize, reserve, etc.)
- Element access via `[]`, `at()`, `front()`, `back()`
- Iterator support (`begin()`, `end()`)
- Exception safety for out-of-bounds access
- Namespace: `kb::Vector<T>`

## Project Structure

```
vector/
├── inlcude/
│   └── vector.hpp          # Vector template class implementation
├── source/
│   └── main.cpp            # Example usage and tests
├── Makefile                # Build configuration
└── README.md               # This file
```

## Building

### Prerequisites
- C++17 compatible compiler (g++, clang++)
- Make

### Compilation

```bash
make          # Build the project
make clean    # Remove build artifacts
```

```bash
mkdir -p build/ && cd build/
cmake ..
cmake --build .
```

```bash
./../test       # main test
./tests/tests   # google tests
```

## Usage

```cpp
#include "inlcude/vector.hpp"
#include <iostream>

int main() {
    kb::Vector<int> vec;
    
    // Add elements
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    
    // Access elements
    std::cout << "Size: " << vec.size() << std::endl;
    std::cout << "First element: " << vec[0] << std::endl;
    std::cout << "Last element: " << vec.back() << std::endl;
    
    // Iterate
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    
    return 0;
}
```

## API Reference

### Constructors
- `Vector()` - Default constructor
- `Vector(size_type size, value_type value = value_type())` - Construct with size and initial value
- `Vector(const Vector& other)` - Copy constructor

### Element Access
- `at(size_type pos)` - Access element with bounds checking
- `operator[](size_type pos)` - Access element without bounds checking
- `front()` - Access first element
- `back()` - Access last element
- `data()` - Direct access to underlying array

### Iterators
- `begin()` - Returns iterator to beginning
- `end()` - Returns iterator to end

### Capacity
- `empty()` - Check if container is empty
- `size()` - Number of elements
- `capacity()` - Capacity of allocated storage
- `max_size()` - Maximum possible number of elements
- `reserve(size_type)` - Reserve storage
- `shrink_to_fit()` - Reduce capacity to fit size

### Modifiers
- `clear()` - Clear all elements
- `push_back(const_reference)` - Add element to end
- `pop_back()` - Remove last element
- `resize(size_type)` - Change number of elements
- `assign(size_type, const_reference)` - Assign new content
- `swap(Vector&)` - Swap contents with another vector

## Implementation Details

- **Capacity Growth Strategy**: Powers of 2 (doubles when full)
- **Memory Management**: Raw pointers with manual allocation
- **Exception Safety**: Basic guarantee for most operations
- **Iterator Type**: Raw pointer (`T*`)

## Author

Developed as part of HSE Programming Languages course labs.

## License

Educational project - free to use and modify.
