#ifndef PE_VECTOR_H
#define PE_VECTOR_H
#include <cstddef>
#include <stdexcept>

namespace knk {
  template < class T >
  class Vector {
  public:
    ~Vector();
    Vector();
    Vector(size_t size, const T & value);
    Vector(const Vector<T> & rhs);
    Vector<T> & operator=(const Vector<T> & rhs) = delete;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    void pushBack(const T&);
    void popBack() noexcept;
    size_t getCapacity() const noexcept;

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

  private:
    T* data_;
    size_t size_, capacity_;
    explicit Vector(size_t size);
  };
}

template< class T>
T& knk::Vector< T >::at(size_t id) {
  if (id < getSize()) {
    return data_[id];
  }
  throw std::logic_error("id > size");
}
template< class T >
knk::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i) {
    data_[i] = rhs.data_[i];
  }
}


template<class T>
knk::Vector<T>::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}

template < class T >
knk::Vector < T >::Vector(size_t size, const T& value):
  data_(size ? new T[size] : nullptr),
   size_(size),
   capacity_(size) {
  for (size_t i = 0; i < size; ++i) {
    data_[i] = value;
  }
};

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

template < class T >
bool knk::Vector < T >::isEmpty() const noexcept{
  return !size_;
}

template < class T >
size_t knk::Vector < T >::getSize() const noexcept {
  return size_;
}

template < class T >
size_t knk::Vector < T >::getCapacity() const noexcept {
  return capacity_;
}

template < class T >
void knk::Vector < T >::pushBack(const T& value) {
  if (size_ >= capacity_) {
    size_t newCapacity = capacity_ == 0 ? 1 : capacity_ * 2;
    T* newData = new T[newCapacity];
    try {
      for (size_t i = 0; i < size_; ++i) {
        newData[i] = data_[i];
      }
    } catch (...) {
      delete [] newData;
      throw;
    }
    delete [] data_;
    data_ = newData;
    capacity_ = newCapacity;
  }
  data_[size_++] = value;
}

template < class T >
void knk::Vector < T >::popBack() noexcept {
  if (size_ > 0) {
    --size_;
  }
}

#endif
