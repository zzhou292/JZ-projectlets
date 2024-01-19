// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

// when doing dp, be careful about double counting.

class Solution {
public:
  int checkHelper(vector<vector<int>> &matrix, vector<vector<int>> &memo,
                  vector<vector<int>> &checked, int i, int j) {
    // termination
    if (i == 0)
      return matrix[i][j];

    if (checked[i][j] == 1)
      return memo[i][j];

    int temp_1 = INT_MAX;
    int temp_2 = INT_MAX;
    int temp_3 = INT_MAX;

    temp_1 = checkHelper(matrix, memo, checked, i - 1, j);
    if (j + 1 < matrix[0].size())
      temp_2 = checkHelper(matrix, memo, checked, i - 1, j + 1);
    if (j - 1 >= 0)
      temp_3 = checkHelper(matrix, memo, checked, i - 1, j - 1);

    int res = min(temp_1, min(temp_2, temp_3)) + matrix[i][j];
    memo[i][j] = res;
    checked[i][j] = 1;
    return res;
  }

  int minFallingPathSum(vector<vector<int>> &matrix) {
    // bd check
    if (matrix.size() == 0 || matrix[0].size() == 0)
      return 0;

    // we check each starting position
    int res = INT_MAX;
    vector<vector<int>> memo(matrix.size(),
                             vector<int>(matrix[0].size(), INT_MAX));
    vector<vector<int>> checked(matrix.size(),
                                vector<int>(matrix[0].size(), 0));
    for (int i = 0; i < matrix[0].size(); i++) {
      res = min(res, checkHelper(matrix, memo, checked, matrix.size() - 1, i));
    }

    return res;
  }
};

int main() {
  vector<vector<int>> input = {{63, 70, 79, 18},
                               {90, 16, -10, 32},
                               {100, 84, 59, -84},
                               {23, -3, 26, 69}};

  Solution a;
  cout << a.minFallingPathSum(input) << endl;

  return 0;
}
