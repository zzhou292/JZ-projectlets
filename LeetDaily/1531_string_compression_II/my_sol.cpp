// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
  int dp_helper(vector<vector<int>> &dp_vec, int i, int k, int n, string &s) {
    if (k < 0)
      return n; // this is illegal
    if (i + k >= n)
      return 0; // pruning
    int ans = dp_vec[i][k];
    if (ans != -1)
      return dp_vec[i][k];

    // case 1 -> delete s[i]
    ans = dp_helper(dp_vec, i + 1, k - 1, n, s);

    int len = 0;
    int same = 0;
    int diff = 0;

    for (int j = i; j < n && diff <= k; j++) {
      if (s[j] == s[i]) {
        same++;
        if (same <= 2 || same == 10 || same == 10 || same == 100)
          len++;
      } else {
        diff++;
      }
      ans = min(ans, len + dp_helper(dp_vec, j + 1, k - diff, n, s));
    }
    dp_vec[i][k] = ans;
    return ans;
  }

  int getLengthOfOptimalCompression(string s, int k) {
    // dp struct
    int n = s.size();
    vector<vector<int>> dp_vec(n, vector<int>(k + 1, -1));

    return dp_helper(dp_vec, 0, k, n, s);
  }
};

int main() {
  Solution sol;
  string s = "aaabcccd";
  int k = 2;
  cout << sol.getLengthOfOptimalCompression(s, k) << endl;
  return 0;
}