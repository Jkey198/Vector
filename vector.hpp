#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <cmath>
#include <exception>
#include <iterator>

namespace kb {
template<typename T>
class Vector {
public:
  /* types */
  typedef T                                     value_type;
  typedef size_t                                size_type;
  typedef value_type&                           reference;
  typedef const value_type&                     const_reference;

  class iterator {
  public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef T*                              pointer;
    typedef T&                              reference;

    iterator() : __ptr_(0) {}
    iterator(pointer p) : __ptr_(p) {}

    reference operator*() const { return *__ptr_; }
    pointer operator->() const { return __ptr_; }
    reference operator[](difference_type n) const { return __ptr_[n]; }

    iterator& operator++() { ++__ptr_; return *this; }
    iterator operator++(int) { iterator tmp(*this); ++__ptr_; return tmp; }
    iterator& operator--() { --__ptr_; return *this; }
    iterator operator--(int) { iterator tmp(*this); --__ptr_; return tmp; }

    iterator& operator+=(difference_type n) { __ptr_ += n; return *this; }
    iterator& operator-=(difference_type n) { __ptr_ -= n; return *this; }

    iterator operator+(difference_type n) const { return iterator(__ptr_ + n); }
    iterator operator-(difference_type n) const { return iterator(__ptr_ - n); }
    difference_type operator-(const iterator& other) const { return __ptr_ - other.__ptr_; }

    bool operator==(const iterator& other) const { return __ptr_ == other.__ptr_; }
    bool operator!=(const iterator& other) const { return __ptr_ != other.__ptr_; }
    bool operator<(const iterator& other) const { return __ptr_ < other.__ptr_; }
    bool operator>(const iterator& other) const { return __ptr_ > other.__ptr_; }
    bool operator<=(const iterator& other) const { return __ptr_ <= other.__ptr_; }
    bool operator>=(const iterator& other) const { return __ptr_ >= other.__ptr_; }

    pointer base() const { return __ptr_; }

  private:
    pointer __ptr_;

    friend iterator operator+(difference_type n, const iterator& it) {
      return iterator(it.__ptr_ + n);
    }
  };

  class const_iterator {
  public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef std::ptrdiff_t                  difference_type;
    typedef const T*                        pointer;
    typedef const T&                        reference;

    const_iterator() : __ptr_(0) {}
    const_iterator(pointer p) : __ptr_(p) {}
    const_iterator(const iterator& it) : __ptr_(it.base()) {}

    reference operator*() const { return *__ptr_; }
    pointer operator->() const { return __ptr_; }
    reference operator[](difference_type n) const { return __ptr_[n]; }

    const_iterator& operator++() { ++__ptr_; return *this; }
    const_iterator operator++(int) { const_iterator tmp(*this); ++__ptr_; return tmp; }
    const_iterator& operator--() { --__ptr_; return *this; }
    const_iterator operator--(int) { const_iterator tmp(*this); --__ptr_; return tmp; }

    const_iterator& operator+=(difference_type n) { __ptr_ += n; return *this; }
    const_iterator& operator-=(difference_type n) { __ptr_ -= n; return *this; }

    const_iterator operator+(difference_type n) const { return const_iterator(__ptr_ + n); }
    const_iterator operator-(difference_type n) const { return const_iterator(__ptr_ - n); }
    difference_type operator-(const const_iterator& other) const { return __ptr_ - other.__ptr_; }

    bool operator==(const const_iterator& other) const { return __ptr_ == other.__ptr_; }
    bool operator!=(const const_iterator& other) const { return __ptr_ != other.__ptr_; }
    bool operator<(const const_iterator& other) const { return __ptr_ < other.__ptr_; }
    bool operator>(const const_iterator& other) const { return __ptr_ > other.__ptr_; }
    bool operator<=(const const_iterator& other) const { return __ptr_ <= other.__ptr_; }
    bool operator>=(const const_iterator& other) const { return __ptr_ >= other.__ptr_; }

    pointer base() const { return __ptr_; }

  private:
    pointer __ptr_;

    friend const_iterator operator+(difference_type n, const const_iterator& it) {
      return const_iterator(it.__ptr_ + n);
    }
  };

  typedef std::reverse_iterator<iterator>       reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  /* constructors : default, copy, iterators */
  Vector();
  Vector(size_type __size, value_type __value = value_type());
  Vector(const Vector& __other);
  Vector(const_iterator __first, const_iterator __last);

  /* destructor */
  ~Vector();

  /* operators */
  Vector& operator=(const Vector& __other);
  void assign(size_type __size, const_reference __value);
  void assign(const_iterator __first, const_iterator __last);

  /* element access */
  reference       at(size_type __pos);
  const_reference at(size_type __pos) const;
  reference       operator[](size_type __pos);
  const_reference operator[](size_type __pos) const;
  reference       front();
  const_reference front() const;
  reference       back();
  const_reference back() const;
  T*              data();
  const T*        data() const;

  /* iterators */
  iterator                begin();
  const_iterator          begin() const;
  iterator                end();
  const_iterator          end() const;
  reverse_iterator        rbegin();
  const_reverse_iterator  rbegin() const;
  reverse_iterator        rend();
  const_reverse_iterator  rend() const;

  /* memory */
  bool      empty() const;
  size_type size() const;
  size_type max_size() const;
  void      reserve(size_type __size);
  size_type capacity() const;
  void      shrink_to_fit();

  /* methods for working with elements */
  void      clear();
  iterator  insert(iterator __pos, const_reference __value);
  void      insert(iterator __pos, const_iterator __first, const_iterator __last);
  iterator  erase(iterator __pos);
  iterator  erase(iterator __first, iterator __last);
  void      push_back(value_type value);
  void      pop_back();
  void      resize(size_type __size);
  void      swap(Vector& __other);

private:
  T*        __begin_;
  T*        __end_;
  T*        __data_;
  size_type __size_;
  size_type __capacity_;
};

template<typename T>
Vector<T>::Vector() : __begin_(0), __end_(0), __data_(0), __size_(0), __capacity_(0) {}

template<typename T>
Vector<T>::Vector(size_type __size, value_type __value) {
  __size_ = __size;
  __capacity_ = __size_;

  T* buffer = new value_type[__capacity_ * sizeof(value_type)];
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

  T* buffer = new value_type[__other.__capacity_ * sizeof(value_type)];
  __data_ = new (buffer) value_type();
  for (size_type i = 0; i < __size_; ++i) {
    new (&(*(__data_ + i))) value_type(*(__other.__data_ + i));
  }

  __begin_ = __data_;
  __end_ = __data_ + __size_;
}

template<typename T>
Vector<T>::Vector(const_iterator __first, const_iterator __last) {
  const T* first = __first.base();
  const T* last = __last.base();
  __size_ = last - first;
  __capacity_ = __size_;

  T* buffer = new value_type[__capacity_ * sizeof(value_type)];
  __data_ = new (buffer) value_type();
  for (size_type i = 0; i < __size_; ++i) {
    new (&(*(__data_ + i))) value_type(*(first + i));
  }

  __begin_ = __data_;
  __end_ = __data_ + __size_;
}

template<typename T>
Vector<T>::~Vector() {
  delete[] __data_;
  __data_ = 0;
  __begin_ = 0;
  __end_ = 0;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& __other) {
  if (this != &__other) {
    delete[] __data_;
    __data_ = 0;
    __begin_ = 0;
    __end_ = 0;

    __size_ = __other.__size_;
    __capacity_ = __other.__capacity_;

    T* buffer = new value_type[__capacity_ * sizeof(value_type)];
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
  __data_ = 0;
  __begin_ = 0;
  __end_ = 0;

  __size_ = __size;
  __capacity_ = __size;

  T* buffer = new value_type[__capacity_ * sizeof(value_type)];
  __data_ = new (buffer) value_type();
  for (size_type i = 0; i < __size_; ++i) {
    new (&(*(__data_ + i))) value_type(__value);
  }

  __begin_ = __data_;
  __end_ = __data_ + __size_;
}

template<typename T>
void Vector<T>::assign(const_iterator __first, const_iterator __last) {
  delete[] __data_;
  __data_ = 0;
  __begin_ = 0;
  __end_ = 0;

  const T* first = __first.base();
  const T* last = __last.base();
  __size_ = last - first;
  __capacity_ = __size_;

  T* buffer = new value_type[__capacity_ * sizeof(value_type)];
  __data_ = new (buffer) value_type();
  for (size_type i = 0; i < __size_; ++i) {
    new (&(*(__data_ + i))) value_type(*(first + i));
  }

  __begin_ = __data_;
  __end_ = __data_ + __size_;
}

template<typename T>
typename Vector<T>::reference Vector<T>::at(size_type __pos) {
  if (__pos >= __size_)
    throw std::runtime_error("Could not find element - invalid index");
  return *(__data_ + __pos);
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type __pos) const {
  if (__pos >= __size_)
    throw std::runtime_error("Could not find element - invalid index");
  return *(__data_ + __pos);
}

template<typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type __pos) {
  if (__pos >= __size_)
    throw std::runtime_error("Could not find element - invalid index");
  return *(__data_ + __pos);
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type __pos) const {
  if (__pos >= __size_)
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
T* Vector<T>::data() {
  return __data_;
}

template<typename T>
const T* Vector<T>::data() const {
  return __data_;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin() {
  return iterator(__begin_);
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const {
  return const_iterator(__begin_);
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end() {
  return iterator(__end_);
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::end() const {
  return const_iterator(__end_);
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin() {
  return reverse_iterator(end());
}

template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rbegin() const {
  return const_reverse_iterator(end());
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend() {
  return reverse_iterator(begin());
}

template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rend() const {
  return const_reverse_iterator(begin());
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

  T* old_data = __data_;
  T* buffer = new value_type[__new_capacity * sizeof(value_type)];
  __data_ = new (buffer) value_type();

  __begin_ = __end_ = 0;
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
    T* old_data = __data_;
    __capacity_ = __size_;

    T* buffer = new value_type[__capacity_ * sizeof(value_type)];
    __data_ = new (buffer) value_type();

    __begin_ = __end_ = 0;

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
  if (__data_ != 0) {
    delete[] __data_;
    __data_ = 0;
    __begin_ = 0;
    __end_ = 0;
  }
  __size_ = 0;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator __pos, const_reference __value) {
  size_type index = __pos.base() - __begin_;

  if (__size_ == __capacity_) {
    size_type new_capacity = (__capacity_ == 0) ? 1 : __capacity_ * 2;
    reserve(new_capacity);
  }

  T* pos = __begin_ + index;

  for (T* it = __end_; it != pos; --it) {
    *it = *(it - 1);
  }

  *pos = __value;
  ++__size_;
  __end_ = __data_ + __size_;

  return iterator(pos);
}

template<typename T>
void Vector<T>::insert(iterator __pos, const_iterator __first, const_iterator __last) {
  size_type index = __pos.base() - __begin_;
  const T* first = __first.base();
  const T* last = __last.base();
  size_type count = last - first;
  if (count == 0) return;

  while (__size_ + count > __capacity_) {
    size_type new_capacity = (__capacity_ == 0) ? 1 : __capacity_ * 2;
    reserve(new_capacity);
  }

  T* pos = __begin_ + index;

  for (T* it = __end_ + count - 1; it != pos + count - 1; --it) {
    *it = *(it - count);
  }

  for (size_type i = 0; i < count; ++i) {
    *(pos + i) = *(first + i);
  }

  __size_ += count;
  __end_ = __data_ + __size_;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator __pos) {
  T* pos = __pos.base();
  for (T* it = pos; it != __end_ - 1; ++it) {
    *it = *(it + 1);
  }

  --__size_;
  __end_ = __data_ + __size_;

  return iterator(pos);
}

template<typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator __first, iterator __last) {
  T* first = __first.base();
  T* last = __last.base();
  size_type count = last - first;
  if (count == 0) return __first;

  for (T* it = first; it != __end_ - count; ++it) {
    *it = *(it + count);
  }

  __size_ -= count;
  __end_ = __data_ + __size_;

  return iterator(first);
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

    for (size_type i = old_size; i < __size; ++i) {
      *(__data_ + i) = value_type();
    }
  }

  __size_ = __size;
  __end_ = __data_ + __size_;
}

template<typename T>
void Vector<T>::swap(Vector& __other) {
  if (__other.__begin_ == 0 && __other.__end_ == 0)
    throw std::runtime_error("Vector");

  T*        cnt_data     = __data_;
  T*        cnt_begin    = __begin_;
  T*        cnt_end      = __end_;
  size_type cnt_size     = __size_;
  size_type cnt_capacity = __capacity_;

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

template<typename T>
void swap(Vector<T>& __a, Vector<T>& __b) {
  __a.swap(__b);
}

} // namespace kb

#endif /* VECTOR_HPP */
