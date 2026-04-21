#include <iostream>
#include <cstring>
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
  return v.isEmpty();
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

bool testCapacityEmpty(const char** pname) {
  * pname = __func__;
  return Vector<int>{}.getCapacity() == 0;
}
bool testCapacityAllocated(const char** pname) {
  * pname = __func__;
  return Vector<int>(5,0).getCapacity() == 5;
}
bool testPushBackGrows(const char** pname) {
  * pname = __func__;
  Vector<int> v;
  v.pushBack(1);
  v.pushBack(2);
  return v.getSize() == 2 && v.getCapacity() >= 2;
}
bool testResizeOnOverflow(const char** pname) {
  * pname = __func__;
  Vector<int> v;
  size_t old = v.getCapacity();
  for(size_t i = 0; i < old + 1; ++i) {
    v.pushBack(0);
  }
  return v.getCapacity() > old;
}
bool testPopBackWorks(const char** pname) {
  * pname = __func__;
  Vector<int> v(3,0);
  v.popBack();
  return v.getSize() == 2;
}
bool testPopBackEmptyNoexcept(const char** pname) {
  * pname = __func__;
  Vector<int> v;
  try {
    v.popBack();
    return true;
  } catch(...) {
    return false;
  }
}

bool testElementCheckedAccess(const char **pname) {
  *pname = __func__;
  Vector<int> v;
  v.pushBack(2);
  const Vector< int >& rv = v;
  try {
    const int& r = rv.at(0);
    return r == 2;
  } catch (...) {
    return false;
  }
}

bool testElementCheckedOutOfBoundAccess(const char **pname) {
  *pname = __func__;
  Vector<int> v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range &e) {
    const char *text = e.what();
    return !std::strcmp("id out of bound", text);
  } catch (...) {
    return false;
  }
}

bool testElementCheckOutOfBoundConstAccess(const char ** pname) {
  *pname = __func__;
  const Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range& e) {
    const char * text = e.what();
    return !std::strcmp("id out of bound", text);
  } catch (...) {
    return true;
  }
}

bool testElementCheckConstAccess(const char **pname) {
  *pname = __func__;
  Vector<int> v;
  v.pushBack(2);
  const Vector<int> &rv = v;
  try {
    const int &r = rv.at(0);
    return r == 2;
  } catch (...) {
    return false;
  }
}

bool testCopyConstructor(const char **pname) {
  *pname = __func__;
  Vector<int> v(10, 2);
  v.pushBack(1);
  v.pushBack(2);
  Vector<int> yav = v;
  if (!v.isEmpty() && !yav.isEmpty()) {
    throw std::logic_error("Vectors expected to be non-empty");
  }
  bool isEqual = yav.getSize() == v.getSize();
  for (size_t i = 0; isEqual && i < v.getSize(); i++) {
    try {
      isEqual = v.at(i) == yav.at(i);
    } catch (...) {
      return false;
    }
  }
  return isEqual;
}

bool testCtorSizeValue(const char** pname) {
  *pname = __func__;
  Vector<int> v(3, 42);
  return v.getSize() == 3 && v[0] == 42 && v[1] == 42 && v[2] == 42;
}

bool testCopyCtor(const char** pname) {
  *pname = __func__;
  Vector<int> a(2, 10); a.pushBack(20);
  Vector<int> b(a);
  return b.getSize() == 3 && b[2] == 20 && a[0] == b[0];
}

bool testMoveCtor(const char** pname) {
  *pname = __func__;
  Vector<int> a(2, 5);
  Vector<int> b(std::move(a));
  return b.getSize() == 2 && b[0] == 5 && a.isEmpty();
}

bool testCopyAssign(const char** pname) {
  *pname = __func__;
  Vector<int> a(2, 100), b(1, 0);
  b = a;
  return b.getSize() == 2 && b[0] == 100 && a.getSize() == 2;
}

bool testMoveAssign(const char** pname) {
  *pname = __func__;
  Vector<int> a(3, 7), b(10, 999);
  b = std::move(a);
  return b.getSize() == 3 && b[0] == 7 && a.isEmpty();
}

bool testSwap(const char** pname) {
  *pname = __func__;
  Vector<int> a(2, 1), b(3, 2);
  a.swap(b);
  return a.getSize() == 3 && a[0] == 2 && b.getSize() == 2 && b[0] == 1;
}

int main() {
  using test_t = bool(*)(const char **);
  using case_t = std::pair< test_t, const char * >;
  case_t tests[] = {
    {testConstructAndDestruct, "Vector must be default constructable"},
    {testDefaultVectorIsEmpty, "Default constructed vector must be empty"},
    {sizeOfEmptyVector, "Size of empty vector must be zero"},
    {sizeOfNonEmptyVector, "Size of non-empty vector must be greater than zero"},

    {testCapacityEmpty, "Capacity of empty vector must be 0"},
    {testCapacityAllocated, "Capacity of allocated vector must match size"},
    {testPushBackGrows, "pushBack must increase size and capacity"},
    {testResizeOnOverflow, "pushBack must trigger resize on overflow"},
    {testPopBackWorks, "popBack must decrease size"},
    {testPopBackEmptyNoexcept, "popBack on empty vector must not throw"},

    {testElementCheckedAccess, "Inbound access must return lvalue reference"},
    {testElementCheckedOutOfBoundAccess, "Out of bound access must generate exception"},
    {testCopyConstructor, "Copied vector must be equal to original"},
    { testElementCheckConstAccess, "same as checkaccess" },
    { testElementCheckOutOfBoundConstAccess, "same as checkbound" },

    {testCtorSizeValue, "Constructor(size,value) fills correctly"},
    {testCopyCtor, "Copy constructor creates independent copy"},
    {testMoveCtor, "Move constructor transfers resources"},
    {testCopyAssign, "Copy assignment works correctly"},
    {testMoveAssign, "Move assignment transfers resources"},
    {testSwap, "Swap exchanges vector contents"}
  };
  constexpr size_t count = sizeof(tests) / sizeof (test_t);
  size_t failed = 0;
  for (size_t i = 0; i < count; ++i) {
    const char * testName = nullptr;

    bool r = false;
    try {
      r = tests[i].first(&testName);
    } catch (const std::logic_error &e) {
      std::cout << "[NOT RUN] " << testName << "\n";
      std::cout << "\t" << "Reason: " << e.what() << "\n";
      failed++;
      continue;
    }

    if (!r) {
      std::cout << "[FAIL] " << "\n";
      std::cout << "Failed function: " << testName << "\n";
      std::cout << tests[i].second  << "\n";
      ++failed;
    }
  }
  if (failed == 0) {
    std::cout << "[PASS] All " << count << " tests passed!\n";
  } else {
    std::cout << "[SUMMARY] " << failed << " of " << count << " tests failed\n";
  }

  return failed > 0 ? 1 : 0;
}