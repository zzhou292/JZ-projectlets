#include <iostream>
#include <mutex>
#include <stdio.h>
#include <thread>
#define ull unsigned long long

ull total_val = 0;
std::mutex m;

void addvalue(ull val) {
  for (ull i = 0; i < val; i++) {
    m.lock();
    total_val += i;
    m.unlock();
  }
}

int main() {

  std::thread t1(addvalue, 10000);
  std::thread t2(addvalue, 20000);
  std::thread t3(addvalue, 30000);
  std::thread t4(addvalue, 40000);

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  std::cout << total_val << std::endl;

  return 0;
}