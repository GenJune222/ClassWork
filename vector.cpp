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
  return false;
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