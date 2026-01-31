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
  typedef typename size_t     size_type;
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
  void resize(size_type size, value_type = value_type());
  void swap(iterator first_elem, iterator second_elem);
  void swap(Vector& other);

private:
  T*      __data_;
  size_t  __size_;
  size_t  __capacity_;
  pointer __begin_  = nullptr;
  pointer __end_    = nullptr;
};



// #endif /* VECTOR_HPP */
