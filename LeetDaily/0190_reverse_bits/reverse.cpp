// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
  uint32_t reverseBits(uint32_t n) {
    uint32_t res = 0;
    for (int i = 0; i < 32; i++) {
      int bit_val = n & (1 << i);

      if (bit_val != 0) {
        res = res | (1 << (31 - i));
      }
    }

    return res;
  }
};

int main() {
  uint32_t input = 43261596;

  Solution a;
  cout << a.reverseBits(input) << endl;

  return 0;
}