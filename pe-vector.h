#ifndef PE_VECTOR_H
#define PE_VECTOR_H
#include <cstddef>

namespace knk {
  template < class T >
  class Vector {
  public:
    ~Vector();
    Vector();

    bool isEmpty() const noexept;

  private:
    T* data_;
    size_t size_, capacity_;
  };
}
template < class T >
knk::Vector < T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{};

template < class T >
knk::Vector < T >::~Vector() {
  delete [] data_;
}
#endif