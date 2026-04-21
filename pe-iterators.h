#ifndef ITERATORS_H
#define ITERATORS_H

#include <cstddef>

namespace knk {
  template< class T >
  struct VIter {
    T* p;
    VIter(T* ptr = nullptr);
    T& operator*() const;
    VIter< T >& operator++();
    VIter< T > operator++(int);
    VIter< T >& operator--();
    VIter< T > operator--(int);
    VIter< T >& operator+=(size_t n);
    VIter< T >& operator-=(size_t n);
    VIter< T > operator+(size_t n) const;
    VIter< T > operator-(size_t n) const;
    long long operator-(const VIter< T >& other) const;
    bool operator==(const VIter< T >& other) const;
    bool operator!=(const VIter< T >& other) const;
    bool operator<(const VIter< T >& other) const;
  };

  template< class T >
  struct VCIter {
    const T* p;
    VCIter(const T* ptr = nullptr);
    VCIter(const VIter< T >& other);
    const T& operator*() const;
    VCIter< T >& operator++();
    VCIter< T > operator++(int);
    VCIter< T >& operator--();
    VCIter< T > operator--(int);
    VCIter< T >& operator+=(size_t n);
    VCIter< T >& operator-=(size_t n);
    VCIter< T > operator+(size_t n) const;
    VCIter< T > operator-(size_t n) const;
    long long operator-(const VCIter< T >& other) const;
    bool operator==(const VCIter< T >& other) const;
    bool operator!=(const VCIter< T >& other) const;
    bool operator<(const VCIter< T >& other) const;
  };

  template< class T >
  knk::VIter< T >::VIter(T* ptr):
    p(ptr)
  {}

  template< class T >
  T& knk::VIter< T >::operator*() const {
    return *p;
  }

  template< class T >
  knk::VIter< T >& knk::VIter< T >::operator++() {
    ++p;
    return *this;
  }

  template< class T >
  knk::VIter< T > knk::VIter< T >::operator++(int) {
    VIter tmp = *this;
    ++p;
    return tmp;
  }

  template< class T >
  knk::VIter< T >& knk::VIter< T >::operator--() {
    --p;
    return *this;
  }

  template< class T >
  knk::VIter< T > knk::VIter< T >::operator--(int) {
    VIter tmp = *this;
    --p;
    return tmp;
  }

  template< class T >
  knk::VIter< T >& knk::VIter< T >::operator+=(size_t n) {
    p += n;
    return *this;
  }

  template< class T >
  knk::VIter< T >& knk::VIter< T >::operator-=(size_t n) {
    p -= n;
    return *this;
  }

  template< class T >
  knk::VIter< T > knk::VIter< T >::operator+(size_t n) const {
    return Viter(p + n);
  }

  template< class T >
  knk::VIter< T > knk::VIter< T >::operator-(size_t n) const {
    return Viter(p - n);
  }

  template< class T >
  long long knk::VIter< T >::operator-(const VIter< T >& other) const {
    return p - other.p;
  }

  template< class T >
  bool knk::VIter< T >::operator==(const VIter< T >& other) const {
    return p == other.p;
  }

  template< class T >
  bool knk::VIter< T >::operator!=(const VIter< T >& other) const {
    return p != other.p;
  }

  template< class T >
  bool knk::VIter< T >::operator<(const VIter< T >& other) const {
    return p < other.p;
  }

  template< class T >
  knk::VCIter< T >::VCIter(const T* ptr):
    p(ptr)
  {}

  template< class T >
  knk::VCIter< T >::VCIter(const VIter< T >& other):
    p(other.p)
  {}

  template< class T >
  const T& knk::VCIter< T >::operator*() const {
    return *p;
  }

  template< class T >
  knk::VCIter< T >& knk::VCIter< T >::operator++() {
    ++p;
    return *this;
  }

  template< class T >
  knk::VCIter< T > knk::VCIter< T >::operator++(int) {
    VCIter tmp = *this;
    ++p;
    return tmp;
  }

  template< class T >
  knk::VCIter< T >& knk::VCIter< T >::operator--() {
    --p;
    return *this;
  }

  template< class T >
  knk::VCIter< T > knk::VCIter< T >::operator--(int) {
    VCIter tmp = *this;
    --p;
    return tmp;
  }

  template< class T >
  knk::VCIter< T >& knk::VCIter< T >::operator+=(size_t n) {
    p += n;
    return *this;
  }

  template< class T >
  knk::VCIter< T >& knk::VCIter< T >::operator-=(size_t n) {
    p -= n;
    return *this;
  }

  template< class T >
  knk::VCIter< T > knk::VCIter< T >::operator+(size_t n) const {
    return Vciter(p + n);
  }

  template< class T >
  knk::VCIter< T > knk::VCIter< T >::operator-(size_t n) const {
    return Vciter(p - n);
  }

  template< class T >
  long long knk::VCIter< T >::operator-(const VCIter< T >& other) const {
    return p - other.p;
  }

  template< class T >
  bool knk::VCIter< T >::operator==(const VCIter< T >& other) const {
    return p == other.p;
  }

  template< class T >
  bool knk::VCIter< T >::operator!=(const VCIter< T >& other) const {
    return p != other.p;
  }

  template< class T >
  bool knk::VCIter< T >::operator<(const VCIter< T >& other) const {
    return p < other.p;
  };
}
#endif