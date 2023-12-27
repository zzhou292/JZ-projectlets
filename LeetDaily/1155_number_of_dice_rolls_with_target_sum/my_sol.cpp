
// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
  const int mod = (int)pow(10, 9) + 7;

  int helper(vector<vector<int>> &dp, int n, int k, int target) {
    if (target == 0 && n == 0)
      return 1;
    if (n == 0 || target <= 0)
      return 0;

    // if exist in memo, return memoed data
    if (dp[n][target] != -1)
      return dp[n][target];

    int res = 0;
    for (int i = 1; i <= k; i++) {
      res = (res + (helper(dp, n - 1, k, target - i) % mod)) % mod;
    }
    dp[n][target] = res % mod;
    return res % mod;
  }

  int numRollsToTarget(int n, int k, int target) {
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, -1));
    auto res = helper(dp, n, k, target);
    return res;
  }
};

int main() {
  Solution a;
  cout << a.numRollsToTarget(30, 30, 500) << endl;

  return 0;
}