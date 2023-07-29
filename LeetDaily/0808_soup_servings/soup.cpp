// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
  float soupHelper(vector<int> &serving_A, vector<int> &serving_B,
                   vector<int> &remain, vector<vector<float>> &dp) {
    if (remain[0] > 0 && remain[1] > 0) {
      if (dp[remain[0] - 1][remain[1] - 1] != -1.0)
        return dp[remain[0] - 1][remain[1] - 1];
      float res = 0.0;
      for (int i = 0; i < 4; i++) {
        remain[0] = remain[0] - serving_A[i];
        remain[1] = remain[1] - serving_B[i];
        res += 0.25 * soupHelper(serving_A, serving_B, remain, dp);
        remain[0] = remain[0] + serving_A[i];
        remain[1] = remain[1] + serving_B[i];
      }
      dp[remain[0] - 1][remain[1] - 1] = res;
      return res;
    } else {
      // termination conditions
      if (remain[0] <= 0 && remain[1] <= 0) {
        return 0.5;
      } else if (remain[0] <= 0) {
        return 1;
      } else if (remain[1] <= 0) {
        return 0;
      }
    }

    return 0;
  }

  double soupServings(int n) {
    if (n > 4800)
      return 1;
    vector<vector<float>> dp((n + 24) / 25, vector<float>((n + 24) / 25, -1.0));
    vector<int> serving_A = {4, 3, 2, 1};
    vector<int> serving_B = {0, 1, 2, 3};

    vector<int> remain = {(n + 24) / 25, (n + 24) / 25};

    return soupHelper(serving_A, serving_B, remain, dp);
  }
};

int main() {
  Solution a;
  cout << a.soupServings(50) << endl;

  return 0;
}