// Author: Json Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
  bool isMatchHelper(string &s, string &p, int i, int j,
                     vector<vector<int>> &dp) {
    if (i >= s.size() && j >= p.size()) {
      return true;
    } else if (j >= p.size()) {
      return false;
    }

    if (dp[i][j] != -1) {
      return bool(dp[i][j]);
    }

    // split into first match and recursion
    bool first_match = (i < s.size()) && (s[i] == p[j] || p[j] == '.');

    // if we encountered a *
    if (p.size() - j >= 2 && p[j + 1] == '*') {
      bool temp = isMatchHelper(s, p, i, j + 2, dp) ||
                  (first_match && (isMatchHelper(s, p, i + 1, j, dp)));
      dp[i][j] = int(temp);
      return temp;
    } else {
      bool temp = first_match && isMatchHelper(s, p, i + 1, j + 1, dp);
      dp[i][j] = int(temp);
      return temp;
    }
  }

  bool isMatch(string s, string p) {
    vector<vector<int>> dp(s.size() + 1, vector<int>(p.size() + 1, -1));
    return isMatchHelper(s, p, 0, 0, dp);
  }
};

int main() {
  string str1 = "ac";
  string str2 = "ab*c";

  Solution a;
  cout << a.isMatch(str1, str2) << endl;
}
