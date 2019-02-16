#include <iostream>
#include <thread>
#include <vector>

class ThreadtestClass  {
  public:
    void operator()() const {
      for (int i=0; i < 10000; i++) {
	std::vector<char> v(1, 42);
      }
      std::cout << "did some allocations." << '\n';
    }
};

int main() {
  ThreadtestClass ct;
  std::cout << "starting threads..." << '\n';
  std::thread t1(ct);
  std::thread t2(ct);
  std::thread t3(ct);
  t1.join();
  t2.join();
  t3.join();
}
