#include <algorithm>
#include <functional>
#include <iostream>
#include <stdio.h>

void ForEach(const std::vector<int> &my_vec, const std::vector<int> &my_vec_2,
             std::function<void(int, int)> func) {
  for (int i = 0; i < my_vec.size(); i++) {
    func(my_vec[i], my_vec_2[i]);
  }
}

int main() {
  std::vector<int> my_vec = {1, 2, 3, 4, 5};
  std::vector<int> my_vec_2 = {1, 2, 3, 4, 5};
  int a = 1;
  int b = 2;
  ForEach(my_vec, my_vec_2, [&a, &b](int x1, int x2) {
    std::cout << a + b + x1 + x2 << std::endl;
  });

  return 0;
}