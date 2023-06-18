// Author: Jason Zhou
// Attempted solution, it is good, but there are optimizations to be done
#include "../general_include.h"

using namespace std;

class Solution {
public:
  bool isPalindrome(string s) {
    int start = 0;
    int end = s.size() - 1;
    while (start <= end) {
      if (!isalnum(s[start])) {
        start++;
        continue;
      }
      if (!isalnum(s[end])) {
        end--;
        continue;
      }
      if (tolower(s[start]) != tolower(s[end]))
        return false;
      else {
        start++;
        end--;
      }
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