// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
  double myPow(double x, int n) {
    double res = x;

    int absn = abs(n);

    if (n == 0)
      return 1;
    if (n == 1)
      return x;

    if (absn % 2 == 0) {
      // if even
      res = myPow(x * x, absn / 2);
    } else {
      // if odd
      res = myPow(x * x, (absn - 1) / 2) * x;
    }

    if (n < 0)
      res = 1 / res;

    return res;
  }
};

int main() {
  Solution a;
  cout << a.myPow(2.0, 999) << endl;

  return 0;
}