#include "../inlcude/vector.hpp"
#include <exception>

template<typename T>
Vector<T>::Vector() : __data_(0), __size_(0), capacity_(0) {}

template<typename T>
Vector<T>::Vector(size_type size, value_type value = value_type())
  : __size_(size) , capacity_(std::pow(2, std::ceil(std::sqrt(size)))), __data_(new T[size]) {
  for (int i = 0; i < __size_; ++i) {
    *(__data_ + i) = value;
  }
}

template<typename T>
Vector<T>::Vector(const Vector& other)
  : __data_(other.__data_), __size_(other.__size_), capacity_(other.capacity_) {
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
    __count_ = other.__count_;
    __data_ = new T[__count_];
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
  if (pos < 0 || pos >= __size_) return nullptr;
  return *(__data_ + pos);
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type pos) const {
  if (pos < 0 || pos >= __size_) return nullptr;
  return *(__data_ + pos);
}

template<typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
  if (pos < 0 || pos >= __size_) return nullptr;
  return *(__data_ + pos);
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type pos) const {
  if (pos < 0 || pos >= __size_) return nullptr;
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
  return __count_; // ???
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
  return __size_; // ???
}

template<typename T>
void Vector<T>::shrink_to_fit() {
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
  pointer __end =
}
