// Author: Jason Zhou
// Attempted solution, it is good, but there are optimizations to be done
#include "../general_include.h"

using namespace std;

class Solution {
public:
  bool isPalindrome(string s) {
    vector<char> c_arr;
    for (int i = 0; i < s.size(); i++) {
      if (s[i] >= 'a' && s[i] <= 'z') {
        c_arr.push_back(s[i]);
      } else if (s[i] >= 'A' && s[i] <= 'Z') {
        c_arr.push_back(s[i] + 32);
      } else if (s[i] >= '0' && s[i] <= '9') {
        c_arr.push_back(s[i]);
      }
    }

    for (int i = 0; i < c_arr.size() / 2; i++) {
      if (c_arr[i] != c_arr[c_arr.size() - 1 - i])
        return false;
    }

    return true;
  }
};

int main() {
  string input = "A man, a plan, a canal: Panama";

  Solution a;
  cout << a.isPalindrome(input) << endl;

  return 0;
}