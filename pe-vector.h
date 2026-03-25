#ifndef PE_VECTOR_H
#define PE_VECTOR_H
#include <cstddef>

namespace knk
{
  template <class T>
  struct Vector {
    T* data;
    size_t size, capacity;
  };
}

#endif