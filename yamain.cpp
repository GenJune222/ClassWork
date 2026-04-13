#include <vector>
#include <iostream>
#include <initializer_list>

int main()
{
  // A(size_t, size_t)
  // A(std::initializer_list< size_t >);
  // A a{11ull, 11ull}

  // vector(size_t, size_t);
  // vector(std::initializer_list< size_t >)
  std::vector< size_t > v{11, 10};
  std::cout << v.size() << "\n";
}