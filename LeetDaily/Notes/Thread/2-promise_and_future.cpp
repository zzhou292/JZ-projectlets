#include <future>
#include <iostream>
#include <stdio.h>
#include <thread>
#define ull unsigned long long

void OddSum(std::promise<ull> p, const ull start, const ull end) {
  ull result = 0;
  for (ull i = start; i <= end; i++) {
    if (i % 2 == 1) {
      result += i;
    }
  }
  p.set_value(result);
}

void EvenSum(std::promise<ull> p, const ull start, const ull end) {
  ull result = 0;
  for (ull i = start; i <= end; i++) {
    if (i % 2 == 0) {
      result += i;
    }
  }
  p.set_value(result);
}

int main() {
  ull start = 0;
  ull end = 9999999999;

  ull result1 = 0;
  ull result2 = 0;

  auto tp1 = std::chrono::high_resolution_clock::now();

  std::promise<ull> p1;
  std::promise<ull> p2;

  std::future<ull> f1 = p1.get_future();
  std::future<ull> f2 = p2.get_future();

  std::thread t1(OddSum, std::move(p1), start, end);
  std::thread t2(EvenSum, std::move(p2), start, end);

 

  std::cout << f1.get() << std::endl;
  std::cout << f2.get() << std::endl;

  t1.join();
  t2.join();

  auto tp2 = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count();

  std::cout << "Duration: " << duration << std::endl;
}