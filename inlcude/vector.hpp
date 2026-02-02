// #define VECTOR_HPP
// #ifndef VECTOR_HPP

#include <cstddef>
#include <cmath>
#include <exception>
// #include <__type_traits/conditional.h>
// #include <__type_traits/enable_if.h>
// #include <__type_traits/is_allocator.h>
// #include <__type_traits/is_constant_evaluated.h>
// #include <__type_traits/is_constructible.h>
// #include <__type_traits/is_nothrow_assignable.h>
// #include <__type_traits/is_nothrow_constructible.h>
// #include <__type_traits/is_pointer.h>
// #include <__type_traits/is_same.h>
// #include <__type_traits/is_trivially_relocatable.h>
// #include <__type_traits/type_identity.h>

template<typename T>
class Vector {
public:
  /* types */
  typedef T*                  iterator;
  typedef T                   value_type;
  typedef size_t              size_type;
  typedef value_type&         reference;
  typedef const value_type&   const_reference;

  /* constructors : default, copy, iterators */
  Vector();
  Vector(size_type size, value_type value = value_type());
  Vector(const Vector& other);
  
  /* destructor */
  ~Vector();

  /* operators */
  reference operator=(const Vector& other);
  void assign(size_type size, const_reference value);

  /* element access */
  reference       at(size_type pos);
  const_reference at(size_type pos) const;
  reference       operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference       front();
  const_reference front() const;
  reference       back();
  const_reference back() const;
  reference       data();
  const_reference data() const;

  /* iterators */
  iterator begin();
  iterator end();
  
  /* capacity */
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  /* methods for work with elements */
  void clear();
  void push_back(const_reference value);
  void pop_back();
  void resize(size_type size);
  void swap(iterator first_elem, iterator second_elem);

private:
  iterator  __begin_ = nullptr;
  iterator  __end_ = nullptr;
  T*        __data_;
  size_type __size_;
  size_type __capacity_;
};

template<typename T>
Vector<T>::Vector() : __data_(0), __size_(0), __capacity_(0) {}

template<typename T>
Vector<T>::Vector(size_type size, value_type value/* = value_type()*/)
  : __size_(size) , __capacity_(std::pow(2, std::ceil(std::sqrt(size)))), __data_(new T[size]) {
  for (int i = 0; i < __size_; ++i) {
    *(__data_ + i) = value;
  }
}

template<typename T>
Vector<T>::Vector(const Vector& other)
  : __data_(other.__data_), __size_(other.__size_), __capacity_(other.__capacity_) {
  for (int i = 0; i < __size_; ++i) {
    *(__data_ + i) = *(other.__data_ + i);
  }
}

template<typename T>
Vector<T>::~Vector() {
  delete[] __data_;
}

template<typename T>
typename Vector<T>::reference Vector<T>::operator=(const Vector& other) {
  if (this != &other) {
    delete[] __data_;
    
    __size_ = other.__size_;
    __capacity_ = other.__capacity_;
    __data_ = new T[__size_];
    for (int i = 0; i < __size_; ++i) {
      *(__data_ + i) = *(other.__data_ + i);
    }
  }

  return *this;
}

template<typename T>
void Vector<T>::assign(size_type size, const_reference value) {
  __size_ = size;
  delete[] __data_;
  __data_ = new T[__size_];
  for (int i = 0; i < __size_; ++i) {
    *(__data_ + i) = value;
  }
}

template<typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
  if (pos < 0 || pos >= __size_) throw std::runtime_error("Could not find element - invalid index");
  return *(__data_ + pos);
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type pos) const {
  if (pos < 0 || pos >= __size_) throw std::runtime_error("Could not find element - invalid index");
  return *(__data_ + pos);
}

template<typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
  if (pos < 0 || pos >= __size_) throw std::runtime_error("Could not find element - invalid index");
  return *(__data_ + pos);
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type pos) const {
  if (pos < 0 || pos >= __size_) throw std::runtime_error("Could not find element - invalid index");
  return *(__data_ + pos);
}

template<typename T>
typename Vector<T>::reference Vector<T>::front() {
  return *(__data_);
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
  return *(__data_);
}

template<typename T>
typename Vector<T>::reference Vector<T>::back() {
  return *(__data_ + __size_);
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
  return *(__data_ + __size_);
}

template<typename T>
typename Vector<T>::reference Vector<T>::data() {
  return *__data_;
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::data() const {
  return *__data_;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin() {
  return __data_;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end() {
  return __data_ + __size_;
}

template<typename T>
bool Vector<T>::empty() const {
  return __size_ == 0;
}

template<typename T>
typename Vector<T>::size_type Vector<T>::size() const {
  return __size_;
}

template<typename T>
typename Vector<T>::size_type Vector<T>::max_size() const {
  return __capacity_; // ??? or __size_ ???
}

template<typename T>
void Vector<T>::reserve(size_type size) {
  __size_ = size;
  delete[] __data_;
  __data_ = new T[__size_];
  for (int i = 0; i < __size_; ++i) *(__data_ + i) = 0;
}

template<typename T>
typename Vector<T>::size_type Vector<T>::capacity() const {
  return __capacity_; // ???
}

template<typename T>
void Vector<T>::shrink_to_fit() {
  if (__size_ < __capacity_) {
    __capacity_ = __size_;
  }
  //TODO: make capacity lower, like size (do we have field 'capacity' ??)
}

template<typename T>
void Vector<T>::clear() {
  // __size_ = 0;
  // count = 0;
  delete[] __data_;
}

template<typename T>
void Vector<T>::push_back(const_reference value) {
  if (__size_ == __capacity_) {
    __capacity_ *= 2;
    __size_ += 1;
  }
  *(__data_ + __size_) = value;
}

template<typename T>
void Vector<T>::pop_back() {
  delete (__data_ + __size_);
  __size_ -= 1;
}

template<typename T>
void Vector<T>::resize(size_type size) {
  if (size == __size_) {
    return;
  } else {
    T* old_data = __data_;
    __data_ = new T[size];
    for (int i = 0; i < __size_; ++i) {
      *(__data_ + i) = *(old_data + i);
    }
    delete[] old_data;
  }
}

template<typename T>
void Vector<T>::swap(iterator first_elem, iterator second_elem) {
  if (first_elem >= __begin_ && first_elem < __end_ &&
    second_elem >= __begin_ && second_elem < __end_) {
    value_type tmp = *first_elem;
    *first_elem = *second_elem;
    *second_elem = tmp;
  } else {
    throw std::runtime_error("Failed to find element");
  }
}

// #endif /* VECTOR_HPP */
