#include <iostream>
#include <stdio.h>
#include <thread>
#define ull unsigned long long

void OddSum(const ull start, const ull end) {
  ull result = 0;
  for (ull i = start; i <= end; i++) {
    if (i % 2 == 1) {
      result += i;
    }
  }
}

void EvenSum(const ull start, const ull end) {
  ull result = 0;
  for (ull i = start; i <= end; i++) {
    if (i % 2 == 0) {
      result += i;
    }
  }
}

int main() {
  ull start = 0;
  ull end = 9999999999;

  ull result1 = 0;
  ull result2 = 0;

  auto tp1 = std::chrono::high_resolution_clock::now();

  //   std::thread t1(OddSum, start, end);
  //   std::thread t2(EvenSum, start, end);

  //   t1.join();
  //   t2.join();

  OddSum(start, end);
  EvenSum(start, end);

  auto tp2 = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count();

  std::cout << "Duration: " << duration << std::endl;

  std::cout << result1 << std::endl;
  std::cout << result2 << std::endl;
}