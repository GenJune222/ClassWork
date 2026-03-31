#include <iostream>
#include "pe-vector.h"

using knk::Vector;

bool testConstructAndDestruct(const char ** pname) {
  * pname = __func__;
  Vector< int > v;
  return true;
}

bool testDefaultVectorIsEmpty(const char ** pname) {
  * pname = __func__;
  Vector< int > v;
  return v.isEmpty(); // && (!v.getSize()) <- можно, но не нужно. Старые тесты - священная корова
}

bool sizeOfEmptyVector(const char ** pname) {
  * pname = __func__;
  Vector< int > v;
  return !v.getSize();
}

bool sizeOfNonEmptyVector(const char ** pname) {
  * pname = __func__;
  constexpr size_t size = 2ull;
  Vector<int> v(size, 10);
  return v.getSize() == size;
}

bool testCapacityEmpty(const char** p) {
  *p=__func__;
  return Vector<int>{}.getCapacity() == 0;
}
bool testCapacityAllocated(const char** p) {
  *p=__func__;
  return Vector<int>(5,0).getCapacity() == 5;
}
bool testPushBackGrows(const char** p) {
  *p=__func__; Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  return v.getSize() == 2 && v.getCapacity() >= 2;
}
bool testResizeOnOverflow(const char** p) {
  *p=__func__;
  Vector<int> v;
  size_t old = v.getCapacity();
  for(size_t i = 0; i < old + 1; ++i) {
    v.pushBack(0);
  }
  return v.getCapacity() > old;
}
bool testPopBackWorks(const char** p) {
  *p=__func__;
  Vector<int> v(3,0);
  v.popBack();
  return v.getSize() == 2;
}
bool testPopBackEmptyNoexcept(const char** p) {
  *p=__func__;
  Vector<int> v;
  try {
    v.popBack();
    return true;
  } catch(...) {
    return false;
  }
}

int main() {
  using test_t = bool(*)(const char **);
  using case_t = std::pair< test_t, const char * >;
  case_t tests[] = {
    {testConstructAndDestruct, "Vector must be default constructable"},
    {testDefaultVectorIsEmpty, "Default constructed vector must be empty"},
    {sizeOfEmptyVector, "Size of empty vector must be zero"},
    {sizeOfNonEmptyVector, "Size of non-empty vector must be greater than zero"}
  };
  constexpr size_t count = sizeof(tests) / sizeof (test_t);
  for (size_t i = 0; i < count; ++i) {
    const char * testName = nullptr;
    bool r = tests[i].first(&testName);
    if (!r) {
      std::cout << "[FAIL] " << "\n";
      std::cout << "Failed function: " << testName << "\n";
      std::cout << tests[i].second  << "\n";
    }
  }
}