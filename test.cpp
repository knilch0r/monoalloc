// constructing vectors
#include <iostream>
#include <vector>

int main(int argc, const char**argv)
{
  std::vector<int> a;
  std::vector<int> b(23,42);
  std::vector<int> c(b);
  c.push_back(argc);
  a.resize(1024*1024*10*argc);
  a[1000000] = 5;
  a.resize(1);

  std::cout << "c:";
  for (auto x : c) std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}
