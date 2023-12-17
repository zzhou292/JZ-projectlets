// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
  string toPFull(long long p, bool even_digit) {
    string res = to_string(p);
    if (even_digit) {
      string reverse(res.rbegin(), res.rend());
      res += reverse;
    } else {
      string testsub = res.substr(0, res.size() - 1);
      string reverse(testsub.rbegin(), testsub.rend());
      res += reverse;
    }

    return res;
  }

  string nearestPalindromic(string n) {
    long long nll = stoll(n);

    // Edge cases the most difficult part
    // if nll <= 10, or n = 10, 100, 1000, 10000
    if (nll <= 10 || (nll % 10 == 0) && stoll(n.substr(1, n.size() - 1)) == 0 &&
                         n[0] == '1') {
      return "" + to_string(nll - 1);
    }

    // if nll = 11, 101, 1001, 10001, we need nll-2
    if (nll % 10 == 1 && stoll(n.substr(1, n.size() - 1)) == 1) {
      return "" + to_string(nll - 2);
    }
    if ((nll + 1) % 10 == 0 &&
        stoll(to_string(nll + 1).substr(1, n.size() - 1)) == 0) {
      return "" + to_string(nll + 2);
    }

    // main algorithm processing
    bool even_len = (n.size() % 2 == 0);
    string p_root = "";
    if (even_len == true) {
      p_root = n.substr(0, n.size() / 2);
    } else {
      p_root = n.substr(0, n.size() / 2 + 1);
    }

    long long upper = stoll(toPFull(stoll(p_root) + 1, even_len));
    long long middle = stoll(toPFull(stoll(p_root), even_len));
    long long lower = stoll(toPFull(stoll(p_root) - 1, even_len));

    long long upper_diff = abs(upper - nll);
    long long middle_diff = abs(middle - nll);
    long long lower_diff = abs(lower - nll);

    if (middle_diff == 0) {
      if (upper_diff < lower_diff)
        return to_string(upper);
      else
        return to_string(lower);
    } else {
      auto min_diff = min(upper_diff, min(lower_diff, middle_diff));
      if (min_diff == lower_diff)
        return to_string(lower);
      else if (min_diff == middle_diff)
        return to_string(middle);
      else
        return to_string(upper);
    }

    return "";
  }
};

int main() {
  Solution a;
  cout << a.nearestPalindromic("123") << endl;
  cout << a.nearestPalindromic("1234") << endl;
  cout << a.nearestPalindromic("12345") << endl;
  cout << a.nearestPalindromic("123456") << endl;
  cout << a.nearestPalindromic("1234567") << endl;
  cout << a.nearestPalindromic("12345678") << endl;
  cout << a.nearestPalindromic("123456789") << endl;
  cout << a.nearestPalindromic("1234567890") << endl;
  cout << a.nearestPalindromic("12345678901") << endl;
  cout << a.nearestPalindromic("123456789012") << endl;
  cout << a.nearestPalindromic("1234567890123") << endl;
  cout << a.nearestPalindromic("12345678901234") << endl;
  return 0;
}