#include <iostream>
using T = int;
size_t size = 10;
T value = 20;

int foo() {
  T* d = new T[size];
  for (size_t i = 0; i < size; ++i) {
    d[i] = value;
  }
  // ???
  delete [] d;
}
int bar() {
  T* d = static_cast< T* >(::operator new(sizeof(T) * size));
  for (size_t i = 0; i < size; ++i) {
    new (d + i) T(value);
  }
  // ???
  for (size_t i = 0; i < size; ++i) {
    (d + i)->~T();
    // d[i].~T();
  }
  ::operator delete(d);
}