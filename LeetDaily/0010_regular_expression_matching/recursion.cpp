// Author: Json Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
  bool isMatch(string s, string p) {
    if (p.empty())
      return s.empty();
    // split into first match and recursion
    bool first_match = !s.empty() && (s[0] == p[0] || p[0] == '.');

    // if we encountered a *
    if (p.size() >= 2 && p[1] == '*') {
      return isMatch(s, p.substr(2)) ||
             (first_match && (isMatch(s.substr(1), p)));
    } else {
      return first_match && isMatch(s.substr(1), p.substr(1));
    }
  }
};

int main() {
  string str1 = "ac";
  string str2 = "ab*c";

  Solution a;
  cout << a.isMatch(str1, str2) << endl;
}