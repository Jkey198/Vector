#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <cmath>
#include <exception>

namespace kb {
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
  Vector(); // * DONE
  Vector(size_type __size, value_type __value = value_type()); // * DONE
  Vector(const Vector& __other); // * DONE
  
  /* destructor */
  ~Vector(); // * DONE

  /* operators */
  Vector& operator=(const Vector& __other); // * DONE
  void assign(size_type __size, const_reference __value); // * DONE

  /* element access */
  reference       at(size_type __pos); // * DONE
  const_reference at(size_type __pos) const; // * DONE
  reference       operator[](size_type __pos); // * DONE
  const_reference operator[](size_type __pos) const; // * DONE
  reference       front(); // * DONE
  const_reference front() const; // * DONE
  reference       back(); // * DONE
  const_reference back() const; // * DONE
  iterator        data(); // * DONE
  iterator        data() const; // * DONE

  /* iterators */
  iterator begin(); // * DONE
  iterator end(); // * DONE
  
  /* memory */
  bool      empty() const; // * DONE
  size_type size() const; // * DONE
  size_type max_size() const; // * DONE
  void      reserve(size_type __size); // * DONE
  size_type capacity() const; // * DONE
  void      shrink_to_fit(); // * DONE

  /* methods for working with elements */
  void clear(); // * DONE
  void push_back(value_type value); // * DONE
  void pop_back(); // * DONE
  void resize(size_type __size); // * DONE
  void swap(Vector& __other); // * DONE

private:
  iterator  __begin_;
  iterator  __end_;
  iterator  __data_;
  size_type __size_;
  size_type __capacity_;
};

template<typename T>
Vector<T>::Vector() : __begin_(nullptr), __end_(nullptr), __data_(nullptr), __size_(0), __capacity_(0) {}

template<typename T>
Vector<T>::Vector(size_type __size, value_type __value) {
  __size_ = __size;
  __capacity_ = __size_;

  iterator buffer = new value_type[__capacity_ * sizeof(value_type)];
  __data_ = new (buffer) value_type();
  for (size_type i = 0; i < __size_; ++i) {
    new (&(*(__data_ + i))) value_type(__value);
  }

  __begin_ = __data_;
  __end_ = __data_ + __size_;
}

template<typename T>
Vector<T>::Vector(const Vector& __other) {
  __size_ = __other.__size_;
  __capacity_ = __other.__capacity_;
  
  iterator buffer  = new value_type[__other.__capacity_ * sizeof(value_type)];
  __data_ = new (buffer) value_type();
  for (size_type i = 0; i < __size_; ++i) {
    new (&(*(__data_ + i))) value_type(*(__other.__data_ + i));
  }

  __begin_ = __data_;
  __end_ = __data_ + __size_;
}

template<typename T>
Vector<T>::~Vector() {
  /*for (size_type i = __size_ - 1; i >= 0; --i) {
    __data_[i]->~T();
  }::operator delete(__data_);*/
  delete[] __data_;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& __other) {
  if (this != &__other) {
    delete[] __data_;
    __begin_ = __end_ = nullptr;
    
    __size_ = __other.__size_;
    __capacity_ = __other.__capacity_;
    
    iterator buffer = new value_type[__capacity_ * sizeof(value_type)];
    __data_ = new (buffer) value_type();
    for (size_type i = 0; i < __size_; ++i) {
      new (&(*(__data_ + i))) value_type(*(__other.__data_ + i));
    }
    
    __begin_ = __data_;
    __end_ = __data_ + __size_;
  }

  return *this;
}

template<typename T>
void Vector<T>::assign(size_type __size, const_reference __value) {
  delete[] __data_;
  
  __size_ = __size;
  __capacity_ = __size;
  
  iterator buffer = new value_type[__capacity_ * sizeof(value_type)];
  __data_ = new (buffer) value_type();
  for (size_type i = 0; i < __size_; ++i) {
    new (&(*(__data_ + i))) value_type(__value);
  }
  
  __begin_ = __data_;
  __end_ = __data_ + __size_;
}

template<typename T>
typename Vector<T>::reference Vector<T>::at(size_type __pos) {
  if (__pos < 0 || __pos >= __size_)
    throw std::runtime_error("Could not find element - invalid index");
  return *(__data_ + __pos);
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type __pos) const {
  if (__pos < 0 || __pos >= __size_)
    throw std::runtime_error("Could not find element - invalid index");
  return *(__data_ + __pos);
}

template<typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type __pos) {
  if (__pos < 0 || __pos >= __size_)
    throw std::runtime_error("Could not find element - invalid index");
  return *(__data_ + __pos);
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type __pos) const {
  if (__pos < 0 || __pos >= __size_)
    throw std::runtime_error("Could not find element - invalid index");
  return *(__data_ + __pos);
}

template<typename T>
typename Vector<T>::reference Vector<T>::front() {
  return *(__begin_);
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
  return *(__begin_);
}

template<typename T>
typename Vector<T>::reference Vector<T>::back() {
  return *(__end_ - 1);
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
  return *(__end_ - 1);
}

template<typename T>
typename Vector<T>::iterator Vector<T>::data() {
  return __data_;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::data() const {
  return __data_;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin() {
  return __begin_;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end() {
  return __end_;
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
  return static_cast<size_type>(-1) / sizeof(T);
}

template<typename T>
void Vector<T>::reserve(size_type __new_capacity) {
  if (__new_capacity > max_size())
    throw std::length_error("Vector");
  if (__new_capacity <= __capacity_) return;

  iterator old_data = __data_;
  iterator buffer = new value_type[__capacity_ * sizeof(value_type)];
  __data_ = new (buffer) value_type();
  
  __begin_ = __end_ = nullptr;
  __capacity_ = __new_capacity;
  
  for (size_type i = 0; i < __size_; ++i) {
    new (&(*(__data_ + i))) value_type(*(old_data + i));
  }

  delete[] old_data;
  __begin_ = __data_;
  __end_ = __data_ + __size_;
}

template<typename T>
typename Vector<T>::size_type Vector<T>::capacity() const {
  return __capacity_;
}

template<typename T>
void Vector<T>::shrink_to_fit() {
  if (__size_ < __capacity_) {
    iterator old_data = __data_;
    __capacity_ = __size_;
    
    iterator buffer = new value_type[__capacity_ * sizeof(value_type)];
    __data_ = new (buffer) value_type();
    
    __begin_ = __end_ = nullptr;
    
    for (size_type i = 0; i < __size_; ++i) {
      new (&(*(__data_ + i))) value_type(*(old_data + i));
    }

    delete[] old_data;
    __begin_ = __data_;
    __end_ = __data_ + __size_;
  }
}

template<typename T>
void Vector<T>::clear() {
  if (__data_ != nullptr) {
    delete[] __data_;
    __data_ = nullptr;
    __begin_ = nullptr;
    __end_ = nullptr;
  }
  __size_ = 0;
}

template<typename T>
void Vector<T>::push_back(value_type __value) {
  if (__size_ + 1 > max_size())
    throw std::length_error("Vector");
  
  if (__size_ == __capacity_) {
    size_type new_capacity = (__capacity_ == 0) ? 1 : __capacity_ * 2;
    reserve(new_capacity);
  }
  
  *(__data_ + (__size_++)) = __value;
  __end_ = __data_ + __size_;
}

template<typename T>
void Vector<T>::pop_back() {
  __end_ -= 1;
  __size_ -= 1;
}

template<typename T>
void Vector<T>::resize(size_type __size) {
  if (__size == __size_) {
    return;
  }

  if (__size > __capacity_) {
    if (__size > max_size())
      throw std::length_error("Vector");
    
    size_type old_size = __size_;
    size_type new_capacity = std::pow(2, std::ceil(std::log2(__size)));
    reserve(new_capacity);
    
    // Initialize new elements with default value
    for (size_type i = old_size; i < __size; ++i) {
      *(__data_ + i) = value_type();
    }
  }
  
  __size_ = __size;
  __end_ = __data_ + __size_;
}

template<typename T>
void Vector<T>::swap(Vector& __other) {
  // ! that looks like trash, but it works...

  if (__other.__begin_ == nullptr && __other.__end_ == nullptr)
    throw std::runtime_error("Vector");
  
  iterator  cnt_data      = __data_;
  iterator  cnt_begin     = __begin_;
  iterator  cnt_end       = __end_;
  size_type cnt_size      = __size_;
  size_type cnt_capacity  = __capacity_;

  __data_     = __other.__data_;
  __begin_    = __other.__begin_;
  __end_      = __other.__end_;
  __size_     = __other.__size_;
  __capacity_ = __other.__capacity_;
  
  __other.__data_     = cnt_data;
  __other.__begin_    = cnt_begin;
  __other.__end_      = cnt_end;
  __other.__size_     = cnt_size;
  __other.__capacity_ = cnt_capacity;
}

} // namespace kb

#endif /* VECTOR_HPP */
