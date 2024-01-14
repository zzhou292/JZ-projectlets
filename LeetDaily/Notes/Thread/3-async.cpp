#include <future>
#include <iostream>
#include <stdio.h>
#include <thread>
#define ull unsigned long long

ull OddSum(const ull start, const ull end) {
  ull result = 0;
  for (ull i = start; i <= end; i++) {
    if (i % 2 == 1) {
      result += i;
    }
  }
  return result;
}

ull EvenSum(const ull start, const ull end) {
  ull result = 0;
  for (ull i = start; i <= end; i++) {
    if (i % 2 == 0) {
      result += i;
    }
  }
  return result;
}

int main() {
  ull start = 0;
  ull end = 9999999999;

  auto tp1 = std::chrono::high_resolution_clock::now();

  // if async then no need to operate on promise and future
  // direct return the function return value
  std::future<ull> f1 = std::async(std::launch::async, OddSum, start, end);
  std::future<ull> f2 = std::async(std::launch::async, EvenSum, start, end);

  std::cout << f1.get() << std::endl;
  std::cout << f2.get() << std::endl;
  auto tp2 = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count();

  std::cout << "Duration: " << duration << std::endl;
}