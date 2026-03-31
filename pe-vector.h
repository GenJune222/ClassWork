#ifndef PE_VECTOR_H
#define PE_VECTOR_H
#include <cstddef>


namespace knk {
  template < class T >
  class Vector {
  public:
    ~Vector();
    Vector();
    Vector(size_t size, const T & value);
    Vector(const Vector<T> & rhs) = delete;
    Vector<T> & operator=(const Vector<T> & rhs) = delete;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    void pushBack(const T&);
    void popBack() noexcept;
    size_t getCapacity() const noexcept;

  private:
    T* data_;
    size_t size_, capacity_;
  };
}
template < class T >
bool knk::Vector < T >::isEmpty() const noexcept{
  return !size_;
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

template < class T >
knk::Vector < T >::Vector(size_t size, const T& value):
  data_(size ? new T[size] : nullptr),
   size_(0),
   capacity_(size)
{};

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