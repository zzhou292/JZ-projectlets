#include <condition_variable>
#include <iostream>
#include <mutex>
#include <stdio.h>
#include <thread>
#define ull unsigned long long

std::mutex m;
std::condition_variable cv;
ull total_val = 0;

void addMoney(ull temp) {
  std::lock_guard<std::mutex> lock(m);
  total_val += temp;
  std::cout << "Amount added to account: " << temp << std::endl;
  cv.notify_all();
}

void withdrawMoney(ull temp) {
  std::unique_lock<std::mutex> lock(m);
  cv.wait(lock, [] { return total_val > 0; });

  if (total_val < temp) {
    std::cout << "Insufficient balance" << std::endl;
    return;
  } else {
    total_val -= temp;
    std::cout << "Balance withdrew: " << temp << std::endl;
  }

  std::cout << "Current balance: " << total_val << std::endl;
}

int main() {
  std::thread t1(withdrawMoney, 100);
  std::thread t2(withdrawMoney, 50);
  std::thread t3(addMoney, 200);

  t1.join();
  t2.join();
  t3.join();

  return 0;
}