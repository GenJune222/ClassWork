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
  //v.pushBack(2);
  try {
    int &r = v.at(0);
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
    {testCopyConstructor, "Copied vector must be equal to original"}
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