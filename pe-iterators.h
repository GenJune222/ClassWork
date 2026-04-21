#ifndef ITERATORS_H
#define ITERATORS_H

#include <cstddef>

namespace knk {
  template< class T >
  struct Viter {
    T* p;
    Viter(T* ptr = nullptr);
    T& operator*() const;
    Viter< T >& operator++();
    Viter< T > operator++(int);
    Viter< T >& operator--();
    Viter< T > operator--(int);
    Viter< T >& operator+=(size_t n);
    Viter< T >& operator-=(size_t n);
    Viter< T > operator+(size_t n) const;
    Viter< T > operator-(size_t n) const;
    long long operator-(const Viter< T >& other) const;
    bool operator==(const Viter< T >& other) const;
    bool operator!=(const Viter< T >& other) const;
    bool operator<(const Viter< T >& other) const;
  };

  template< class T >
  struct Vciter {
    const T* p;
    Vciter(const T* ptr = nullptr);
    Vciter(const Viter< T >& other);
    const T& operator*() const;
    Vciter< T >& operator++();
    Vciter< T > operator++(int);
    Vciter< T >& operator--();
    Vciter< T > operator--(int);
    Vciter< T >& operator+=(size_t n);
    Vciter< T >& operator-=(size_t n);
    Vciter< T > operator+(size_t n) const;
    Vciter< T > operator-(size_t n) const;
    long long operator-(const Vciter< T >& other) const;
    bool operator==(const Vciter< T >& other) const;
    bool operator!=(const Vciter< T >& other) const;
    bool operator<(const Vciter< T >& other) const;
  };

  template< class T >
  knk::Viter< T >::Viter(T* ptr):
    p(ptr)
  {}

  template< class T >
  T& knk::Viter< T >::operator*() const {
    return *p;
  }

  template< class T >
  knk::Viter< T >& knk::Viter< T >::operator++() {
    ++p;
    return *this;
  }

  template< class T >
  knk::Viter< T > knk::Viter< T >::operator++(int) {
    Viter tmp = *this;
    ++p;
    return tmp;
  }

  template< class T >
  knk::Viter< T >& knk::Viter< T >::operator--() {
    --p;
    return *this;
  }

  template< class T >
  knk::Viter< T > knk::Viter< T >::operator--(int) {
    Viter tmp = *this;
    --p;
    return tmp;
  }

  template< class T >
  knk::Viter< T >& knk::Viter< T >::operator+=(size_t n) {
    p += n;
    return *this;
  }

  template< class T >
  knk::Viter< T >& knk::Viter< T >::operator-=(size_t n) {
    p -= n;
    return *this;
  }

  template< class T >
  knk::Viter< T > knk::Viter< T >::operator+(size_t n) const {
    return Viter(p + n);
  }

  template< class T >
  knk::Viter< T > knk::Viter< T >::operator-(size_t n) const {
    return Viter(p - n);
  }

  template< class T >
  long long knk::Viter< T >::operator-(const Viter< T >& other) const {
    return p - other.p;
  }

  template< class T >
  bool knk::Viter< T >::operator==(const Viter< T >& other) const {
    return p == other.p;
  }

  template< class T >
  bool knk::Viter< T >::operator!=(const Viter< T >& other) const {
    return p != other.p;
  }

  template< class T >
  bool knk::Viter< T >::operator<(const Viter< T >& other) const {
    return p < other.p;
  }

  template< class T >
  knk::Vciter< T >::Vciter(const T* ptr):
    p(ptr)
  {}

  template< class T >
  knk::Vciter< T >::Vciter(const Viter< T >& other):
    p(other.p)
  {}

  template< class T >
  const T& knk::Vciter< T >::operator*() const {
    return *p;
  }

  template< class T >
  knk::Vciter< T >& knk::Vciter< T >::operator++() {
    ++p;
    return *this;
  }

  template< class T >
  knk::Vciter< T > knk::Vciter< T >::operator++(int) {
    Vciter tmp = *this;
    ++p;
    return tmp;
  }

  template< class T >
  knk::Vciter< T >& knk::Vciter< T >::operator--() {
    --p;
    return *this;
  }

  template< class T >
  knk::Vciter< T > knk::Vciter< T >::operator--(int) {
    Vciter tmp = *this;
    --p;
    return tmp;
  }

  template< class T >
  knk::Vciter< T >& knk::Vciter< T >::operator+=(size_t n) {
    p += n;
    return *this;
  }

  template< class T >
  knk::Vciter< T >& knk::Vciter< T >::operator-=(size_t n) {
    p -= n;
    return *this;
  }

  template< class T >
  knk::Vciter< T > knk::Vciter< T >::operator+(size_t n) const {
    return Vciter(p + n);
  }

  template< class T >
  knk::Vciter< T > knk::Vciter< T >::operator-(size_t n) const {
    return Vciter(p - n);
  }

  template< class T >
  long long knk::Vciter< T >::operator-(const Vciter< T >& other) const {
    return p - other.p;
  }

  template< class T >
  bool knk::Vciter< T >::operator==(const Vciter< T >& other) const {
    return p == other.p;
  }

  template< class T >
  bool knk::Vciter< T >::operator!=(const Vciter< T >& other) const {
    return p != other.p;
  }

  template< class T >
  bool knk::Vciter< T >::operator<(const Vciter< T >& other) const {
    return p < other.p;
  };
}
#endif